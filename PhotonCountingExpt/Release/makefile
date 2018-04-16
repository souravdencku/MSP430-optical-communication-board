################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include DataFlowLib/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/arduino.ar \

ELF += \
PhotonCountingExpt.elf \

EEP += \
PhotonCountingExpt.eep \

FLASH_IMAGE += \
PhotonCountingExpt.hex \


# All Target
all: PhotonCountingExpt

# Tool invocations
PhotonCountingExpt: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-size" -A "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-ar" rcs  "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

PhotonCountingExpt.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.elf"   $(LINK_OBJ) $(AR)  "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/arduino.ar" "-L/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

PhotonCountingExpt.eep: $(ELF)
	@echo 'Create eeprom image'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.elf" "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.eep"
	@echo 'Finished building: $@'
	@echo ' '

PhotonCountingExpt.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.elf" "/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/Release/PhotonCountingExpt.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_DEPS)$(AR)$(FLASH_IMAGE)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ELF)$(ASM_DEPS)$(CC_DEPS)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) PhotonCountingExpt
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
