################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/boxdefines.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/boxpackets.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/fielddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/fieldencode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/protogenglue.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/scaleddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/scaledencode.c 

OBJS += \
./Src/protocol/boxdefines.o \
./Src/protocol/boxpackets.o \
./Src/protocol/fielddecode.o \
./Src/protocol/fieldencode.o \
./Src/protocol/protogenglue.o \
./Src/protocol/scaleddecode.o \
./Src/protocol/scaledencode.o 

C_DEPS += \
./Src/protocol/boxdefines.d \
./Src/protocol/boxpackets.d \
./Src/protocol/fielddecode.d \
./Src/protocol/fieldencode.d \
./Src/protocol/protogenglue.d \
./Src/protocol/scaleddecode.d \
./Src/protocol/scaledencode.d 


# Each subdirectory must supply rules for building sources it contributes
Src/protocol/boxdefines.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/boxdefines.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/boxdefines.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/boxpackets.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/boxpackets.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/boxpackets.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/fielddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/fielddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/fielddecode.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/fieldencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/fieldencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/fieldencode.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/protogenglue.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/protogenglue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/protogenglue.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/scaleddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/scaleddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/scaleddecode.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/protocol/scaledencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/protocol/scaledencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F302x8 -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/ILI9340" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/common" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/Firmware/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Src/protocol/scaledencode.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


