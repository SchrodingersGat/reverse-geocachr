################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ILI9340_linker.c \
../Src/display.c \
../Src/gpio.c \
../Src/gps.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/system_stm32f3xx.c \
../Src/tim.c \
../Src/timer.c \
../Src/usart.c 

OBJS += \
./Src/ILI9340_linker.o \
./Src/display.o \
./Src/gpio.o \
./Src/gps.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/system_stm32f3xx.o \
./Src/tim.o \
./Src/timer.o \
./Src/usart.o 

C_DEPS += \
./Src/ILI9340_linker.d \
./Src/display.d \
./Src/gpio.d \
./Src/gps.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/system_stm32f3xx.d \
./Src/tim.d \
./Src/timer.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/gps.o: ../Src/gps.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -u _printf_float -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


