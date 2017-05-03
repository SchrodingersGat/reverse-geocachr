################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ILI9340.c \
../src/ILI9340_font.c \
../src/box_messages.c \
../src/cr_startup_lpc15xx.c \
../src/display.c \
../src/ext_eeprom.c \
../src/gps.c \
../src/hid_desc.c \
../src/hid_generic.c \
../src/hid_main.c \
../src/spi.c \
../src/sysinit.c \
../src/waypoint.c \
../src/waypoints.c 

OBJS += \
./src/ILI9340.o \
./src/ILI9340_font.o \
./src/box_messages.o \
./src/cr_startup_lpc15xx.o \
./src/display.o \
./src/ext_eeprom.o \
./src/gps.o \
./src/hid_desc.o \
./src/hid_generic.o \
./src/hid_main.o \
./src/spi.o \
./src/sysinit.o \
./src/waypoint.o \
./src/waypoints.o 

C_DEPS += \
./src/ILI9340.d \
./src/ILI9340_font.d \
./src/box_messages.d \
./src/cr_startup_lpc15xx.d \
./src/display.d \
./src/ext_eeprom.d \
./src/gps.d \
./src/hid_desc.d \
./src/hid_generic.d \
./src/hid_main.d \
./src/spi.d \
./src/sysinit.d \
./src/waypoint.d \
./src/waypoints.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DNDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\LPCworkspace\lpc_chip_15xx\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Oliver\Google Drive\Reverse GeoCache Box\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_15xx\inc\usbd" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


