################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/%.o LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/%.su LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/%.cyclo: ../LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/%.c LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/APP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/APP/Inc" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/APP/Src" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Application" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Ethernet" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DHCP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DNS" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/httpServer" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/MQTT" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNMP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNTP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/TFTP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTFormat.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTPacket.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./LIB/ioLibrary_Driver-master/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-LIB-2f-ioLibrary_Driver-2d-master-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

