################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gamestage/GameStage.cpp \
../src/gamestage/GameStageStaticWrapper.cpp \
../src/gamestage/GameStateManager.cpp \
../src/gamestage/StageDeathCause.cpp \
../src/gamestage/StageGame.cpp \
../src/gamestage/StageIntro.cpp \
../src/gamestage/StageMenu.cpp \
../src/gamestage/StageOutro.cpp 

OBJS += \
./src/gamestage/GameStage.o \
./src/gamestage/GameStageStaticWrapper.o \
./src/gamestage/GameStateManager.o \
./src/gamestage/StageDeathCause.o \
./src/gamestage/StageGame.o \
./src/gamestage/StageIntro.o \
./src/gamestage/StageMenu.o \
./src/gamestage/StageOutro.o 

CPP_DEPS += \
./src/gamestage/GameStage.d \
./src/gamestage/GameStageStaticWrapper.d \
./src/gamestage/GameStateManager.d \
./src/gamestage/StageDeathCause.d \
./src/gamestage/StageGame.d \
./src/gamestage/StageIntro.d \
./src/gamestage/StageMenu.d \
./src/gamestage/StageOutro.d 


# Each subdirectory must supply rules for building sources it contributes
src/gamestage/%.o: ../src/gamestage/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Dinterface=class -DSTATIC= -O2 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


