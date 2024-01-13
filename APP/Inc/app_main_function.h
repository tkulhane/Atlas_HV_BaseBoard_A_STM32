/*
 * app_main_function.h
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#ifndef INC_APP_MAIN_FUNCTION_H_
#define INC_APP_MAIN_FUNCTION_H_


#include "app_function_ADC.h"
#include "main.h"

#include "app_spi_function_DAC.h"
#include "app_gpio_function.h"
#include "app_usart_process.h"
#include "app_communication.h"

#define minimum_voltage 30
#define maximum_voltage 550

#define delay_polarity 200
#define delay_enable 200

#define delay_restart 3000
#define max_restart_count 3

#define ramp_v_step 5
#define ramp_t_step 100

#define regStart_Time 500



typedef enum
{
	polarity_positive,
	polarity_negative
}eOutputPolarity;


typedef struct
{
	bool enable;
	uint16_t set_voltage;
	eOutputPolarity polarity;
	bool output;
	float voltage_measurement;
	float current_measurement;
	bool over_current;
	bool power_good;
	bool disableInError;

}ChannelStatusStruct;

typedef struct
{
	bool voltage_ramp;
	bool enable_request;
	bool polarity_request;
	bool restart_request;
	bool regStart_req;

	uint32_t voltage_ramp_timer;
	uint32_t enable_timer;
	uint32_t polarity_timer;
	uint32_t restart_timer;
	uint8_t restarts_counter;
	uint32_t regStart_timer;

	uint16_t request_voltage;
	uint16_t voltageBeforeEnable;

}ChannelChangeStruct;


extern ChannelStatusStruct ChannelsStatus[3];
extern ChannelChangeStruct ChannelsChange[3];

extern bool _ControlOutputWithChannelEnable;

void LoadDACConstant();
void StoreDACConstant(uint8_t coef, float value);
float GetDACConstant(uint8_t coef);
void SendDACCoefficients();

uint16_t Get_PreRegulatorVoltage(uint16_t voltage);
uint16_t Get_DACValue(int dac_channel, uint16_t value);
void Set_Voltage(uint8_t channel, uint16_t voltage);
void Channel_Enable(uint8_t channel, bool enable);
void Channel_Restart(uint8_t channel);
void Channel_Enable_fromRestart(uint8_t channel);
void Channel_Polarity(uint8_t channel, eOutputPolarity polarity);
void Channel_Output(uint8_t channel, bool output);
void ChannelControl(uint8_t channel);
void Get_ChannelVoltage(uint8_t channel);
void Get_ErrorSignals();
void Get_AllMeasurement();
void Get_Setting();
void Get_State_err();
void Set_PreReg_Voltage(uint8_t channel, uint16_t voltage);
void Set_OutReg_Voltage(uint8_t channel, uint16_t voltage);

void System_Reset();

void AdaptiveVoltageTune_Start(int channel);
void AdaptiveVoltageTune(int channel);


#endif /* INC_APP_MAIN_FUNCTION_H_ */
