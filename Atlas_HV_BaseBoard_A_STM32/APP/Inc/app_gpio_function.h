/*
 * app_gpio_function.h
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#ifndef INC_APP_GPIO_FUNCTION_H_
#define INC_APP_GPIO_FUNCTION_H_


#include "main.h"

#include "app_spi_function_DAC.h"
#include "app_main_function.h"
#include "app_usart_process.h"

void LedSwitch(int value);
void Enable_GPIO(uint8_t channel, bool value);
void Output_GPIO(uint8_t channel, bool relay_p, bool relay_n);

#endif /* INC_APP_GPIO_FUNCTION_H_ */
