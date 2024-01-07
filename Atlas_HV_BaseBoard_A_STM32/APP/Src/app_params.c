/*
 * app_params.c
 *
 *  Created on: Jan 1, 2024
 *      Author: tomas
 */


#include "app_params.h"
#include "flash.h"
#include "app_communication.h"


#define Default_AdjCoef_k 475.3679441
#define Default_AdjCoef_q 676.4176934

#define Default_Meas_U_Coef_k 0.005390557
#define Default_Meas_U_Coef_q 0.063614657

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

	DefaultParams.sramOffset_StoreControl_0 = 0;
	DefaultParams.sramOffset_StoreControl_1 = 0;

	DefaultParams.sramOffset_IP_ADDRESS = ip_MAKEU32(192,168,0,22);
	DefaultParams.sramOffset_NETMASK_ADDRESS = ip_MAKEU32(255,255,255,0);
	DefaultParams.sramOffset_GATEWAY_ADDRESS = ip_MAKEU32(192,168,0,1);

	DefaultParams.sramOffset_ReadCoef_k_0 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.sramOffset_ReadCoef_k_1 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.sramOffset_ReadCoef_k_2 = MakeUint32FromFloat(Default_Meas_U_Coef_k);
	DefaultParams.sramOffset_ReadCoef_k_3 = MakeUint32FromFloat(Default_Meas_I_Coef_k);
	DefaultParams.sramOffset_ReadCoef_k_4 = MakeUint32FromFloat(Default_Meas_I_Coef_k);
	DefaultParams.sramOffset_ReadCoef_k_5 = MakeUint32FromFloat(Default_Meas_I_Coef_k);

	DefaultParams.sramOffset_ReadCoef_q_0 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.sramOffset_ReadCoef_q_1 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.sramOffset_ReadCoef_q_2 = MakeUint32FromFloat(Default_Meas_U_Coef_q);
	DefaultParams.sramOffset_ReadCoef_q_3 = MakeUint32FromFloat(Default_Meas_I_Coef_q);
	DefaultParams.sramOffset_ReadCoef_q_4 = MakeUint32FromFloat(Default_Meas_I_Coef_q);
	DefaultParams.sramOffset_ReadCoef_q_5 = MakeUint32FromFloat(Default_Meas_I_Coef_q);

	DefaultParams.sramOffset_AdjCoef_k_ch0 =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_k_ch1  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_k_ch2  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_q_ch0 = MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.sramOffset_AdjCoef_q_ch1 =  MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.sramOffset_AdjCoef_q_ch2  =  MakeUint32FromFloat(Default_AdjCoef_q);

	DefaultParams.sramOffset_EnableErrorExecute = 1;
	DefaultParams.sramOffset_DisableSupplyInLostConnection = 0;
	DefaultParams.sramOffset_ControlOutputWithChannelEnable = 1;
	DefaultParams.sramOffset_ErrorExecuteAutoRestore = 1;


}


void ParamsLoad()
{

	FlashSectorParams LoadParams;

	Flash_ReadParamStruct(&LoadParams);

	uint32_t StoreControl_0 = LoadParams.sramOffset_StoreControl_0;
	//uint32_t StoreControl_1 = LoadParams.sramOffset_StoreControl_1;


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
	MainParams.sramOffset_StoreControl_0 = STORE_VALIDE_CODE;
	MainParams.sramOffset_StoreControl_1 = 0xA1B2C3D4;

	Flash_WriteParamStruct(MainParams);
}

void RestoreParamsDefault()
{
	Flash_WriteParamStruct(DefaultParams);
	ParamsLoad();
}




void SetConfigData(int cfg, int value)
{
	uint32_t *addr = &MainParams.sramOffset_EnableErrorExecute + cfg;

	*addr = value;

}


void SendConfigData()
{
	SendCommunication(cmd_CfgGet_EnableErrorExecute, MainParams.sramOffset_EnableErrorExecute);
	SendCommunication(cmd_CfgGet_DisableInConnLost, MainParams.sramOffset_DisableSupplyInLostConnection);
	SendCommunication(cmd_CfgGet_CtrlOutWithChEnable, MainParams.sramOffset_ControlOutputWithChannelEnable);
	SendCommunication(cmd_CfgGet_ErrorExecuteAutoRestart, MainParams.sramOffset_ErrorExecuteAutoRestore);
}


