/**
 ****************************************************************************************************
 * @file        app.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2025-01-13
 * @brief       app.c文件
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 N647开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#include "app.h"
#include "app_config.h"
#include "app_lcd.h"
#include "app_camera.h"
#include "ll_aton_runtime.h"
#include "led.h"


static const char *nn_classes_table[NN_CLASSES] = NN_CLASSES_TABLE;
static volatile uint32_t app_nn_frame_count = 0;

static void app_camera_nn_pipe_frame_cb(void);
static uint32_t app_get_array_max_index(float_t *nn_out, uint32_t nn_out_len);
//static void app_display_network_output(const char *class_name, float_t class_probe, uint32_t inference_ms);
static void app_display_network_output(float_t normal_prob,float_t fire_prob,uint32_t inference_ms);



#if 1
void app_run(void)
{

    /* =====================================================
     * 声明 Default 神经网络实例
     * 必须有这一句，否则 NN_Instance_Default 不存在
     * ===================================================== */
    LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);


    /* =====================================================
     * 获取网络 Input / Output 描述
     * ===================================================== */
    const LL_Buffer_InfoTypeDef *nn_in_info =
        LL_ATON_Input_Buffers_Info_Default();

    const LL_Buffer_InfoTypeDef *nn_out_info =
        LL_ATON_Output_Buffers_Info_Default();


    uint8_t *nn_in;

    float_t *nn_out[NN_OUTPUT_NUMBER];

    uint32_t nn_out_len[NN_OUTPUT_NUMBER];

    uint8_t i;

    uint32_t time_stamp[2];


    /* =====================================================
     * 3分类 Softmax
     *
     * 0 = FIRE
     * 1 = NEUTRAL
     * 2 = SMOKE
     * ===================================================== */
    float_t prob[NN_CLASSES];

    float_t max_logit;
    float_t exp_sum;

    uint32_t max_class;
    float_t max_prob;


    /* =====================================================
     * 获取神经网络输入 Buffer
     *
     * 新模型：
     * UINT8
     * 160 x 160 x 3
     * ===================================================== */
    nn_in =
        (uint8_t *)LL_Buffer_addr_start(&nn_in_info[0]);


    /* =====================================================
     * 获取神经网络输出 Buffer
     *
     * generate:
     * --output-data-type float32
     *
     * Output:
     * float32[3]
     * ===================================================== */
    for (i = 0; i < NN_OUTPUT_NUMBER; i++)
    {
        nn_out[i] =
            (float_t *)LL_Buffer_addr_start(&nn_out_info[i]);

        nn_out_len[i] =
            LL_Buffer_len(&nn_out_info[i]);
    }


    /* =====================================================
     * LCD 初始化
     * ===================================================== */
    app_lcd_init();


    /* =====================================================
     * Camera 初始化
     *
     * PIPE2 完成一帧后：
     * app_camera_nn_pipe_frame_cb()
     * 会增加 app_nn_frame_count
     * ===================================================== */
    app_camera_init(
        NULL,
        NULL,
        NULL,
        app_camera_nn_pipe_frame_cb
    );


    /* =====================================================
     * PIPE1
     *
     * Camera -> LCD
     * ===================================================== */
    app_camera_display_pipe_start(
        app_lcd_get_bg_buffer(),
        CMW_MODE_CONTINUOUS
    );



    /* =====================================================
     * 主循环
     * ===================================================== */
    while (1)
    {

        /* -------------------------------------------------
         * Camera / ISP
         * ------------------------------------------------- */
        app_camera_isp_update();


        /* -------------------------------------------------
         * PIPE2
         *
         * Camera
         *   ↓
         * DCMIPP
         *   ↓
         * 160 x 160 RGB888
         *   ↓
         * nn_in
         * ------------------------------------------------- */
        app_camera_nn_pipe_start(
            nn_in,
            CMW_MODE_SNAPSHOT
        );


        /* -------------------------------------------------
         * 等待 NN PIPE2 一帧采集完成
         * ------------------------------------------------- */
        while (app_nn_frame_count == 0)
        {
            app_camera_isp_update();
        }

        app_nn_frame_count = 0;





#if 0
        /* =====================================================
         * 固定图片测试
         *
         * 不使用 Camera PIPE2
         * PC生成的160x160 RGB888直接送入模型
         * ===================================================== */

        memcpy(
            nn_in,
            test_image,
            160 * 160 * 3
        );


        /* CPU修改了nn_in
         * NPU读取前Clean DCache
         */
        SCB_CleanDCache_by_Addr(
            nn_in,
            160 * 160 * 3
        );

#endif
        /* =================================================
         * NPU 推理
         * ================================================= */
        time_stamp[0] = HAL_GetTick();

        LL_ATON_RT_Main(
            &NN_Instance_Default
        );

        time_stamp[1] = HAL_GetTick();


        /* =================================================
         * NPU -> CPU
         *
         * NPU 写完输出后，
         * CPU 读取之前 Invalidate DCache
         * ================================================= */
        for (i = 0; i < NN_OUTPUT_NUMBER; i++)
        {
            SCB_InvalidateDCache_by_Addr(
                nn_out[i],
                nn_out_len[i]
            );
        }


        /* =================================================
         * 新模型输出
         *
         * nn_out[0][0] = FIRE logit
         * nn_out[0][1] = NEUTRAL logit
         * nn_out[0][2] = SMOKE logit
         *
         * 这里是 logits，不直接当百分比。
         * ================================================= */


        /* =================================================
         * Step 1：寻找最大 Logit
         *
         * 后面计算：
         *
         * exp(logit - max_logit)
         *
         * 防止 expf() 数值溢出
         * ================================================= */
        max_logit = nn_out[0][0];

        for (i = 1; i < NN_CLASSES; i++)
        {
            if (nn_out[0][i] > max_logit)
            {
                max_logit = nn_out[0][i];
            }
        }


        /* =================================================
         * Step 2：Softmax 分子
         * ================================================= */
        exp_sum = 0.0f;

        for (i = 0; i < NN_CLASSES; i++)
        {
            prob[i] =
                expf(nn_out[0][i] - max_logit);

            exp_sum += prob[i];
        }


        /* =================================================
         * Step 3：Softmax 归一化
         *
         * 得到真正 0~1 的概率
         * ================================================= */
        for (i = 0; i < NN_CLASSES; i++)
        {
            prob[i] /= exp_sum;
        }


        /* =================================================
         * Step 4：寻找最大概率
         * ================================================= */
        max_class = 0;
        max_prob  = prob[0];

        for (i = 1; i < NN_CLASSES; i++)
        {
            if (prob[i] > max_prob)
            {
                max_prob  = prob[i];
                max_class = i;
            }
        }


        /* =================================================
         * LCD 前景层开始更新
         * ================================================= */
        app_lcd_draw_area_update();


        /* 清除上一帧文字 */
        UTIL_LCD_FillRect(
            0,
            0,
            LCD_FG_WIDTH,
            LCD_FG_HEIGHT,
            0x00000000
        );


        /* =================================================
         * 标题
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(0),
            RIGHT_MODE,
            "FIRE / SMOKE AI"
        );


        /* =================================================
         * 推理时间
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(2),
            RIGHT_MODE,
            "Inference: %lu ms",
            time_stamp[1] - time_stamp[0]
        );


        /* =================================================
         * FIRE
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(4),
            RIGHT_MODE,
            "FIRE: %.1f%%",
            prob[0] * 100.0f
        );


        /* =================================================
         * NEUTRAL
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(5),
            RIGHT_MODE,
            "NEUTRAL: %.1f%%",
            prob[1] * 100.0f
        );


        /* =================================================
         * SMOKE
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(6),
            RIGHT_MODE,
            "SMOKE: %.1f%%",
            prob[2] * 100.0f
        );


        /* =================================================
         * 最终分类结果
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(8),
            RIGHT_MODE,
            "Result: %s",
            nn_classes_table[max_class]
        );


        /* =================================================
         * 最大置信度
         * ================================================= */
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(9),
            RIGHT_MODE,
            "Confidence: %.1f%%",
            max_prob * 100.0f
        );
        /* =================================================
         * 原始数据值
         * ================================================= */

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(11),
            RIGHT_MODE,
            "RAW0: %.3f",
            nn_out[0][0]
        );

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(12),
            RIGHT_MODE,
            "RAW1: %.3f",
            nn_out[0][1]
        );

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(13),
            RIGHT_MODE,
            "RAW2: %.3f",
            nn_out[0][2]
        );

        /* =================================================
         * 提交 LCD FG Layer
         * ================================================= */
        app_lcd_draw_area_commit();
    }
}
#endif

#if 0
void app_run(void)
{
#if 0
	   /* 1. 初始化 LCD */
	    app_lcd_init();

	    /* 2. 初始化 Camera
	       不测试 NN，所以回调也可以不给 */
	    app_camera_init(NULL, NULL, NULL, NULL);

	    /* 3. 启动 Camera -> LCD 显示通道 */
	    app_camera_display_pipe_start(
	        app_lcd_get_bg_buffer(),
	        CMW_MODE_CONTINUOUS
	    );

	    /* 4. 只运行 Camera / ISP */
	    while (1)
	    {
	        app_camera_isp_update();
	    }

#endif

    LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);
    const LL_Buffer_InfoTypeDef *nn_in_info = LL_ATON_Input_Buffers_Info_Default();
    const LL_Buffer_InfoTypeDef *nn_out_info = LL_ATON_Output_Buffers_Info_Default();
    uint8_t *nn_in;
    float_t  *nn_out[NN_OUTPUT_NUMBER];
    uint32_t nn_out_len[NN_OUTPUT_NUMBER];
    uint8_t i;
    uint32_t time_stamp[2];
    uint32_t index;

    nn_in = (float_t  *)LL_Buffer_addr_start(&nn_in_info[0]);

    for (i = 0; i < NN_OUTPUT_NUMBER; i++)
    {
        nn_out[i] = (uint8_t *)LL_Buffer_addr_start(&nn_out_info[i]);
        nn_out_len[i] = LL_Buffer_len(&nn_out_info[i]);
    }

    app_lcd_init();
    app_camera_init(NULL, NULL, NULL, app_camera_nn_pipe_frame_cb);

    app_camera_display_pipe_start(app_lcd_get_bg_buffer(), CMW_MODE_CONTINUOUS);

    while (1)
    {
    	//摄像头读取一帧数据
        app_camera_isp_update();

        app_camera_nn_pipe_start(nn_in, CMW_MODE_SNAPSHOT);
        while (app_nn_frame_count == 0);
        app_nn_frame_count = 0;

        time_stamp[0] = HAL_GetTick();
        //NPU推理
        LL_ATON_RT_Main(&NN_Instance_Default);

        time_stamp[1] = HAL_GetTick();

        /* NPU写完输出后，CPU读取前先Invalidate DCache */
        for (i = 0; i < NN_OUTPUT_NUMBER; i++)
        {
            SCB_InvalidateDCache_by_Addr(
                nn_out[i],
                nn_out_len[i]
            );
        }

        /* UINT8 [NORMAL, FIRE] 取得最大概率类别 */
        index = app_get_array_max_index(nn_out[0], nn_out_len[0]);

        /*
         * TFLite output quantization:
         *
         * real_value = (quantized_value - zero_point) * scale
         *
         * scale      = 0.00390625 = 1 / 256
         * zero_point = 0
         */

        app_display_network_output(
            nn_classes_table[index],
            (float_t)nn_out[0][index] / 256.0f,
            time_stamp[1] - time_stamp[0]
        );
    }


}
#endif
static void app_camera_nn_pipe_frame_cb(void)
{
    app_nn_frame_count++;
}

static uint32_t app_get_array_max_index(float_t *nn_out, uint32_t nn_out_len)
{
    uint32_t index = 0;
    uint32_t i;

    for (i = 1; i < NN_CLASSES; i++)
    {
        if (nn_out[i] > nn_out[index])
        {
            index = i;
        }
    }

    return index;
}

static void app_display_network_output(float_t normal_prob,float_t fire_prob,uint32_t inference_ms)
{
    uint8_t line_nb = 0;


    /* =====================================================
     * 开始更新LCD前景层
     * ===================================================== */
    app_lcd_draw_area_update();


    /* 清除上一帧文字 */
    UTIL_LCD_FillRect(
        0,
        0,
        LCD_FG_WIDTH,
        LCD_FG_HEIGHT,
        0x00000000
    );


    /* =====================================================
     * 标题
     * ===================================================== */
    UTIL_LCDEx_PrintfAt(
        0,
        LINE(line_nb),
        RIGHT_MODE,
        "FIRE AI"
    );


    /* =====================================================
     * 推理时间
     * ===================================================== */
    line_nb += 2;

    UTIL_LCDEx_PrintfAt(
        0,
        LINE(line_nb),
        RIGHT_MODE,
        "Inference: %lu ms",
        inference_ms
    );


    /* =====================================================
     * NORMAL概率
     * ===================================================== */
    line_nb += 2;

    UTIL_LCDEx_PrintfAt(
        0,
        LINE(line_nb),
        RIGHT_MODE,
        "NORMAL: %.1f%%",
        normal_prob * 100.0f
    );


    /* =====================================================
     * FIRE概率
     * ===================================================== */
    line_nb += 1;

    UTIL_LCDEx_PrintfAt(
        0,
        LINE(line_nb),
        RIGHT_MODE,
        "FIRE: %.1f%%",
        fire_prob * 100.0f
    );


    /* =====================================================
     * 最终检测结果
     *
     * FIRE >= 60%   -> 检测到火焰
     *
     * FIRE <= 40%   -> 未检测到火焰
     *
     * 40%~60%       -> 不确定
     * ===================================================== */
    line_nb += 2;


    if (fire_prob >= 0.60f)
    {
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "FIRE DETECTED!"
        );

        line_nb += 1;

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "WARNING!"
        );
    }
    else if (fire_prob <= 0.40f)
    {
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "NO FIRE"
        );

        line_nb += 1;

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "STATUS: NORMAL"
        );
    }
    else
    {
        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "UNCERTAIN"
        );

        line_nb += 1;

        UTIL_LCDEx_PrintfAt(
            0,
            LINE(line_nb),
            RIGHT_MODE,
            "KEEP CHECKING..."
        );
    }


    /* =====================================================
     * 提交LCD前景层
     * ===================================================== */
    app_lcd_draw_area_commit();
}
