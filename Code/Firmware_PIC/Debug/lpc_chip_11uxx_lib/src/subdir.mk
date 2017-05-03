################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lpc_chip_11uxx_lib/src/adc_1125.c \
../lpc_chip_11uxx_lib/src/adc_11xx.c \
../lpc_chip_11uxx_lib/src/chip_11xx.c \
../lpc_chip_11uxx_lib/src/clock_11xx.c \
../lpc_chip_11uxx_lib/src/gpio_11xx_1.c \
../lpc_chip_11uxx_lib/src/gpio_11xx_2.c \
../lpc_chip_11uxx_lib/src/gpiogroup_11xx.c \
../lpc_chip_11uxx_lib/src/i2c_11xx.c \
../lpc_chip_11uxx_lib/src/iocon_11xx.c \
../lpc_chip_11uxx_lib/src/pinint_11xx.c \
../lpc_chip_11uxx_lib/src/pmu_11xx.c \
../lpc_chip_11uxx_lib/src/ring_buffer.c \
../lpc_chip_11uxx_lib/src/ssp_11xx.c \
../lpc_chip_11uxx_lib/src/sysctl_11xx.c \
../lpc_chip_11uxx_lib/src/sysinit_11xx.c \
../lpc_chip_11uxx_lib/src/timer_11xx.c \
../lpc_chip_11uxx_lib/src/uart_11xx.c \
../lpc_chip_11uxx_lib/src/wwdt_11xx.c 

OBJS += \
./lpc_chip_11uxx_lib/src/adc_1125.o \
./lpc_chip_11uxx_lib/src/adc_11xx.o \
./lpc_chip_11uxx_lib/src/chip_11xx.o \
./lpc_chip_11uxx_lib/src/clock_11xx.o \
./lpc_chip_11uxx_lib/src/gpio_11xx_1.o \
./lpc_chip_11uxx_lib/src/gpio_11xx_2.o \
./lpc_chip_11uxx_lib/src/gpiogroup_11xx.o \
./lpc_chip_11uxx_lib/src/i2c_11xx.o \
./lpc_chip_11uxx_lib/src/iocon_11xx.o \
./lpc_chip_11uxx_lib/src/pinint_11xx.o \
./lpc_chip_11uxx_lib/src/pmu_11xx.o \
./lpc_chip_11uxx_lib/src/ring_buffer.o \
./lpc_chip_11uxx_lib/src/ssp_11xx.o \
./lpc_chip_11uxx_lib/src/sysctl_11xx.o \
./lpc_chip_11uxx_lib/src/sysinit_11xx.o \
./lpc_chip_11uxx_lib/src/timer_11xx.o \
./lpc_chip_11uxx_lib/src/uart_11xx.o \
./lpc_chip_11uxx_lib/src/wwdt_11xx.o 

C_DEPS += \
./lpc_chip_11uxx_lib/src/adc_1125.d \
./lpc_chip_11uxx_lib/src/adc_11xx.d \
./lpc_chip_11uxx_lib/src/chip_11xx.d \
./lpc_chip_11uxx_lib/src/clock_11xx.d \
./lpc_chip_11uxx_lib/src/gpio_11xx_1.d \
./lpc_chip_11uxx_lib/src/gpio_11xx_2.d \
./lpc_chip_11uxx_lib/src/gpiogroup_11xx.d \
./lpc_chip_11uxx_lib/src/i2c_11xx.d \
./lpc_chip_11uxx_lib/src/iocon_11xx.d \
./lpc_chip_11uxx_lib/src/pinint_11xx.d \
./lpc_chip_11uxx_lib/src/pmu_11xx.d \
./lpc_chip_11uxx_lib/src/ring_buffer.d \
./lpc_chip_11uxx_lib/src/ssp_11xx.d \
./lpc_chip_11uxx_lib/src/sysctl_11xx.d \
./lpc_chip_11uxx_lib/src/sysinit_11xx.d \
./lpc_chip_11uxx_lib/src/timer_11xx.d \
./lpc_chip_11uxx_lib/src/uart_11xx.d \
./lpc_chip_11uxx_lib/src/wwdt_11xx.d 


# Each subdirectory must supply rules for building sources it contributes
lpc_chip_11uxx_lib/src/%.o: ../lpc_chip_11uxx_lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


