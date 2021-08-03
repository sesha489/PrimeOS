################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Custom_Lib.c \
../src/EventHandlers.c \
../src/FAT16.c \
../src/Font.c \
../src/SDC.c \
../src/TFT.c \
../src/syscalls.c \
../src/system_stm32f7xx.c 

CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/Custom_Lib.o \
./src/EventHandlers.o \
./src/FAT16.o \
./src/Font.o \
./src/SDC.o \
./src/TFT.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f7xx.o 

C_DEPS += \
./src/Custom_Lib.d \
./src/EventHandlers.d \
./src/FAT16.d \
./src/Font.d \
./src/SDC.d \
./src/TFT.d \
./src/syscalls.d \
./src/system_stm32f7xx.d 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DSTM32 -DSTM32F7 -DSTM32F767ZITx -DNUCLEO_F767ZI -DDEBUG -DSTM32F767xx -I"D:/SelfProjects/STM32/PrimOS/inc" -I"D:/SelfProjects/STM32/PrimOS/CMSIS/device" -I"D:/SelfProjects/STM32/PrimOS/CMSIS/core" -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DSTM32 -DSTM32F7 -DSTM32F767ZITx -DNUCLEO_F767ZI -DDEBUG -DSTM32F767xx -I"D:/SelfProjects/STM32/PrimOS/inc" -I"D:/SelfProjects/STM32/PrimOS/CMSIS/device" -I"D:/SelfProjects/STM32/PrimOS/CMSIS/core" -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


