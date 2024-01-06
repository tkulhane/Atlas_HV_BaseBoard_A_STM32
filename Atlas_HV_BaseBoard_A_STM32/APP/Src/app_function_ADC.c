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


float ReadCoef_k[6];
float ReadCoef_q[6];

//k coefficients for ADC channels
const float Default_ReadCoef_k[6] =
{
		0.00540804,
		0.00540804,
		0.00540804,
		0.06175469,
		0.06175469,
		0.06175469
};

//q coefficients for ADC channels
const float Default_ReadCoef_q[6] =
{
		0.09030197,
		0.09030197,
		0.09030197,
		0.06370294,
		0.06370294,
		0.06370294
};

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


float GetCoef_k(int channel)
{
	float f;
	uint32_t val = DefaultParams.sramOffset_ReadCoef_k_0 + 4*channel;
	memcpy(&f,&val,sizeof(f));

	return  f;
}


float GetCoef_q(int channel)
{
	float f;
	uint32_t val = DefaultParams.sramOffset_ReadCoef_q_0 + 4*channel;
	memcpy(&f,&val,sizeof(f));

	return  f;
}



/* @brief load coefficient from sram
 *
 */
void LoadADCConstant()
{
	for(int i = 0; i<6; i++)
	{

		if(BACKUP_SRAM_read_StoreControl(sramOffset_ReadCoef_k_0 + i))
		{
			ReadCoef_k[i] = BACKUP_SRAM_read_float(sramOffset_ReadCoef_k_0 + i);
		}
		else
		{
			ReadCoef_k[i] = Default_ReadCoef_k[i];
		}

		if(BACKUP_SRAM_read_StoreControl(sramOffset_ReadCoef_q_0 + i))
		{
			ReadCoef_q[i] = BACKUP_SRAM_read_float(sramOffset_ReadCoef_q_0 + i);
		}
		else
		{
			ReadCoef_q[i] = Default_ReadCoef_q[i];
		}

	}
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
	BACKUP_SRAM_write_float(sramOffset_ReadCoef_k_0 + coef, value);
	BACKUP_SRAM_write_StoreControl(sramOffset_ReadCoef_k_0 + coef, true);
}

/* @brief get coefficient from sram
 *
 * @param coef  -> coefficient order, k: 0 to 5, q: 6 to 11
 *
 */
float GetADCConstant(uint8_t coef)
{
	float f;

	if(BACKUP_SRAM_read_StoreControl(sramOffset_ReadCoef_k_0 + coef))
	{
		f = BACKUP_SRAM_read_float(sramOffset_ReadCoef_k_0 + coef);
	}
	else
	{
		if((coef >= 0) && (coef <= 5))
		{
			f = Default_ReadCoef_k[coef];
		}
		else if((coef >= 6) && (coef <= 11))
		{
			f = Default_ReadCoef_q[coef - 6];
		}

	}

	return f;
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

	}
}



