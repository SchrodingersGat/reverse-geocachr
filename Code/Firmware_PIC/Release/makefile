################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Reverse\ Geocachr.axf

# Tool invocations
Reverse\ Geocachr.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Oliver\LPCworkspace\lpc_chip_15xx\Release" -L"C:\Users\Oliver\LPCworkspace\lpc_board_nxp_lpcxpresso_1549\Release" -Xlinker -Map="Reverse Geocachr.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Reverse_Geocachr_Release.ld" -o "Reverse Geocachr.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) "Reverse Geocachr.axf"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Reverse Geocachr.axf" ; arm-none-eabi-objcopy -v -O binary "Reverse Geocachr.axf" "Reverse Geocachr.bin" ; checksum -p LPC1549 -d "Reverse Geocachr.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
