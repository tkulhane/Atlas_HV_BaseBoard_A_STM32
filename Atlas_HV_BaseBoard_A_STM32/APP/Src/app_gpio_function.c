/*
 * app_gpio_function.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#include "app_gpio_function.h"

/* @brief switch red led on nucleo board
 *
 */
void LedSwitch(int value)
{
	//HAL_GPIO_WritePin(LED_red_GPIO_Port, LED_red_Pin, value);
}

/* @brief controll of channel enable pin
 *
 * @param channel -> channel of power supply
 * @param value   -> enable-true, disable-false
 *
 */
void Enable_GPIO(uint8_t channel, bool value)
{
	switch(channel)
	{
		case 0:
			HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, value);
			break;

		case 1:
			HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, value);
			break;

		case 2:
			HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, value);
			break;

		default:
			break;

	}
}

/* @brief controll of channel otput polarity relay
 *
 * @param channel -> channel of power supply
 * @param relay_p   -> relay for positive polarity (direct relay)
 * @param relay_n   -> relay for negative polarity (reverse relay)
 *
 */
void Output_GPIO(uint8_t channel, bool relay_p, bool relay_n)
{
	if(relay_p && relay_n) return;

	switch(channel)
	{
		case 0:
			HAL_GPIO_WritePin(SWDIR_1_GPIO_Port, SWDIR_1_Pin, relay_p);
			HAL_GPIO_WritePin(SWREV_1_GPIO_Port, SWREV_1_Pin, relay_n);
			break;

		case 1:
			HAL_GPIO_WritePin(SWDIR_2_GPIO_Port, SWDIR_2_Pin, relay_p);
			HAL_GPIO_WritePin(SWREV_2_GPIO_Port, SWREV_2_Pin, relay_n);
			break;

		case 2:
			HAL_GPIO_WritePin(SWDIR_3_GPIO_Port, SWDIR_3_Pin, relay_p);
			HAL_GPIO_WritePin(SWREV_3_GPIO_Port, SWREV_3_Pin, relay_n);
			break;

		default:
			break;

	}
}
