/*
 * app_spi_function_ADC.h
 *
 *  Created on: 13. 2. 2022
 *      Author: tomas
 */

#ifndef INC_APP_FUNCTION_ADC_H_
#define INC_APP_FUNCTION_ADC_H_

#include "main.h"
#include "spi.h"
#include "app_main_function.h"
#include "app_backup_sram.h"

#define meas_size 5

extern float *p_ADC_data[8];

void ReadADCChannels();
void ADCStore();
void LoadADCConstant();
void StoreADCConstant(uint8_t coef, float value);
float GetADCConstant(uint8_t coef);
void SendADCCoefficients();


#endif /* INC_APP_FUNCTION_ADC_H_ */
