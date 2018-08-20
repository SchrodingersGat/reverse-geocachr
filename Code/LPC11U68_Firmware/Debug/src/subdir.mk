################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/box_usb.c \
../src/checksum.c \
../src/cr_startup_lpc11u6x.c \
../src/crp.c \
../src/eemem.c \
../src/hid_desc.c \
../src/hid_generic.c \
../src/hid_main.c \
../src/mtb.c \
../src/sysinit.c \
../src/timer.c \
../src/waypoints.c 

OBJS += \
./src/box_usb.o \
./src/checksum.o \
./src/cr_startup_lpc11u6x.o \
./src/crp.o \
./src/eemem.o \
./src/hid_desc.o \
./src/hid_generic.o \
./src/hid_main.o \
./src/mtb.o \
./src/sysinit.o \
./src/timer.o \
./src/waypoints.o 

C_DEPS += \
./src/box_usb.d \
./src/checksum.d \
./src/cr_startup_lpc11u6x.d \
./src/crp.d \
./src/eemem.d \
./src/hid_desc.d \
./src/hid_generic.d \
./src/hid_main.d \
./src/mtb.d \
./src/sysinit.d \
./src/timer.d \
./src/waypoints.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -D__MTB_BUFFER_SIZE=256 -DCORE_M0PLUS -D__USE_ROMDIVIDE -I"C:\Users\Oliver\Documents\MCUXpressoIDE_10.2.0_759\workspace\lpc_chip_11u6x\inc" -I"C:\Users\Oliver\Documents\MCUXpressoIDE_10.2.0_759\workspace\lpc_board_nxp_lpcxpresso_11u68\inc" -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\LPC11U68_Firmware\src" -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\LPC11U68_Firmware\inc" -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\LPC11U68_Firmware\inc\usbd" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/LPC11U68_Firmware\..\protocol" -I"C:/Users/Oliver/Programming/Reverse GeoCache Box/Code/LPC11U68_Firmware\..\common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


