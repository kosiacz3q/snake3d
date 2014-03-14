################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Brick.cpp \
../src/BrickProperties.cpp \
../src/Camera.cpp \
../src/Gainer.cpp \
../src/Game.cpp \
../src/GameStateManager.cpp \
../src/IMessager.cpp \
../src/MM.cpp \
../src/MainBrick.cpp \
../src/MapObject.cpp \
../src/Menu.cpp \
../src/MessagePack.cpp \
../src/MouseHandler.cpp \
../src/Object.cpp \
../src/Obstacle.cpp \
../src/RandomPositionGenerator.cpp \
../src/RotaryCounter.cpp \
../src/ShapeGenerator.cpp \
../src/SnakeAbilities.cpp \
../src/SnakeBody.cpp \
../src/StringHandler.cpp \
../src/Texture.cpp \
../src/Vectorf.cpp \
../src/main.cpp 

OBJS += \
./src/Brick.o \
./src/BrickProperties.o \
./src/Camera.o \
./src/Gainer.o \
./src/Game.o \
./src/GameStateManager.o \
./src/IMessager.o \
./src/MM.o \
./src/MainBrick.o \
./src/MapObject.o \
./src/Menu.o \
./src/MessagePack.o \
./src/MouseHandler.o \
./src/Object.o \
./src/Obstacle.o \
./src/RandomPositionGenerator.o \
./src/RotaryCounter.o \
./src/ShapeGenerator.o \
./src/SnakeAbilities.o \
./src/SnakeBody.o \
./src/StringHandler.o \
./src/Texture.o \
./src/Vectorf.o \
./src/main.o 

CPP_DEPS += \
./src/Brick.d \
./src/BrickProperties.d \
./src/Camera.d \
./src/Gainer.d \
./src/Game.d \
./src/GameStateManager.d \
./src/IMessager.d \
./src/MM.d \
./src/MainBrick.d \
./src/MapObject.d \
./src/Menu.d \
./src/MessagePack.d \
./src/MouseHandler.d \
./src/Object.d \
./src/Obstacle.d \
./src/RandomPositionGenerator.d \
./src/RotaryCounter.d \
./src/ShapeGenerator.d \
./src/SnakeAbilities.d \
./src/SnakeBody.d \
./src/StringHandler.d \
./src/Texture.d \
./src/Vectorf.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


