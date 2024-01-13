/*
 * app_params.h
 *
 *  Created on: Jan 1, 2024
 *      Author: tomas
 */

#ifndef INC_APP_PARAMS_H_
#define INC_APP_PARAMS_H_

#include "main.h"
#include "app_udp.h"

#define STORE_VALIDE_CODE 0xA4B7A4B7

/*Struct of parameters in flash*/
typedef struct
{
	uint32_t StoreControl_0;
	uint32_t StoreControl_1;

	uint32_t MAC_aadress_1_3MSB; //11.11.11.00.00.00
	uint32_t MAC_aadress_2_3LSB; //00.00.00.11.11.11
	uint32_t IP_ADDRESS;
	uint32_t NETMASK_ADDRESS;
	uint32_t GATEWAY_ADDRESS;
	uint32_t UdpRecvPort;


	uint32_t ReadCoef_k_0;
	uint32_t ReadCoef_k_1;
	uint32_t ReadCoef_k_2;
	uint32_t ReadCoef_k_3;
	uint32_t ReadCoef_k_4;
	uint32_t ReadCoef_k_5;
	uint32_t ReadCoef_q_0;
	uint32_t ReadCoef_q_1;
	uint32_t ReadCoef_q_2;
	uint32_t ReadCoef_q_3;
	uint32_t ReadCoef_q_4;
	uint32_t ReadCoef_q_5;

	uint32_t AdjCoef_k_ch0;
	uint32_t AdjCoef_k_ch1;
	uint32_t AdjCoef_k_ch2;
	uint32_t AdjCoef_q_ch0;
	uint32_t AdjCoef_q_ch1;
	uint32_t AdjCoef_q_ch2;

	uint32_t EnableErrorExecute;
	uint32_t DisableSupplyInLostConnection ;
	uint32_t ControlOutputWithChannelEnable;
	uint32_t ErrorExecuteAutoRestore;
	uint32_t EnableAdaptiveVoltageTune;

	uint32_t Reserved_1;
	uint32_t Reserved_2;
	uint32_t Reserved_3;
	uint32_t Reserved_4;
	uint32_t Reserved_5;
	uint32_t Reserved_6;
	uint32_t Reserved_7;
	uint32_t Reserved_8;

	uint32_t VoltageRamp_VoltStep;
	uint32_t VoltageRamp_TimeStep;



}FlashSectorParams;


extern FlashSectorParams MainParams;
extern FlashSectorParams DefaultParams;


void ParamsDefaultValues();
void ParamsLoad();
void ParamsStore();
void RestoreParamsDefault();

void SetConfigData(int cfg, int value);
void SendConfigData();

#endif /* INC_APP_PARAMS_H_ */
