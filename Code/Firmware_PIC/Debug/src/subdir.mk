################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ILI9340.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/ILI9340_font.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/bitfieldspecial.c \
../src/box_usb.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxdefines.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxpackets.c \
../src/cr_startup_lpc15xx.c \
../src/display.c \
../src/ext_eeprom.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fielddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fieldencode.c \
../src/gps.c \
../src/hid_desc.c \
../src/hid_generic.c \
../src/hid_main.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/protogenglue.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaleddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaledencode.c \
../src/spi.c \
../src/sysinit.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c \
../src/waypoints.c 

OBJS += \
./src/ILI9340.o \
./src/ILI9340_font.o \
./src/bitfieldspecial.o \
./src/box_usb.o \
./src/boxdefines.o \
./src/boxpackets.o \
./src/cr_startup_lpc15xx.o \
./src/display.o \
./src/ext_eeprom.o \
./src/fielddecode.o \
./src/fieldencode.o \
./src/gps.o \
./src/hid_desc.o \
./src/hid_generic.o \
./src/hid_main.o \
./src/protogenglue.o \
./src/scaleddecode.o \
./src/scaledencode.o \
./src/spi.o \
./src/sysinit.o \
./src/waypoint.o \
./src/waypoints.o 

C_DEPS += \
./src/ILI9340.d \
./src/ILI9340_font.d \
./src/bitfieldspecial.d \
./src/box_usb.d \
./src/boxdefines.d \
./src/boxpackets.d \
./src/cr_startup_lpc15xx.d \
./src/display.d \
./src/ext_eeprom.d \
./src/fielddecode.d \
./src/fieldencode.d \
./src/gps.d \
./src/hid_desc.d \
./src/hid_generic.d \
./src/hid_main.d \
./src/protogenglue.d \
./src/scaleddecode.d \
./src/scaledencode.d \
./src/spi.d \
./src/sysinit.d \
./src/waypoint.d \
./src/waypoints.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ILI9340_font.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/ILI9340_font.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/ILI9340_font.d" -MT"src/ILI9340_font.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bitfieldspecial.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/bitfieldspecial.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/bitfieldspecial.d" -MT"src/bitfieldspecial.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/boxdefines.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxdefines.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/boxdefines.d" -MT"src/boxdefines.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/boxpackets.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxpackets.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/boxpackets.d" -MT"src/boxpackets.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fielddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fielddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/fielddecode.d" -MT"src/fielddecode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fieldencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fieldencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/fieldencode.d" -MT"src/fieldencode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/protogenglue.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/protogenglue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/protogenglue.d" -MT"src/protogenglue.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/scaleddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaleddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/scaleddecode.d" -MT"src/scaleddecode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/scaledencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaledencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/scaledencode.d" -MT"src/scaledencode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/waypoint.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\Firmware\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -I"../../common" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"src/waypoint.d" -MT"src/waypoint.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


