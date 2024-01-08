/*
 * app_eth_process.h
 *
 *  Created on: 18. 3. 2022
 *      Author: tomas
 */

#ifndef INC_APP_ETH_PROCESS_H_
#define INC_APP_ETH_PROCESS_H_

#include "main.h"

#include "app_spi_function_DAC.h"
#include "app_communication.h"
#include "usart.h"
#include "app_gpio_function.h"
#include "app_main_function.h"
#include "app_udp.h"

bool ETH_BufferNotEmpty();
bool ETH_BufferNotFull();
void ETH_WriteBuffer(const uint8_t *Buffer, int legth);
uint8_t ETH_ReadBuffer();
void ETH_Send(char *data, uint16_t size);

#endif /* INC_APP_ETH_PROCESS_H_ */
