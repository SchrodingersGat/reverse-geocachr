################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c 

OBJS += \
./Src/common/waypoint.o 

C_DEPS += \
./Src/common/waypoint.d 


# Each subdirectory must supply rules for building sources it contributes
Src/common/waypoint.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/common/waypoint.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


