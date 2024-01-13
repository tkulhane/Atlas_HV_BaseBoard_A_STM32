/*
 * app_params.c
 *
 *  Created on: Jan 1, 2024
 *      Author: tomas
 */


#include "app_params.h"
#include "flash.h"
#include "app_communication.h"


#define Default_AdjCoef_k 547.8647847
#define Default_AdjCoef_q 642.7527532

#define Default_Meas_U_Coef_k 0.00542121
#define Default_Meas_U_Coef_q 0.05778585

#define Default_Meas_I_Coef_k 0.0972
#define Default_Meas_I_Coef_q 0.0619




FlashSectorParams MainParams;
FlashSectorParams DefaultParams;


uint32_t MakeUint32FromFloat(float value)
{
	uint32_t x;
	memcpy(&x,&value,sizeof(x));

	return x;
}



void ParamsDefaultValues()
{

	DefaultParams.StoreControl_0 = 0;
	DefaultParams.StoreControl_1 = 0;


	DefaultParams.MAC_aadress_1_3MSB = mac_MAKEU32(0xAD,0xCF,0xE8);
	DefaultParams.MAC_aadress_2_3LSB = mac_MAKEU32(0xA5,0xDF,0xFF);
	DefaultParams.IP_ADDRESS = ip_MAKEU32(192,168,0,23);
	DefaultParams.NETMASK_ADDRESS = ip_MAKEU32(255,255,255,0);
	DefaultParams.GATEWAY_ADDRESS = ip_MAKEU32(192,168,0,1);
	DefaultParams.UdpRecvPort = 5005;

	DefaultParams.ReadCoef_k_0 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.ReadCoef_k_1 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.ReadCoef_k_2 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.ReadCoef_k_3 = MakeUint32FromFloat(Default_Meas_I_Coef_k);
	DefaultParams.ReadCoef_k_4 = MakeUint32FromFloat(Default_Meas_I_Coef_k);
	DefaultParams.ReadCoef_k_5 = MakeUint32FromFloat(Default_Meas_I_Coef_k);

	DefaultParams.ReadCoef_q_0 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.ReadCoef_q_1 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.ReadCoef_q_2 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.ReadCoef_q_3 = MakeUint32FromFloat(Default_Meas_I_Coef_q);
	DefaultParams.ReadCoef_q_4 = MakeUint32FromFloat(Default_Meas_I_Coef_q);
	DefaultParams.ReadCoef_q_5 = MakeUint32FromFloat(Default_Meas_I_Coef_q);

	DefaultParams.AdjCoef_k_ch0 =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.AdjCoef_k_ch1  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.AdjCoef_k_ch2  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.AdjCoef_q_ch0 = MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.AdjCoef_q_ch1 =  MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.AdjCoef_q_ch2  =  MakeUint32FromFloat(Default_AdjCoef_q);

	DefaultParams.EnableErrorExecute = 1;
	DefaultParams.DisableSupplyInLostConnection = 0;
	DefaultParams.ControlOutputWithChannelEnable = 1;
	DefaultParams.ErrorExecuteAutoRestore = 1;
	DefaultParams.EnableAdaptiveVoltageTune = 0;

	DefaultParams.VoltageRamp_VoltStep = 5;
	DefaultParams.VoltageRamp_TimeStep = 100;


}


void ParamsLoad()
{

	FlashSectorParams LoadParams;

	Flash_ReadParamStruct(&LoadParams);

	uint32_t StoreControl_0 = LoadParams.StoreControl_0;
	//uint32_t StoreControl_1 = LoadParams.StoreControl_1;


	for(int i = 2; i < NUMBER_OF_PARAMS;i++)
	{
		//if((StoreControl_0 == STORE_VALIDE_CODE) &&  ((StoreControl_1 >> i) & 0x000001))
		if(StoreControl_0 == STORE_VALIDE_CODE)
		{
			*((uint32_t*)(&MainParams)+i) = *((uint32_t*)(&LoadParams)+i);


		}
		else
		{
			*((uint32_t*)(&MainParams)+i) = *((uint32_t*)(&DefaultParams)+i);
		}
	}

}

void ParamsStore()
{
	MainParams.StoreControl_0 = STORE_VALIDE_CODE;
	MainParams.StoreControl_1 = 0x0;

	Flash_WriteParamStruct(MainParams);
}

void RestoreParamsDefault()
{
	Flash_WriteParamStruct(DefaultParams);
	ParamsLoad();
}




void SetConfigData(int cfg, int value)
{
	uint32_t *addr = &MainParams.EnableErrorExecute + cfg;

	*addr = value;

}


void SendConfigData()
{
	SendCommunication(cmd_CfgGet_EnableErrorExecute, MainParams.EnableErrorExecute);
	SendCommunication(cmd_CfgGet_DisableInConnLost, MainParams.DisableSupplyInLostConnection);
	SendCommunication(cmd_CfgGet_CtrlOutWithChEnable, MainParams.ControlOutputWithChannelEnable);
	SendCommunication(cmd_CfgGet_ErrorExecuteAutoRestart, MainParams.ErrorExecuteAutoRestore);
	SendCommunication(cmd_CfgGet_EnableAdaptiveVoltTune, MainParams.EnableAdaptiveVoltageTune);
}


