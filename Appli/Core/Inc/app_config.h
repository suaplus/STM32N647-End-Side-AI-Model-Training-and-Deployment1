/**
 ****************************************************************************************************
 * @file        app_config.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2025-01-13
 * @brief       app_config.h文件
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

#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

#include "stm32n6xx_hal.h"

#define LCD_BG_WIDTH                    480
#define LCD_BG_HEIGHT                   480
#define LCD_FG_WIDTH                    800
#define LCD_FG_HEIGHT                   480

#define CAMERA_MIRROR_FLIP              CMW_MIRRORFLIP_MIRROR

#define NN_WIDTH                        160//240
#define NN_HEIGHT                       160//240
#define NN_FORMAT                       DCMIPP_PIXEL_PACKER_FORMAT_RGB888_YUV444_1
#define NN_BPP                          3
#define NN_CLASSES                      3//101

#define NN_CLASSES_TABLE { \
							"FIRE",               \
							"NEUTRAL",            \
							"SMOKE"               \
}
#if 0
#define NN_CLASSES_TABLE                {\
                                            "apple_pie",\
                                            "baby_back_ribs",\
                                            "baklava",\
                                            "beef_carpaccio",\
                                            "beef_tartare",\
                                            "beet_salad",\
                                            "beignets",\
                                            "bibimbap",\
                                            "bread_pudding",\
                                            "breakfast_burrito",\
                                            "bruschetta",\
                                            "caesar_salad",\
                                            "cannoli",\
                                            "caprese_salad",\
                                            "carrot_cake",\
                                            "ceviche",\
                                            "cheesecake",\
                                            "cheese_plate",\
                                            "chicken_curry",\
                                            "chicken_quesadilla",\
                                            "chicken_wings",\
                                            "chocolate_cake",\
                                            "chocolate_mousse",\
                                            "churros",\
                                            "clam_chowder",\
                                            "club_sandwich",\
                                            "crab_cakes",\
                                            "creme_brulee",\
                                            "croque_madame",\
                                            "cup_cakes",\
                                            "deviled_eggs",\
                                            "donuts",\
                                            "dumplings",\
                                            "edamame",\
                                            "eggs_benedict",\
                                            "escargots",\
                                            "falafel",\
                                            "filet_mignon",\
                                            "fish_and_chips",\
                                            "foie_gras",\
                                            "french_fries",\
                                            "french_onion_soup",\
                                            "french_toast",\
                                            "fried_calamari",\
                                            "fried_rice",\
                                            "frozen_yogurt",\
                                            "garlic_bread",\
                                            "gnocchi",\
                                            "greek_salad",\
                                            "grilled_cheese_sandwich",\
                                            "grilled_salmon",\
                                            "guacamole",\
                                            "gyoza",\
                                            "hamburger",\
                                            "hot_and_sour_soup",\
                                            "hot_dog",\
                                            "huevos_rancheros",\
                                            "hummus",\
                                            "ice_cream",\
                                            "lasagna",\
                                            "lobster_bisque",\
                                            "lobster_roll_sandwich",\
                                            "macaroni_and_cheese",\
                                            "macarons",\
                                            "miso_soup",\
                                            "mussels",\
                                            "nachos",\
                                            "omelette",\
                                            "onion_rings",\
                                            "oysters",\
                                            "pad_thai",\
                                            "paella",\
                                            "pancakes",\
                                            "panna_cotta",\
                                            "peking_duck",\
                                            "pho",\
                                            "pizza",\
                                            "pork_chop",\
                                            "poutine",\
                                            "prime_rib",\
                                            "pulled_pork_sandwich",\
                                            "ramen",\
                                            "ravioli",\
                                            "red_velvet_cake",\
                                            "risotto",\
                                            "samosa",\
                                            "sashimi",\
                                            "scallops",\
                                            "seaweed_salad",\
                                            "shrimp_and_grits",\
                                            "spaghetti_bolognese",\
                                            "spaghetti_carbonara",\
                                            "spring_rolls",\
                                            "steak",\
                                            "strawberry_shortcake",\
                                            "sushi",\
                                            "tacos",\
                                            "takoyaki",\
                                            "tiramisu",\
                                            "tuna_tartare",\
                                            "waffles"\
                                        }
#endif
#define NN_OBJDETECT_PROBE_THRESHOLD    0.50f//0.85f
#define NN_OUTPUT_NUMBER                1

#endif
