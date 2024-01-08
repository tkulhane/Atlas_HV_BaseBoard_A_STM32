################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.c 

OBJS += \
./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.o 

C_DEPS += \
./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/ioLibrary_Driver-master/Ethernet/W5200/%.o LIB/ioLibrary_Driver-master/Ethernet/W5200/%.su LIB/ioLibrary_Driver-master/Ethernet/W5200/%.cyclo: ../LIB/ioLibrary_Driver-master/Ethernet/W5200/%.c LIB/ioLibrary_Driver-master/Ethernet/W5200/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Inc" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Src" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Application" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Ethernet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DHCP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DNS" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/httpServer" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/MQTT" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNMP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNTP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/TFTP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Ethernet-2f-W5200

clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Ethernet-2f-W5200:
	-$(RM) ./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.cyclo ./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.d ./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.o ./LIB/ioLibrary_Driver-master/Ethernet/W5200/w5200.su

.PHONY: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Ethernet-2f-W5200

