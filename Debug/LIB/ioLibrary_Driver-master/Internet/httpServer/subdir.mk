################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.c \
../LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.c \
../LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.c 

OBJS += \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.o \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.o \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.o 

C_DEPS += \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.d \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.d \
./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/ioLibrary_Driver-master/Internet/httpServer/%.o LIB/ioLibrary_Driver-master/Internet/httpServer/%.su LIB/ioLibrary_Driver-master/Internet/httpServer/%.cyclo: ../LIB/ioLibrary_Driver-master/Internet/httpServer/%.c LIB/ioLibrary_Driver-master/Internet/httpServer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Inc" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/APP/Src" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Application" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Ethernet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DHCP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DNS" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/httpServer" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/MQTT" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNMP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNTP" -I"C:/CODE_temp/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/TFTP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-httpServer

clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-httpServer:
	-$(RM) ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.cyclo ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.d ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.o ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpParser.su ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.cyclo ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.d ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.o ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpServer.su ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.cyclo ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.d ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.o ./LIB/ioLibrary_Driver-master/Internet/httpServer/httpUtil.su

.PHONY: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-httpServer

