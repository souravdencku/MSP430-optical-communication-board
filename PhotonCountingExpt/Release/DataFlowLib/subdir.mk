################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataFlowLib/CircularQueue.cpp \
../DataFlowLib/Packet.cpp \
../DataFlowLib/PacketFactory.cpp \
../DataFlowLib/SerialDriver.cpp \
../DataFlowLib/dataflow_common.cpp 

CPP_DEPS += \
./DataFlowLib/CircularQueue.cpp.d \
./DataFlowLib/Packet.cpp.d \
./DataFlowLib/PacketFactory.cpp.d \
./DataFlowLib/SerialDriver.cpp.d \
./DataFlowLib/dataflow_common.cpp.d 

LINK_OBJ += \
./DataFlowLib/CircularQueue.cpp.o \
./DataFlowLib/Packet.cpp.o \
./DataFlowLib/PacketFactory.cpp.o \
./DataFlowLib/SerialDriver.cpp.o \
./DataFlowLib/dataflow_common.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
DataFlowLib/CircularQueue.cpp.o: ../DataFlowLib/CircularQueue.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

DataFlowLib/Packet.cpp.o: ../DataFlowLib/Packet.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

DataFlowLib/PacketFactory.cpp.o: ../DataFlowLib/PacketFactory.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

DataFlowLib/SerialDriver.cpp.o: ../DataFlowLib/SerialDriver.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

DataFlowLib/dataflow_common.cpp.o: ../DataFlowLib/dataflow_common.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=164 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR     -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/cores/arduino" -I"/home/jyothish/Documents/softwares/arduino-1.6.4/hardware/arduino/avr/variants/standard" -I"/home/jyothish/Desktop/jyothish_test/arduino_eclipse/PhotonCountingExpt/DataFlowLib" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


