/*
 * app_spi_function.h
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#ifndef INC_APP_SPI_FUNCTION_DAC_H_
#define INC_APP_SPI_FUNCTION_DAC_H_

#include "main.h"

#include "app_gpio_function.h"
#include "app_main_function.h"
#include "app_usart_process.h"
#include "spi.h"



void SendCommandToDAC(uint8_t adr, uint16_t value,  bool rw);
void SendValueToDAC(uint8_t dac_channel, uint16_t value);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi);
void DAC_Init();


#endif /* INC_APP_SPI_FUNCTION_DAC_H_ */
