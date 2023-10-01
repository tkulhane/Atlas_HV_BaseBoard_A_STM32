################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Src/app__mainloop.c \
../APP/Src/app_backup_sram.c \
../APP/Src/app_callback_function.c \
../APP/Src/app_communication.c \
../APP/Src/app_error.c \
../APP/Src/app_eth_process.c \
../APP/Src/app_function_ADC.c \
../APP/Src/app_gpio_function.c \
../APP/Src/app_main_function.c \
../APP/Src/app_spi_function_DAC.c \
../APP/Src/app_udp.c \
../APP/Src/app_usart_process.c 

OBJS += \
./APP/Src/app__mainloop.o \
./APP/Src/app_backup_sram.o \
./APP/Src/app_callback_function.o \
./APP/Src/app_communication.o \
./APP/Src/app_error.o \
./APP/Src/app_eth_process.o \
./APP/Src/app_function_ADC.o \
./APP/Src/app_gpio_function.o \
./APP/Src/app_main_function.o \
./APP/Src/app_spi_function_DAC.o \
./APP/Src/app_udp.o \
./APP/Src/app_usart_process.o 

C_DEPS += \
./APP/Src/app__mainloop.d \
./APP/Src/app_backup_sram.d \
./APP/Src/app_callback_function.d \
./APP/Src/app_communication.d \
./APP/Src/app_error.d \
./APP/Src/app_eth_process.d \
./APP/Src/app_function_ADC.d \
./APP/Src/app_gpio_function.d \
./APP/Src/app_main_function.d \
./APP/Src/app_spi_function_DAC.d \
./APP/Src/app_udp.d \
./APP/Src/app_usart_process.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Src/%.o APP/Src/%.su APP/Src/%.cyclo: ../APP/Src/%.c APP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/APP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/APP/Inc" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/APP/Src" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Application" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Ethernet" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DHCP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/DNS" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/FTPClient" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/FTPServer" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/httpServer" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/MQTT" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNMP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/SNTP" -I"/Users/tomas/Documents/_temp_STM32/Atlas_HV_BaseBoard_A_STM32/Atlas_HV_BaseBoard_A_STM32/LIB/ioLibrary_Driver-master/Internet/TFTP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-APP-2f-Src

clean-APP-2f-Src:
	-$(RM) ./APP/Src/app__mainloop.cyclo ./APP/Src/app__mainloop.d ./APP/Src/app__mainloop.o ./APP/Src/app__mainloop.su ./APP/Src/app_backup_sram.cyclo ./APP/Src/app_backup_sram.d ./APP/Src/app_backup_sram.o ./APP/Src/app_backup_sram.su ./APP/Src/app_callback_function.cyclo ./APP/Src/app_callback_function.d ./APP/Src/app_callback_function.o ./APP/Src/app_callback_function.su ./APP/Src/app_communication.cyclo ./APP/Src/app_communication.d ./APP/Src/app_communication.o ./APP/Src/app_communication.su ./APP/Src/app_error.cyclo ./APP/Src/app_error.d ./APP/Src/app_error.o ./APP/Src/app_error.su ./APP/Src/app_eth_process.cyclo ./APP/Src/app_eth_process.d ./APP/Src/app_eth_process.o ./APP/Src/app_eth_process.su ./APP/Src/app_function_ADC.cyclo ./APP/Src/app_function_ADC.d ./APP/Src/app_function_ADC.o ./APP/Src/app_function_ADC.su ./APP/Src/app_gpio_function.cyclo ./APP/Src/app_gpio_function.d ./APP/Src/app_gpio_function.o ./APP/Src/app_gpio_function.su ./APP/Src/app_main_function.cyclo ./APP/Src/app_main_function.d ./APP/Src/app_main_function.o ./APP/Src/app_main_function.su ./APP/Src/app_spi_function_DAC.cyclo ./APP/Src/app_spi_function_DAC.d ./APP/Src/app_spi_function_DAC.o ./APP/Src/app_spi_function_DAC.su ./APP/Src/app_udp.cyclo ./APP/Src/app_udp.d ./APP/Src/app_udp.o ./APP/Src/app_udp.su ./APP/Src/app_usart_process.cyclo ./APP/Src/app_usart_process.d ./APP/Src/app_usart_process.o ./APP/Src/app_usart_process.su

.PHONY: clean-APP-2f-Src

