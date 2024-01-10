/*
 * app_communication.h
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */

#ifndef INC_APP_COMMUNICATION_H_
#define INC_APP_COMMUNICATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "app_spi_function_DAC.h"
#include "app_gpio_function.h"
#include "app_main_function.h"
#include "app_usart_process.h"
#include "app_eth_process.h"
#include "app_udp.h"

#define STRING_TABLE_SIZE 50

#define ConnectedTimer_Value 1000

typedef enum
{
	cmd_NON,
	cmd_Connected,
	cmd_enable_CH1,
	cmd_enable_CH2,
	cmd_enable_CH3,
	cmd_output_CH1,
	cmd_output_CH2,
	cmd_output_CH3,
	cmd_set_voltage_CH1,
	cmd_set_voltage_CH2,
	cmd_set_voltage_CH3,
	cmd_polarity_CH1,
	cmd_polarity_CH2,
	cmd_polarity_CH3,
	cmd_get_voltage_CH1,
	cmd_get_voltage_CH2,
    cmd_get_voltage_CH3,
	cmd_get_current_CH1,
	cmd_get_current_CH2,
	cmd_get_current_CH3,
	cmd_error_signals,
	cmd_getallvalues,
	cmd_getsetting,
	cmd_thats_all,
	cmd_LED,

	cmd_ip_store_endpoint,

	cmd_ip_store_mac,
	cmd_ip_store_myip,
	cmd_ip_store_mymask,
	cmd_ip_store_mygatew,
	cmd_ip_store_UdpRecvPort,

	cmd_ip_get_mac,
	cmd_ip_get_myip,
	cmd_ip_get_mymask,
	cmd_ip_get_mygatew,
	cmd_ip_get_UdpRecvPort,

	cmd_ip_getsetting,
	cmd_adc_set_k0,
	cmd_adc_set_k1,
	cmd_adc_set_k2,
	cmd_adc_set_k3,
	cmd_adc_set_k4,
	cmd_adc_set_k5,
	cmd_adc_set_q0,
	cmd_adc_set_q1,
	cmd_adc_set_q2,
	cmd_adc_set_q3,
	cmd_adc_set_q4,
	cmd_adc_set_q5,
	cmd_adc_get_k0,
	cmd_adc_get_k1,
	cmd_adc_get_k2,
	cmd_adc_get_k3,
	cmd_adc_get_k4,
	cmd_adc_get_k5,
	cmd_adc_get_q0,
	cmd_adc_get_q1,
	cmd_adc_get_q2,
	cmd_adc_get_q3,
	cmd_adc_get_q4,
	cmd_adc_get_q5,
	cmd_dac_set_k0,
	cmd_dac_set_k1,
	cmd_dac_set_k2,
	cmd_dac_set_q0,
	cmd_dac_set_q1,
	cmd_dac_set_q2,
	cmd_dac_get_k0,
	cmd_dac_get_k1,
	cmd_dac_get_k2,
	cmd_dac_get_q0,
	cmd_dac_get_q1,
	cmd_dac_get_q2,
	cmd_adc_getallcoef,
	cmd_dac_getallcoef,
	cmd_set_pre_reg_CH1,
	cmd_set_pre_reg_CH2,
	cmd_set_pre_reg_CH3,
	cmd_set_out_reg_CH1,
	cmd_set_out_reg_CH2,
	cmd_set_out_reg_CH3,

	cmd_ch1_get_err_state,
	cmd_ch2_get_err_state,
	cmd_ch3_get_err_state,
	cmd_errState_Get,

	cmd_CfgSet_EnableErrorExecute,
	cmd_CfgSet_DisableInConnLost,
	cmd_CfgSet_CtrlOutWithChEnable,
	cmd_CfgSet_ErrorExecuteAutoRestart,

	cmd_CfgGet_EnableErrorExecute,
	cmd_CfgGet_DisableInConnLost,
	cmd_CfgGet_CtrlOutWithChEnable,
	cmd_CfgGet_ErrorExecuteAutoRestart,
	cmd_Cfg_Get,

	cmd_params_store,
	cmd_params_default,

	cmd_Eth_ReInit,

	cmd_reset


}eCommand_Id;

typedef enum
{
	cform_full,
	cform_short
}eCommand_Form;

typedef enum
{
	csource_UART,
	csource_ETH,
}eCommand_source;

typedef enum
{
	cparse_non,
	cparse_int,
	cparse_float,
	cparse_u32t
}eCommand_parse;

extern int _command_id;
extern bool _AppConnected;

void ProcessCommand(int command_id);
int get_string_length(const char* s);
bool StringIsEqual(const uint8_t *one,int one_start, int one_end, const uint8_t *two,int two_start, int two_end);
int GetDelimiterPosition(const uint8_t *Buffer, int legth, uint8_t Delimiter);
bool ProcessLine(const uint8_t *Buffer, int legth);
bool ProcessCommunication_UART();
bool ProcessCommunication_ETH();
void SendCommunication(eCommand_Id command_id, int data);
void SendCommunication_float(eCommand_Id command_id, float data);
void SendCommunication_u32(eCommand_Id command_id, uint32_t data);

void Comunication_ResetConnectedTimer();
void Communication_ConnectedTimer();

#endif /* INC_APP_COMMUNICATION_H_ */
