/*
 * app_spi_function_ADC.c
 *
 *  Created on: 13. 2. 2022
 *      Author: tomas
 */

#include "app_function_ADC.h"

#define ADC_coef 1241.58836

uint16_t meas_data[8][meas_size];
uint8_t meas_counter;
uint8_t Read_Data[16]; //read data from ADC

float *p_ADC_data[8];


//ADC address array
uint8_t Adresses[16] =
{
		0,
		1 << 3,
		0,
		2 << 3,
		0,
		3 << 3,
		0,
		4 << 3,
		0,
		5 << 3,
		0,
		6 << 3,
		0,
		7 << 3,
		0,
		0 << 3

};

/* @brief get K coeficient for ADC
 *
 *	@channel -> adc channel
 */
float GetCoef_k(int channel)
{
	float *addr = ((float *)&MainParams.ReadCoef_k_0) + channel;//  + (4 * channel);
	return *addr;
}

/* @brief get Q coeficient for ADC
 *
 *	@channel -> adc channel
 */
float GetCoef_q(int channel)
{
	float *addr =((float *)&MainParams.ReadCoef_q_0) + channel;//  + (4 * channel);
	return *addr;
}

/* @brief store coefficient to sram
 *
 * @param coef  -> coefficient order, k: 0 to 5, q: 6 to 11
 * @param value -> value of coefficient
 *
 *
 */
void StoreADCConstant(uint8_t coef, float value)
{
	float *addr = ((float *)&MainParams.ReadCoef_k_0) + coef;//  + (4 * channel);
	*addr = value;
}

/* @brief send ADC coefficients to communication
 *
 *
 */
void SendADCCoefficients()
{
	for(int i = 0;i<12;i++)
	{
		SendCommunication_float(cmd_adc_get_k0 + i,GetCoef_k(i));
	}
}


/* @brief calculate of array values average
 *
 * @param array  -> pointer on array
 * @param length -> length of array
 *
 * @return average of array
 *
 */
uint16_t CalcAvg(uint16_t *array, uint16_t length)
{
	uint32_t AVG = 0;

	for(int i = 0; i<length ; i++)
	{
		AVG += array[i];
	}

	return (AVG/length);
}

/* @brief calculate voltage or current from ADC value and coefficients
 *
 * @param channel -> ADC channel (0,1,2 - voltage; 3,4,5 - current)
 * @param value -> ADC data
 *
 * @return voltage or current (float)
 */
float CalcAdcValue(uint8_t channel,uint16_t value)
{
	float f = (float)value/ADC_coef;

	float Coef_k = GetCoef_k(channel);
	float Coef_q = GetCoef_q(channel);


	f = (f - Coef_q) / Coef_k;

	return f;
}

/* @brief read all ADC channels
 *
 *	data save to Read_Data
 *
 */
void ReadADCChannels()
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, Adresses, Read_Data, 8,2);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}

/* @brief save data to average buffer and processed average buffer
 *
 *	processed data (measurement average) are saved on selected addresses in p_ADC_data array
 *
 */
void ADCStore()
{
	//save data from ADC data read buffer
	for(int i = 0;i<8;i++)
	{
		meas_data[i][meas_counter] = 0 | Read_Data[2*i] | (Read_Data[(2*i)+1] << 8);
	}

	meas_counter++;

	//all buffers full - calculate average and store on selected addresses
	if(meas_counter > (meas_size - 1))
	{
		meas_counter = 0;

		uint16_t avg[8];
		for(int i = 0; i < 8 ;i++)
		{
			avg[i] = CalcAvg(meas_data[i], meas_size); //calculate average
		}

		for(int i = 0; i<6;i++)
		{
			*p_ADC_data[i] = CalcAdcValue(i,avg[i]); //calculate value(voltage or current and saved on selected addresses)
		}

		//voltageRegulator(0);
		//AdaptiveVoltageTune(0);

	}
}



