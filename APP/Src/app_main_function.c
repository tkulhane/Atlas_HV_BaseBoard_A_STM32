/*
 * app_main_function.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 *      ver.9
 */

#include "app_main_function.h"
#include "app_error.h"

#define DAC_coef 3276.8

#define PreReg_Coef_k 84.8727273
#define PreReg_Coef_q 127.8259425

#define Default_AdjCoef_k 511.8182426
#define Default_AdjCoef_q 655.2648273

//float AdjCoef_k[3];
//float AdjCoef_q[3];

ChannelStatusStruct ChannelsStatus[3];
ChannelChangeStruct ChannelsChange[3];

float AdaptiveDiff[3];
float addSetVoltage[3];
bool adaptiveVoltRequest[3];


//bool MainParams.ControlOutputWithChannelEnable;

/* @brief get K coeficient for DAC
 *
 *	@channel -> adc channel
 */
float GetDacCoef_k(int channel)
{
	float *addr = ((float *)&MainParams.AdjCoef_k_ch0) + channel;
	return *addr;
}

/* @brief get Q coeficient for DAC
 *
 *	@channel -> adc channel
 */
float GetDacCoef_q(int channel)
{
	float *addr = ((float *)&MainParams.AdjCoef_q_ch0) + channel;
	return *addr;
}

/* @brief store coefficient to sram
 *
 * @param coef  -> coefficient order, k: 0 to 5, q: 6 to 11
 * @param value -> value of coefficient
 *
 *
 */
void StoreDACConstant(uint8_t coef, float value)
{
	float *addr = ((float *)&MainParams.AdjCoef_k_ch0) + coef;//  + (4 * channel);
	*addr = value;
}

/* @brief send DAC coefficients to communication
 *
 *
 */
void SendDACCoefficients()
{
	for(int i = 0;i<6;i++)
	{
		SendCommunication_float(cmd_dac_get_k0 + i, GetDacCoef_k(i));
	}

}

/* @brief Calculation voltage for preregulator from recomended output voltage
 *
 * @param voltage -> request voltage on power supply output
 *
 * @return uint16_t value of voltage for pre regulator
 */
uint16_t Get_PreRegulatorVoltage(uint16_t voltage)
{
	return (0.15789 * (float)voltage) + 21.05263;
}

//Calculate DAC register value from recomended voltage
uint16_t Get_DACValue(int dac_channel, uint16_t value)
{
	uint16_t code;


	if(dac_channel == 0 || dac_channel == 1 || dac_channel == 2)
	{
		code = (uint16_t)(((PreReg_Coef_q - (float)value) / PreReg_Coef_k) * (float)DAC_coef);
	}
	else
	{
		float coef_k = GetDacCoef_k(dac_channel - 3);
		float coef_q = GetDacCoef_q(dac_channel - 3);

		code = (uint16_t)(((coef_q - (float)value) / coef_k) * (float)DAC_coef);
	}


	return code;
}

uint16_t Get_DACValue_F(int dac_channel, float value)
{
	uint16_t code;


	if(dac_channel == 0 || dac_channel == 1 || dac_channel == 2)
	{
		code = (uint16_t)(((PreReg_Coef_q - (float)value) / PreReg_Coef_k) * (float)DAC_coef);
	}
	else
	{
		float coef_k = GetDacCoef_k(dac_channel - 3);
		float coef_q = GetDacCoef_q(dac_channel - 3);

		code = (uint16_t)((((float)coef_q - (float)value) / coef_k) * (float)DAC_coef);
	}


	return code;
}

/* @brief Setting pre regulator output voltage
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param voltage -> request voltage on regulator output
 * 
 */
void Set_PreReg_Voltage(uint8_t channel, uint16_t voltage)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if((voltage < minimum_voltage) && (voltage > maximum_voltage)) return;

	uint16_t value = Get_DACValue(channel, voltage);
	SendValueToDAC(channel,value);
}

/* @brief Setting out regulator output voltage
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param voltage -> request voltage on regulator output
 * 
 */
void Set_OutReg_Voltage(uint8_t channel, uint16_t voltage)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if((voltage < minimum_voltage) && (voltage > maximum_voltage)) return;

	uint16_t value = Get_DACValue(channel + 3, voltage);
	SendValueToDAC(channel + 3, value);
}

void Set_OutReg_Voltage_F(uint8_t channel, float voltage)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if((voltage < minimum_voltage) && (voltage > maximum_voltage)) return;

	uint16_t value = Get_DACValue_F(channel + 3, voltage);
	SendValueToDAC(channel + 3, value);
}

/* @brief Setting voltage on pre and output regulator, call Set_PreReg_Voltage and Set_OutReg_Voltage function
 *        and voltage ramping at large difference
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param voltage -> request voltage on output of power supply channel
 * 
 */
void Set_Voltage(uint8_t channel, uint16_t voltage)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if((voltage < minimum_voltage) || (voltage > maximum_voltage)) return;

	ChannelsChange[channel].request_voltage = voltage; //store request voltage

	adaptiveVoltRequest[channel] = false;

	if(abs(voltage - ChannelsStatus[channel].set_voltage) > MainParams.VoltageRamp_VoltStep) //voltage ramping if difference is bigger that voltage ramp step
	{
		//ChannelsChange[channel].request_voltage = voltage; //store request voltage

		//calculate new voltage
		if(ChannelsStatus[channel].set_voltage < ChannelsChange[channel].request_voltage)
		{
			ChannelsStatus[channel].set_voltage += MainParams.VoltageRamp_VoltStep;
		}
		else
		{
			ChannelsStatus[channel].set_voltage -= MainParams.VoltageRamp_VoltStep;
		}

		//Set voltage
		Set_OutReg_Voltage(channel, ChannelsStatus[channel].set_voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(ChannelsStatus[channel].set_voltage));

		//Enable and set ramping timer
		ChannelsChange[channel].voltage_ramp = true;
		ChannelsChange[channel].voltage_ramp_timer = HAL_GetTick();
	}
	else //without voltage ramping if difference is smaller that voltage ramp step
	{
		//ChannelsChange[channel].request_voltage = voltage; //store request voltage
		ChannelsStatus[channel].set_voltage = voltage;
		Set_OutReg_Voltage(channel, voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(voltage));

		ChannelsChange[channel].regStart_timer = HAL_GetTick();
		ChannelsChange[channel].regStart_req = true;
	}


}


void Set_VoltageInEnable(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	uint16_t voltage = minimum_voltage;

	Set_OutReg_Voltage(channel, voltage);
	Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(voltage));

	ChannelsStatus[channel].set_voltage = voltage;
}

/* @brief Setting voltage from ramping control
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param voltage -> request voltage on output of power supply channel
 *
 */
void Set_Voltage_From_Ramping(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	if(abs(ChannelsStatus[channel].set_voltage - ChannelsChange[channel].request_voltage) > MainParams.VoltageRamp_VoltStep) //keep ramping
	{

		//calculate new voltage
		if(ChannelsStatus[channel].set_voltage < ChannelsChange[channel].request_voltage)
		{
			ChannelsStatus[channel].set_voltage += MainParams.VoltageRamp_VoltStep;
		}
		else
		{
			ChannelsStatus[channel].set_voltage -= MainParams.VoltageRamp_VoltStep;
		}

		//Set out voltage
		Set_OutReg_Voltage(channel, ChannelsStatus[channel].set_voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(ChannelsStatus[channel].set_voltage));

		//Reset ramping timer
		ChannelsChange[channel].voltage_ramp = true;
		ChannelsChange[channel].voltage_ramp_timer = HAL_GetTick();
	}
	else
	{
		//Disable ramping timer
		ChannelsChange[channel].voltage_ramp = false;

		ChannelsStatus[channel].set_voltage = ChannelsChange[channel].request_voltage;

		Set_OutReg_Voltage(channel, ChannelsStatus[channel].set_voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(ChannelsStatus[channel].set_voltage));

		ChannelsChange[channel].regStart_timer = HAL_GetTick();
		ChannelsChange[channel].regStart_req = true;
	}

}

/* @brief Request on anable or disable channel of power supply
 *        Enable - Setting minimial voltage on power supply channel and set enable_request_timer
 *		           Enable timer exetutes in Channel Control function
 *		  Disable - Setting minimal voltage, disable channel and disable enable_request_timer
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param enable -> true - enable, false disble 
 * 
 */
void Channel_Enable(uint8_t channel, bool enable)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if(enable == ChannelsStatus[channel].enable) return;


	ChannelsChange[channel].voltageBeforeEnable = ChannelsChange[channel].request_voltage;

	ChannelsChange[channel].restarts_counter = 0;
	ChannelsStatus[channel].disableInError = false;

	if(enable)
	{
		//Set_Voltage(channel, minimum_voltage);
		Set_VoltageInEnable(channel);
		Enable_GPIO(channel, true);
		ChannelsStatus[channel].enable = true;
		ChannelsChange[channel].restart_request = false;
		ChannelsChange[channel].enable_request = true;
		ChannelsChange[channel].enable_timer = HAL_GetTick();
	}
	else
	{
		ChannelsChange[channel].enable_request = false;
		ChannelsStatus[channel].enable = false;
		ChannelsChange[channel].restart_request = false;
		Enable_GPIO(channel, false);
		adaptiveVoltRequest[channel] = false;
	}


	if(MainParams.ControlOutputWithChannelEnable) //je aktivni funkce ovladani vystupu s eneble
	{
		if(enable)
		{
			Channel_Output(channel, true);
		}
		else
		{
			Channel_Output(channel, false);
		}
	}

}

void Channel_Restart(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	if(ChannelsStatus[channel].enable == false)
	{
		ChannelsChange[channel].restart_request = false;
		return;
	}

	//ChannelsChange[channel].restarts_counter++;

	ErrorTimerReset(channel);

	if(ChannelsChange[channel].restarts_counter >= max_restart_count)
	{
		Channel_Enable(channel, false);
		ChannelsStatus[channel].disableInError = true;
		ChannelsChange[channel].restart_request = false;
	}
	else
	{
		ChannelsChange[channel].restart_request = true;
		ChannelsChange[channel].restart_timer = HAL_GetTick();

		Enable_GPIO(channel, false);
		Channel_Output(channel, false);

	}


}

void Channel_Enable_fromRestart(uint8_t channel)
{
	ChannelsChange[channel].voltageBeforeEnable = ChannelsChange[channel].request_voltage;

	Set_VoltageInEnable(channel);
	Enable_GPIO(channel, true);
	ChannelsStatus[channel].enable = true;
	ChannelsChange[channel].restart_request = false;
	ChannelsChange[channel].enable_request = true;
	ChannelsChange[channel].enable_timer = HAL_GetTick();

	Channel_Output(channel, true);

	if(MainParams.ControlOutputWithChannelEnable) //je aktivni funkce ovladani vystupu s eneble
	{
		Channel_Output(channel, true);
	}


}

/* @brief Channel polarity change
 *        Request on polarity change, set polarity timer. Timer exetutes in ChannelControl function.
 *
 * @param channel -> Channel of power supply (0,1,2)
 * @param polarity -> polarity of output voltage
 * 
 */
void Channel_Polarity(uint8_t channel, eOutputPolarity polarity)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;
	if(polarity == ChannelsStatus[channel].polarity) return;

	if(MainParams.ControlOutputWithChannelEnable && ChannelsStatus[channel].enable) return; // polarita nejde prepnout, kdyz je kanál zapnutý


	if(ChannelsChange[channel].polarity_request) return;

	ChannelsStatus[channel].polarity = polarity;
	Output_GPIO(channel, false, false);

	ChannelsChange[channel].polarity_request = true;
	ChannelsChange[channel].polarity_timer = HAL_GetTick();

}

/* @brief Enable output of power supply
 *        
 * @param channel -> Channel of power supply (0,1,2)
 * @param output -> true - output on, false - output off
 * 
 */
void Channel_Output(uint8_t channel, bool output)
{

	if(MainParams.ControlOutputWithChannelEnable && ChannelsStatus[channel].enable && !ChannelsChange[channel].enable_request && output) return; // vystup nejde zapnout, kdyz je kanál zapnutý

	ChannelsStatus[channel].output = output;

	if(ChannelsStatus[channel].polarity == polarity_positive)
	{
		Output_GPIO(channel, output, false);
	}
	else if(ChannelsStatus[channel].polarity == polarity_negative)
	{
		Output_GPIO(channel, false, output);
	}
}

/* @brief Control of power supply channel
 *        Execute request on enable, polarity change and ramping set voltage
 *
 * @param channel -> Channel of power supply (0,1,2)
 * 
 */
void ChannelControl(uint8_t channel)
{
	//voltage ramping
	if(ChannelsChange[channel].voltage_ramp)
	{
		if((HAL_GetTick()-ChannelsChange[channel].voltage_ramp_timer) >= MainParams.VoltageRamp_TimeStep)
		{
			Set_Voltage_From_Ramping(channel);
		}
	}

	//enable control
	if(ChannelsChange[channel].enable_request)
	{
		if((HAL_GetTick()-ChannelsChange[channel].enable_timer) >= delay_enable)
		{
			ChannelsChange[channel].enable_request = false;
			Enable_GPIO(channel, true);
			//nastavit napeti
			Set_Voltage(channel, ChannelsChange[channel].request_voltage );
		}
	}

	//polarity change control
	if(ChannelsChange[channel].polarity_request)
	{
		if((HAL_GetTick()-ChannelsChange[channel].polarity_timer) >= delay_polarity)
		{
			ChannelsChange[channel].polarity_request = false;
			bool output = ChannelsStatus[channel].output;

			if(ChannelsStatus[channel].polarity == polarity_positive)
			{
				Output_GPIO(channel, output, false);
			}
			else if(ChannelsStatus[channel].polarity == polarity_negative)
			{
				Output_GPIO(channel, false, output);
			}

		}
	}

	//restart channel
	if(ChannelsChange[channel].restart_request)
	{
		if((HAL_GetTick()-ChannelsChange[channel].restart_timer) >= delay_restart)
		{
			//ChannelsChange[channel].restart_request = false;
			//ChannelsChange[channel].restarts_counter++;
			ChannelsChange[channel].restarts_counter++;
			Channel_Enable_fromRestart(channel);

		}
	}

	if(ChannelsChange[channel].regStart_req)
	{
		if((HAL_GetTick()-ChannelsChange[channel].regStart_timer) >= regStart_Time)
		{
			ChannelsChange[channel].regStart_req = false;
			AdaptiveVoltageTune_Start(channel);
		}
	}

}

/* @brief Send by communication measured channel voltage from Channel status struct
 *
 * @param channel -> Channel of power supply (0,1,2)
 * 
 */
void Get_ChannelVoltage(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	//SendCommunication(cmd_get_voltage_CH1 + channel, ChannelsStatus[channel].voltage_measurement*100);
	SendCommunication_float(cmd_get_voltage_CH1 + channel, ChannelsStatus[channel].voltage_measurement);
}

/* @brief Send by communication measured channel current from Channel status struct
 *
 * @param channel -> Channel of power supply (0,1,2)
 * 
 */
void Get_ChannelCurrent(uint8_t channel)
{
	if(!(channel == 0 || channel == 1 || channel == 2)) return;

	//SendCommunication(cmd_get_current_CH1 + channel, ChannelsStatus[channel].current_measurement*1000);
	SendCommunication_float(cmd_get_current_CH1 + channel, ChannelsStatus[channel].current_measurement);
}

void Get_ErrorSignals()
{
	uint8_t error_reg = 0;

	error_reg |= ChannelsStatus[0].power_good << 0;
	error_reg |= ChannelsStatus[1].power_good << 1;
	error_reg |= ChannelsStatus[2].power_good << 2;

	error_reg |= ChannelsStatus[0].over_current << 3;
	error_reg |= ChannelsStatus[1].over_current << 4;
	error_reg |= ChannelsStatus[2].over_current << 5;

	SendCommunication(cmd_error_signals, error_reg);
}

/* @brief Send by communication all measured value, all voltages and currents
 *
 * 
 */
void Get_AllMeasurement()
{
	Get_ChannelVoltage(0);
	Get_ChannelVoltage(1);
	Get_ChannelVoltage(2);
	Get_ChannelCurrent(0);
	Get_ChannelCurrent(1);
	Get_ChannelCurrent(2);

	Get_ErrorSignals();
}

/* @brief Send by communication setting of power supply
 *
 * 
 */
void Get_Setting()
{
	SendCommunication(cmd_set_voltage_CH1, ChannelsChange[0].request_voltage);
	SendCommunication(cmd_set_voltage_CH2, ChannelsChange[1].request_voltage);
	SendCommunication(cmd_set_voltage_CH3, ChannelsChange[2].request_voltage);

	//SendCommunication(cmd_set_voltage_CH1,ChannelsStatus[0].set_voltage);
	//SendCommunication(cmd_set_voltage_CH2,ChannelsStatus[1].set_voltage);
	//SendCommunication(cmd_set_voltage_CH3,ChannelsStatus[2].set_voltage);

	SendCommunication(cmd_enable_CH1, ChannelsStatus[0].enable);
	SendCommunication(cmd_enable_CH2, ChannelsStatus[1].enable);
	SendCommunication(cmd_enable_CH3, ChannelsStatus[2].enable);

	SendCommunication(cmd_polarity_CH1, ChannelsStatus[0].polarity + 1);
	SendCommunication(cmd_polarity_CH2, ChannelsStatus[1].polarity + 1);
	SendCommunication(cmd_polarity_CH3, ChannelsStatus[2].polarity + 1);

	SendCommunication(cmd_output_CH1, ChannelsStatus[0].output);
	SendCommunication(cmd_output_CH2, ChannelsStatus[1].output);
	SendCommunication(cmd_output_CH3, ChannelsStatus[2].output);

	SendCommunication(cmd_thats_all, 1);
}

void Get_State_err()
{

	for(int i = 0; i <3; i++)
	{
		uint8_t err_state = 0;

		if(ChannelsStatus[i].disableInError)//kanal byl vypnut z erroru
		{
			err_state = 1;
		}
		else if(ChannelsChange[i].restart_request) //kanal se restartuje
		{
			err_state = 2;
		}

		SendCommunication(cmd_ch1_get_err_state + i, err_state);
	}

}

/* @brief reset MCU
 *
 *
 */
void System_Reset()
{
	__DSB();
	SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) | (SCB_AIRCR_SYSRESETREQ_Msk));
	__DSB();
	while(1);
}


void VoltageRamp_SetVoltageStep(int voltage)
{
	if((voltage < 1) || (voltage > 100)) return;

	MainParams.VoltageRamp_VoltStep = voltage;
}

void VoltageRamp_SetTimeStep(int time)
{
	if((time < 1) || (time > 10000)) return;

	MainParams.VoltageRamp_TimeStep = time;
}

void VoltageRamp_SendSetting()
{
	SendCommunication(cmd_voltRamp_get_volt, MainParams.VoltageRamp_VoltStep);
	SendCommunication(cmd_voltRamp_get_time, MainParams.VoltageRamp_TimeStep);
}



void AdaptiveVoltageTune_Start(int channel)
{
	if(MainParams.EnableAdaptiveVoltageTune == false)
	{
		adaptiveVoltRequest[channel] = false;
		return;
	}

	addSetVoltage[channel] = 0;
	adaptiveVoltRequest[channel] = true;
}

void AdaptiveVoltageTune(int channel)
{
	if(ChannelsChange[channel].voltage_ramp == true || ChannelsStatus[channel].enable == false)
	{
		return;
	}


	float measVoltage = ChannelsStatus[channel].voltage_measurement;
	uint16_t setVoltage = ChannelsStatus[channel].set_voltage;

	AdaptiveDiff[channel] = measVoltage - (float)setVoltage;

	if(abs(AdaptiveDiff[channel] > 2))
	{
		adaptiveVoltRequest[channel] = true;
	}

	if(adaptiveVoltRequest[channel] == false) return;

	if(AdaptiveDiff[channel] > 0.50)
	{
		addSetVoltage[channel] -= 0.25;

		uint16_t voltage = setVoltage + addSetVoltage[channel];

		Set_OutReg_Voltage(channel, voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(voltage));
	}
	if(AdaptiveDiff[channel] < -0.50)
	{
		addSetVoltage[channel] += 0.25;

		float voltage = setVoltage + addSetVoltage[channel];

		Set_OutReg_Voltage_F(channel, voltage);
		Set_PreReg_Voltage(channel, Get_PreRegulatorVoltage(voltage));
	}
	else
	{
		adaptiveVoltRequest[channel] = false;
	}


}



