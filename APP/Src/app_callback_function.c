/*
 * app_callback_function.c
 *
 *  Created on: Mar 9, 2022
 *      Author: tomas
 */


#include "app_callback_function.h"


/* @brief callback of timer period elapsed -> for ADC measure and read error signals
 *
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if(htim == &htim10)
	{
		ReadADCChannels();
		ADCStore();
		ErrorSignalsRead();
	}
}
