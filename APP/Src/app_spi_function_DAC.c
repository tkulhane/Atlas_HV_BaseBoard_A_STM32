/*
 * app_spi_function.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#include "app_spi_function_DAC.h"

/* @brief send command to DAC and save value into backup restore register
 *
 * @param adr   -> DAC register address
 * @param value -> value to write in DAC register
 * @param rw    -> read/write bit
 *
 */
void SendCommandToDAC(uint8_t adr, uint16_t value,  bool rw)
{

	uint8_t data[3];

	data[2] = value & (0x00FF);
	data[1] = value >> 8;
	data[0] = (adr & 0x0F) | (rw << 7);

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, data, sizeof(data),10);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}


/* @brief send value to DAC
 *
 * @param dac_channel -> DAC output channel
 * @param value       -> value to write in DAC output register
 *
 */
void SendValueToDAC(uint8_t dac_channel, uint16_t value)
{

	uint8_t data[3];

	data[2] = value & 0x000F;
	data[1] = value >> 4;
	data[0] = (dac_channel & 0x07) | (1 << 3) | (0 << 7);

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, data, sizeof(data),10);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

}



/* @brief DAC initialization
 *
 */
void DAC_Init()
{
	SendCommandToDAC(0, 0, 0); //dummy command
	SendCommandToDAC(5, 0xA, 0); //reset up
	SendCommandToDAC(5, 0, 0); //reset down
	SendCommandToDAC(2, 0, 0); //sync register -> all 0
	SendCommandToDAC(3, 0, 0); //config register -> all 0
	SendCommandToDAC(4, 0 | (1 << 8)  , 0); //gain register -> reference diveded by 2

	for(int i = 0; i < 8; i++)
	{
		SendValueToDAC(i, 4095); // set all DAC channels on maximum value -> minimum output voltage of power supply
	}

}


