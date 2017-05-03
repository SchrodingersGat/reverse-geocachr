################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/ILI9340.c \
../example/src/ILI9340_font.c \
../example/src/box_messages.c \
../example/src/cr_startup_lpc15xx.c \
../example/src/display.c \
../example/src/gps.c \
../example/src/hid_desc.c \
../example/src/hid_generic.c \
../example/src/hid_main.c \
../example/src/spi.c \
../example/src/sysinit.c \
../example/src/waypoint.c 

OBJS += \
./example/src/ILI9340.o \
./example/src/ILI9340_font.o \
./example/src/box_messages.o \
./example/src/cr_startup_lpc15xx.o \
./example/src/display.o \
./example/src/gps.o \
./example/src/hid_desc.o \
./example/src/hid_generic.o \
./example/src/hid_main.o \
./example/src/spi.o \
./example/src/sysinit.o \
./example/src/waypoint.o 

C_DEPS += \
./example/src/ILI9340.d \
./example/src/ILI9340_font.d \
./example/src/box_messages.d \
./example/src/cr_startup_lpc15xx.d \
./example/src/display.d \
./example/src/gps.d \
./example/src/hid_desc.d \
./example/src/hid_generic.d \
./example/src/hid_main.d \
./example/src/spi.d \
./example/src/sysinit.d \
./example/src/waypoint.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\LPCworkspace\lpc_chip_15xx\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Oliver\LPCworkspace\HID Test\example\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_15xx\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


