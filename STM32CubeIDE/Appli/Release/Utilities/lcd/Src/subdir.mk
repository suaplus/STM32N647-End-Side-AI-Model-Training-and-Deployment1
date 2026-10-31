################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Utilities/lcd/stm32_lcd.c 

OBJS += \
./Utilities/lcd/Src/stm32_lcd.o 

C_DEPS += \
./Utilities/lcd/Src/stm32_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/lcd/Src/stm32_lcd.o: C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Utilities/lcd/stm32_lcd.c Utilities/lcd/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32N647xx -DBSP_UART_RX_DISABLE -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_SW_FALLBACK -c -I../../../Appli/Core/Inc -I../../../Secure_nsclib -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/Include -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/NORFlash" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/HyperRAM" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/LED" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/03_My_Fire_Smoke_AI_Image_Classification_v2/Drivers/BSP/LCD" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/03_My_Fire_Smoke_AI_Image_Classification_v2/Drivers/BSP/BUS" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/UART" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/DSP/Include" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_ISP/isp/Inc" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_ISP/evision/Inc" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/03_My_Fire_Smoke_AI_Image_Classification_v2/Appli/STM32_MW_ISP" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA/sensors" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA/sensors/imx335" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/03_My_Fire_Smoke_AI_Image_Classification_v2/Appli/STM32_MW_CAMERA" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Inc" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Npu/ll_aton" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Npu/Devices/STM32N6XX" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_VISION_MODELS_PP/Inc" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Utilities/lcd" -I"C:/15-STM32N647_AI/04_SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/03_My_Fire_Smoke_AI_Image_Classification_v2/Model" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-lcd-2f-Src

clean-Utilities-2f-lcd-2f-Src:
	-$(RM) ./Utilities/lcd/Src/stm32_lcd.cyclo ./Utilities/lcd/Src/stm32_lcd.d ./Utilities/lcd/Src/stm32_lcd.o ./Utilities/lcd/Src/stm32_lcd.su

.PHONY: clean-Utilities-2f-lcd-2f-Src

