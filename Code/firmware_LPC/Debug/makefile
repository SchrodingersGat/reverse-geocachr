################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include code/src/subdir.mk
-include code/common/subdir.mk
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
all: ReverseGeocache.axf

# Tool invocations
ReverseGeocache.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Oliver\LPCworkspace\nxp_lpcxpresso_11u14_board_lib\Debug" -L"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\Debug" -L"C:\Users\Oliver\LPCworkspace\lpc_chip_11uxx_lib\libs" -Xlinker -Map="ReverseGeocache.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "nxp_lpcxpresso_11u14_usbd_lib_hid_generic_Debug.ld" -o "ReverseGeocache.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ReverseGeocache.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ReverseGeocache.axf" ; arm-none-eabi-objcopy -O binary "ReverseGeocache.axf" "ReverseGeocache.bin" ; checksum -p LPC11U24_301 -d "ReverseGeocache.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
