/*
 * app_params.c
 *
 *  Created on: Jan 1, 2024
 *      Author: tomas
 */


#include "app_params.h"
#include "flash.h"

#define Default_AdjCoef_k 511.8182426
#define Default_AdjCoef_q 655.2648273


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

	DefaultParams.sramOffset_ReadCoef_k_0 = MakeUint32FromFloat(0.00540804);
	DefaultParams.sramOffset_ReadCoef_k_1 = MakeUint32FromFloat(0.00540804);
	DefaultParams.sramOffset_ReadCoef_k_2 = MakeUint32FromFloat(0.00540804);
	DefaultParams.sramOffset_ReadCoef_k_3 = MakeUint32FromFloat(0.06175469);
	DefaultParams.sramOffset_ReadCoef_k_4 = MakeUint32FromFloat(0.06175469);
	DefaultParams.sramOffset_ReadCoef_k_5 = MakeUint32FromFloat(0.06175469);

	DefaultParams.sramOffset_ReadCoef_q_0 = MakeUint32FromFloat(0.09030197);
	DefaultParams.sramOffset_ReadCoef_q_1 = MakeUint32FromFloat(0.09030197);
	DefaultParams.sramOffset_ReadCoef_q_2 = MakeUint32FromFloat(0.09030197);
	DefaultParams.sramOffset_ReadCoef_q_3 = MakeUint32FromFloat(0.06370294);
	DefaultParams.sramOffset_ReadCoef_q_4 = MakeUint32FromFloat(0.06370294);
	DefaultParams.sramOffset_ReadCoef_q_5 = MakeUint32FromFloat(0.06370294);

	DefaultParams.sramOffset_AdjCoef_k_ch0 =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_k_ch1  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_k_ch2  =  MakeUint32FromFloat(Default_AdjCoef_k);
	DefaultParams.sramOffset_AdjCoef_q_ch0 = MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.sramOffset_AdjCoef_q_ch1 =  MakeUint32FromFloat(Default_AdjCoef_q);
	DefaultParams.sramOffset_AdjCoef_q_ch2  =  MakeUint32FromFloat(Default_AdjCoef_q);


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


