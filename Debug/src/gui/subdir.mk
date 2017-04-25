################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gui/FlickeringColor.cpp \
../src/gui/SelectableTexturedButton.cpp \
../src/gui/SelfStabilizingRotator.cpp \
../src/gui/StringDrawer.cpp \
../src/gui/TextInFrame.cpp 

OBJS += \
./src/gui/FlickeringColor.o \
./src/gui/SelectableTexturedButton.o \
./src/gui/SelfStabilizingRotator.o \
./src/gui/StringDrawer.o \
./src/gui/TextInFrame.o 

CPP_DEPS += \
./src/gui/FlickeringColor.d \
./src/gui/SelectableTexturedButton.d \
./src/gui/SelfStabilizingRotator.d \
./src/gui/StringDrawer.d \
./src/gui/TextInFrame.d 


# Each subdirectory must supply rules for building sources it contributes
src/gui/%.o: ../src/gui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Dinterface=class -DSTATIC= -O2 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


