################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/subdir.mk
-include lwip/contrib/apps/udpecho/subdir.mk
-include lwip/contrib/apps/tcpecho/subdir.mk
-include freertos/source/subdir.mk
-include freertos/portable/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
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
all: Practica2_freeRTOS.axf

# Tool invocations
Practica2_freeRTOS.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -print-memory-usage -Xlinker --gc-sections -Xlinker -Map="Practica2_freeRTOS.map" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T "Practica2_freeRTOS_Debug.ld" -o "Practica2_freeRTOS.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Practica2_freeRTOS.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Practica2_freeRTOS.axf"; # arm-none-eabi-objcopy -v -O binary "Practica2_freeRTOS.axf" "Practica2_freeRTOS.bin" ; # checksum -p MK64FN1M0xxx12 -d "Practica2_freeRTOS.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
