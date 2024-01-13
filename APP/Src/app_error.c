/*
 * app_error.c
 *
 *  Created on: Feb 19, 2022
 *      Author: tomas
 */


#include "app_error.h"
#include "app_params.h"
#include "app_leds.h"


uint8_t Error_Array_Reg[Error_Array_Size];
uint8_t Error_Array_Counter;

uint32_t ErrorTimer[6];

bool *p_ERROR_data[6];
bool _Found_Error;
bool _FoundError_OR;
bool _FoundErrorforEach[6];

bool _EnableErrorExecute;
bool _DisableSupplyInLostConnection;


/* @brief reaction on error signal
 *
 */
void ErrorExecute(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	//_Found_Error = false;

	//power good execution -> channel disable
	if(_FoundErrorforEach[channel])
	{
		//Channel_Enable(channel, false);

		if(MainParams.ErrorExecuteAutoRestore)
		{
			Channel_Restart(channel);
		}
		else
		{
			ChannelsStatus[channel].disableInError = true;
			Channel_Enable(channel, false);
		}


	}

	//over current execution -> output disable
	if(_FoundErrorforEach[channel + 3])
	{
		//Channel_Output(channel, false);
		/*
		if(_restart)
			Channel_Restart(channel);
		else
			Channel_Enable(channel, false);
			*/
	}

}


void ErrorSignalTime()
{

	_FoundError_OR = false;

	for(int i = 0; i < 6; i++)
	{
		if(*p_ERROR_data[i]) //error je 1
		{
			if((HAL_GetTick() - ErrorTimer[i]) > Error_Time)
			{
				_Found_Error = true;
				_FoundErrorforEach[i] = true;
			}
		}
		else
		{
			ErrorTimer[i] = HAL_GetTick();
			_FoundErrorforEach[i] = false;
		}


		if(_FoundErrorforEach[i])
		{
			_Found_Error = true;
		}

		_FoundError_OR = _FoundError_OR | _FoundErrorforEach[i];

	}

	//_FoundError_OR = _FoundErrorforEach[0] || _FoundErrorforEach[1] || _FoundErrorforEach[2];

}

void ErrorTimerReset(int channel)
{
	ErrorTimer[channel] = HAL_GetTick();
	ErrorTimer[channel+3 ] = HAL_GetTick();
}

/* @brief Process of error signals - count true bit (error signalization) in Error Array Register
 *  write to _Found_Error:
 *  	true -> found error
 *  	false -> non error
 */
void ErrorProcess()
{

	for(int errbit = 0; errbit < 6; errbit++)
	{
		int ee = 0;
		for(int i = 0; i < Error_Array_Size ; i++)
		{
			if(Error_Array_Reg[i] & (1 << errbit)) ee++;
		}

		if(ee >= Error_Threshold)
		{
			*p_ERROR_data[errbit] = true;
			//_Found_Error = true;
		}
		else
		{
			*p_ERROR_data[errbit] = false;
		}

	}
}


/* @brief Read error signals from power supply - power goods and over currents
 *
 * @return true -> found error, after process (after Error_Array_Size counts)
 * @return false -> non error
 */
void ErrorSignalsRead()
{

	uint8_t temp_error_reg = 0;
	
	if(ChannelsStatus[0].enable && !ChannelsChange[0].restart_request)
	{
		temp_error_reg |= (!((bool)HAL_GPIO_ReadPin(PG_1_GPIO_Port, PG_1_Pin)))  << 0;
		temp_error_reg |= ((bool)HAL_GPIO_ReadPin(OC_1_GPIO_Port, OC_1_Pin))  << 3;
	}

	if(ChannelsStatus[1].enable && !ChannelsChange[1].restart_request)
	{
		temp_error_reg |= (!((bool)HAL_GPIO_ReadPin(PG_2_GPIO_Port, PG_2_Pin)))  << 1;
		temp_error_reg |= ((bool)HAL_GPIO_ReadPin(OC_3_GPIO_Port, OC_2_Pin))  << 4;
	}

	if(ChannelsStatus[2].enable && !ChannelsChange[2].restart_request)
	{
		temp_error_reg |= (!((bool)HAL_GPIO_ReadPin(PG_3_GPIO_Port, PG_3_Pin)))  << 2;
		temp_error_reg |= ((bool)HAL_GPIO_ReadPin(OC_3_GPIO_Port, OC_3_Pin))  << 5;
	}



	Error_Array_Reg[Error_Array_Counter] = temp_error_reg;
	Error_Array_Counter++;
	if(Error_Array_Counter > (Error_Array_Size - 1))
	{
		Error_Array_Counter = 0;
		ErrorProcess();
	}
}


void AppConnectedExecute(bool AppConnected)
{
	//HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, AppConnected);


	if((AppConnected == false) && MainParams.DisableSupplyInLostConnection)
	{

		for(int i = 0; i< 3; i++)
		{
			Channel_Enable(i, false);
			Channel_Output(i, false);
		}

	}
}


