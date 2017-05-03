################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/ILI9340_font.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/bitfieldspecial.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxdefines.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxpackets.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fielddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fieldencode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/protogenglue.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaleddecode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaledencode.c \
C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c 

OBJS += \
./code/common/ILI9340_font.o \
./code/common/bitfieldspecial.o \
./code/common/boxdefines.o \
./code/common/boxpackets.o \
./code/common/fielddecode.o \
./code/common/fieldencode.o \
./code/common/protogenglue.o \
./code/common/scaleddecode.o \
./code/common/scaledencode.o \
./code/common/waypoint.o 

C_DEPS += \
./code/common/ILI9340_font.d \
./code/common/bitfieldspecial.d \
./code/common/boxdefines.d \
./code/common/boxpackets.d \
./code/common/fielddecode.d \
./code/common/fieldencode.d \
./code/common/protogenglue.d \
./code/common/scaleddecode.d \
./code/common/scaledencode.d \
./code/common/waypoint.d 


# Each subdirectory must supply rules for building sources it contributes
code/common/ILI9340_font.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/ILI9340_font.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/ILI9340_font.d" -MT"code/common/ILI9340_font.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/bitfieldspecial.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/bitfieldspecial.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/bitfieldspecial.d" -MT"code/common/bitfieldspecial.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/boxdefines.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxdefines.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/boxdefines.d" -MT"code/common/boxdefines.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/boxpackets.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/boxpackets.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/boxpackets.d" -MT"code/common/boxpackets.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/fielddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fielddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/fielddecode.d" -MT"code/common/fielddecode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/fieldencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/fieldencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/fieldencode.d" -MT"code/common/fieldencode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/protogenglue.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/protogenglue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/protogenglue.d" -MT"code/common/protogenglue.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/scaleddecode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaleddecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/scaleddecode.d" -MT"code/common/scaleddecode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/scaledencode.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/scaledencode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/scaledencode.d" -MT"code/common/scaledencode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/common/waypoint.o: C:/Users/Oliver/Programming/Reverse\ GeoCache\ Box/Code/common/waypoint.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0 -I../../common -I"C:\Users\Oliver\Programming\Reverse GeoCache Box\Code\firmware\code\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc" -I"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"code/common/waypoint.d" -MT"code/common/waypoint.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


