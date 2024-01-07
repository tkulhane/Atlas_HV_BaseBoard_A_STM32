/*
 * app_usart_process.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#include "app_eth_process.h"


#define eth_buffer_size 4096
uint8_t eth_buffer[eth_buffer_size];
uint16_t eth_wpointer = 0;
uint16_t eth_rpointer = 0;
uint16_t eth_bcounter = 0;

/* @brief Empty ethernet buffer (FIFO) signalization
 *
 * @return true -> FIFO is not empty
 * @return false -> FIFO is empty
 */
bool ETH_BufferNotEmpty()
{
	return (eth_bcounter > 0);
}

/* @brief Full uart buffer (FIFO) signalization
 *
 * @return true -> FIFO is not full
 * @return false -> FIFO is full
 */
bool ETH_BufferNotFull()
{
	return !(eth_bcounter >= (eth_buffer_size-1));
}

/* @brief function add data byte to FIFO
 *
 */
void ETH_WriteBuffer(const uint8_t *Buffer, int length)
{
	for(int i = 0;i<length;i++)
	{
		if(eth_bcounter >= (eth_buffer_size-1)) return;

		eth_buffer[eth_wpointer] = Buffer[i];
		eth_bcounter++;
		eth_wpointer++;
		if(eth_wpointer > eth_buffer_size - 1) eth_wpointer = 0;
	}
}

/* @brief read data byty from FIFO
 *
 * @return one element uint8_t data 
 */
uint8_t ETH_ReadBuffer()
{
	uint8_t data = eth_buffer[eth_rpointer];
	eth_bcounter--;
	eth_rpointer++;
	if(eth_rpointer > eth_buffer_size - 1) eth_rpointer = 0;

	return data;
}

/* @brief send message by uart
 *
 * @param data -> pointer on data buffer with message
 * @param size -> lenght of data buffer
 *
 */
void ETH_Send(char *data, uint16_t size)
{
	ETH_udp_Transmit((uint8_t *)data,size);
}
