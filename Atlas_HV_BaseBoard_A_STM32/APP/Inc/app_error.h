/*
 * app_error.h
 *
 *  Created on: Feb 19, 2022
 *      Author: tomas
 */

#ifndef INC_APP_ERROR_H_
#define INC_APP_ERROR_H_

#include "main.h"
#include "app_spi_function_DAC.h"
#include "app_gpio_function.h"
#include "app_main_function.h"
#include "app_usart_process.h"
#include "app_communication.h"

#define Error_Array_Size 20
#define Error_Threshold 16
uint8_t Error_Array_Reg[Error_Array_Size];
uint8_t Error_Array_Counter;

bool *p_ERROR_data[6];
bool _Found_Error;

void ErrorExecute(uint8_t channel);
void ErrorProcess();
void ErrorSignalsRead();

#endif /* INC_APP_ERROR_H_ */
