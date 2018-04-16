################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ArduinoUart.cpp \
../PhotonCounter.cpp \
../PhotonCountingExpt.cpp 

CPP_DEPS += \
./ArduinoUart.cpp.d \
./PhotonCounter.cpp.d \
./PhotonCountingExpt.cpp.d 

LINK_OBJ += \
./ArduinoUart.cpp.o \
./PhotonCounter.cpp.o \
./PhotonCountingExpt.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
ArduinoUart.cpp.o: ../ArduinoUart.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

PhotonCounter.cpp.o: ../PhotonCounter.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

PhotonCountingExpt.cpp.o: ../PhotonCountingExpt.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


