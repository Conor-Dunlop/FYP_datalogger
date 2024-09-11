################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SX1262/src/lr_fhss_mac.c \
../Drivers/SX1262/src/sx126x.c \
../Drivers/SX1262/src/sx126x_driver_version.c \
../Drivers/SX1262/src/sx126x_lr_fhss.c 

OBJS += \
./Drivers/SX1262/src/lr_fhss_mac.o \
./Drivers/SX1262/src/sx126x.o \
./Drivers/SX1262/src/sx126x_driver_version.o \
./Drivers/SX1262/src/sx126x_lr_fhss.o 

C_DEPS += \
./Drivers/SX1262/src/lr_fhss_mac.d \
./Drivers/SX1262/src/sx126x.d \
./Drivers/SX1262/src/sx126x_driver_version.d \
./Drivers/SX1262/src/sx126x_lr_fhss.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SX1262/src/%.o Drivers/SX1262/src/%.su Drivers/SX1262/src/%.cyclo: ../Drivers/SX1262/src/%.c Drivers/SX1262/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/SX1262/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SX1262-2f-src

clean-Drivers-2f-SX1262-2f-src:
	-$(RM) ./Drivers/SX1262/src/lr_fhss_mac.cyclo ./Drivers/SX1262/src/lr_fhss_mac.d ./Drivers/SX1262/src/lr_fhss_mac.o ./Drivers/SX1262/src/lr_fhss_mac.su ./Drivers/SX1262/src/sx126x.cyclo ./Drivers/SX1262/src/sx126x.d ./Drivers/SX1262/src/sx126x.o ./Drivers/SX1262/src/sx126x.su ./Drivers/SX1262/src/sx126x_driver_version.cyclo ./Drivers/SX1262/src/sx126x_driver_version.d ./Drivers/SX1262/src/sx126x_driver_version.o ./Drivers/SX1262/src/sx126x_driver_version.su ./Drivers/SX1262/src/sx126x_lr_fhss.cyclo ./Drivers/SX1262/src/sx126x_lr_fhss.d ./Drivers/SX1262/src/sx126x_lr_fhss.o ./Drivers/SX1262/src/sx126x_lr_fhss.su

.PHONY: clean-Drivers-2f-SX1262-2f-src

