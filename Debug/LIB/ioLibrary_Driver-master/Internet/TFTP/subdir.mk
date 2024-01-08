################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.c \
../LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.c 

OBJS += \
./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.o \
./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.o 

C_DEPS += \
./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.d \
./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/ioLibrary_Driver-master/Internet/TFTP/%.o LIB/ioLibrary_Driver-master/Internet/TFTP/%.su LIB/ioLibrary_Driver-master/Internet/TFTP/%.cyclo: ../LIB/ioLibrary_Driver-master/Internet/TFTP/%.c LIB/ioLibrary_Driver-master/Internet/TFTP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Inc" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Src" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Application" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Ethernet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DHCP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DNS" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/httpServer" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/MQTT" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNMP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNTP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/TFTP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-TFTP

clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-TFTP:
	-$(RM) ./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.cyclo ./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.d ./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.o ./LIB/ioLibrary_Driver-master/Internet/TFTP/netutil.su ./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.cyclo ./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.d ./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.o ./LIB/ioLibrary_Driver-master/Internet/TFTP/tftp.su

.PHONY: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-TFTP

