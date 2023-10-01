/*
 * app_usart_process.h
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#ifndef INC_APP_USART_PROCESS_H_
#define INC_APP_USART_PROCESS_H_


#include "main.h"

#include "app_spi_function_DAC.h"
#include "app_communication.h"
#include "usart.h"
#include "app_gpio_function.h"
#include "app_main_function.h"


void Uart_WriteBuffer(uint8_t data);
bool Uart_BufferNotEmpty();
uint8_t Uart_ReadBuffer();
void Uart_Send(char *data, uint16_t size);


#endif /* INC_APP_USART_PROCESS_H_ */
