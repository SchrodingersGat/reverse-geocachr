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
all: ReverseGeocacheLPC11U68.axf

# Tool invocations
ReverseGeocacheLPC11U68.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Oliver\Documents\MCUXpressoIDE_10.2.0_759\workspace\lpc_chip_11u6x\Debug" -L"C:\Users\Oliver\Documents\MCUXpressoIDE_10.2.0_759\workspace\lpc_board_nxp_lpcxpresso_11u68\Debug" -Xlinker -Map="ReverseGeocacheLPC11U68.map" -Xlinker --gc-sections -Xlinker --allow-multiple-definition -mcpu=cortex-m0 -mthumb -T "ReverseGeocacheLPC11U68_Debug.ld" -u _printf_float -u _scanf_float -o "ReverseGeocacheLPC11U68.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ReverseGeocacheLPC11U68.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ReverseGeocacheLPC11U68.axf"; # arm-none-eabi-objcopy -O binary "ReverseGeocacheLPC11U68.axf" "ReverseGeocacheLPC11U68.bin" ; checksum -p LPC11U68 -d "ReverseGeocacheLPC11U68.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
