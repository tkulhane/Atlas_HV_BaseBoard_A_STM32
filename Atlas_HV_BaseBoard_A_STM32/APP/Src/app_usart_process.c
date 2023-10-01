/*
 * app_usart_process.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#include "app_usart_process.h"


#define uart_buffer_size 1024
uint8_t uart_buffer[uart_buffer_size];
uint16_t uart_wpointer = 0;
uint16_t uart_rpointer = 0;
uint16_t uart_bcounter = 0;

/* @brief Empty uart buffer (FIFO) signalization
 *
 * @return true -> FIFO is not empty
 * @return false -> FIFO is empty
 */
bool Uart_BufferNotEmpty()
{
	return (uart_bcounter > 0);
}

/* @brief Full uart buffer (FIFO) signalization
 *
 * @return true -> FIFO is not full
 * @return false -> FIFO is full
 */
bool Uart_BufferNotFull()
{
	return !(uart_bcounter >= (uart_buffer_size-1));
}

/* @brief function add data byte to FIFO
 *
 */
void Uart_WriteBuffer(uint8_t data)
{
	if(uart_bcounter >= (uart_buffer_size-1)) return;

	uart_buffer[uart_wpointer] = data;
	uart_bcounter++;
	uart_wpointer++;
	if(uart_wpointer > uart_buffer_size - 1) uart_wpointer = 0;

}

/* @brief read data byte from FIFO
 *
 * @return one element uint8_t data 
 */
uint8_t Uart_ReadBuffer()
{
	uint8_t data = uart_buffer[uart_rpointer];
	uart_bcounter--;
	uart_rpointer++;
	if(uart_rpointer > uart_buffer_size - 1) uart_rpointer = 0;

	return data;
}

/* @brief send message by uart
 *
 * @param data -> pointer on data buffer with message
 * @param size -> lenght of data buffer
 *
 */
void Uart_Send(char *data, uint16_t size)
{

	HAL_UART_Transmit(&huart2, (uint8_t *)data, size,100);
}
