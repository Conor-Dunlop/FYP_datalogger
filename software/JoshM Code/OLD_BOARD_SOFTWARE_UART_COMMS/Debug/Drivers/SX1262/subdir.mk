################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SX1262/lr_fhss_mac.c \
../Drivers/SX1262/sx126x.c \
../Drivers/SX1262/sx126x_driver_version.c \
../Drivers/SX1262/sx126x_hal.c \
../Drivers/SX1262/sx126x_lr_fhss.c 

OBJS += \
./Drivers/SX1262/lr_fhss_mac.o \
./Drivers/SX1262/sx126x.o \
./Drivers/SX1262/sx126x_driver_version.o \
./Drivers/SX1262/sx126x_hal.o \
./Drivers/SX1262/sx126x_lr_fhss.o 

C_DEPS += \
./Drivers/SX1262/lr_fhss_mac.d \
./Drivers/SX1262/sx126x.d \
./Drivers/SX1262/sx126x_driver_version.d \
./Drivers/SX1262/sx126x_hal.d \
./Drivers/SX1262/sx126x_lr_fhss.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SX1262/%.o Drivers/SX1262/%.su Drivers/SX1262/%.cyclo: ../Drivers/SX1262/%.c Drivers/SX1262/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SX1262

clean-Drivers-2f-SX1262:
	-$(RM) ./Drivers/SX1262/lr_fhss_mac.cyclo ./Drivers/SX1262/lr_fhss_mac.d ./Drivers/SX1262/lr_fhss_mac.o ./Drivers/SX1262/lr_fhss_mac.su ./Drivers/SX1262/sx126x.cyclo ./Drivers/SX1262/sx126x.d ./Drivers/SX1262/sx126x.o ./Drivers/SX1262/sx126x.su ./Drivers/SX1262/sx126x_driver_version.cyclo ./Drivers/SX1262/sx126x_driver_version.d ./Drivers/SX1262/sx126x_driver_version.o ./Drivers/SX1262/sx126x_driver_version.su ./Drivers/SX1262/sx126x_hal.cyclo ./Drivers/SX1262/sx126x_hal.d ./Drivers/SX1262/sx126x_hal.o ./Drivers/SX1262/sx126x_hal.su ./Drivers/SX1262/sx126x_lr_fhss.cyclo ./Drivers/SX1262/sx126x_lr_fhss.d ./Drivers/SX1262/sx126x_lr_fhss.o ./Drivers/SX1262/sx126x_lr_fhss.su

.PHONY: clean-Drivers-2f-SX1262

