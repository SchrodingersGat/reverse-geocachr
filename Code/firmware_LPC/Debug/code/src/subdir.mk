################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/src/ILI9340.c \
../code/src/box_usb.c \
../code/src/cr_startup_lpc11xx.c \
../code/src/display.c \
../code/src/gps.c \
../code/src/hid_desc.c \
../code/src/hid_generic.c \
../code/src/hid_main.c \
../code/src/spi.c \
../code/src/sysinit.c \
../code/src/waypoints.c 

OBJS += \
./code/src/ILI9340.o \
./code/src/box_usb.o \
./code/src/cr_startup_lpc11xx.o \
./code/src/display.o \
./code/src/gps.o \
./code/src/hid_desc.o \
./code/src/hid_generic.o \
./code/src/hid_main.o \
./code/src/spi.o \
./code/src/sysinit.o \
./code/src/waypoints.o 

C_DEPS += \
./code/src/ILI9340.d \
./code/src/box_usb.d \
./code/src/cr_startup_lpc11xx.d \
./code/src/display.d \
./code/src/gps.d \
./code/src/hid_desc.d \
./code/src/hid_generic.d \
./code/src/hid_main.d \
./code/src/spi.d \
./code/src/sysinit.d \
./code/src/waypoints.d 


# Each subdirectory must supply rules for building sources it contributes
code/src/%.o: ../code/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/src/cr_startup_lpc11xx.o: ../code/src/cr_startup_lpc11xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"code/src/cr_startup_lpc11xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


