################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Drivers/BSP/BUS/bsp_bus.c 

OBJS += \
./Drivers/BSP/BUS/bsp_bus.o 

C_DEPS += \
./Drivers/BSP/BUS/bsp_bus.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/BUS/bsp_bus.o: D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Drivers/BSP/BUS/bsp_bus.c Drivers/BSP/BUS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N647xx -DBSP_UART_RX_DISABLE -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_SW_FALLBACK -c -I../../../Appli/Core/Inc -I../../../Secure_nsclib -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../../../../STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/Include -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/NORFlash" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/HyperRAM" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/LED" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Drivers/BSP/LCD" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Drivers/BSP/BUS" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Drivers/BSP/UART" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Drivers/CMSIS/DSP/Include" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_ISP/isp/Inc" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_ISP/evision/Inc" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Appli/STM32_MW_ISP" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA/sensors" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_MW_CAMERA/sensors/imx335" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Appli/STM32_MW_CAMERA" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Inc" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Npu/ll_aton" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/AI/Npu/Devices/STM32N6XX" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Middlewares/STM32_VISION_MODELS_PP/Inc" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/STM32Cube_FW_N6_V1.0.0/Utilities/lcd" -I"D:/STM32_PRO/STM32_N647/SOP_Gateway_Project/02_STM32N647_MCU/SoftwarePackage/Projects/99_Applications/002_My_Fire_AI_Image_Classification/Model" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-BUS

clean-Drivers-2f-BSP-2f-BUS:
	-$(RM) ./Drivers/BSP/BUS/bsp_bus.cyclo ./Drivers/BSP/BUS/bsp_bus.d ./Drivers/BSP/BUS/bsp_bus.o ./Drivers/BSP/BUS/bsp_bus.su

.PHONY: clean-Drivers-2f-BSP-2f-BUS

