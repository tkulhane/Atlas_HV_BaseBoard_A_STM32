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
	uint32_t sramOffset_StoreControl_0;
	uint32_t sramOffset_StoreControl_1;

	uint32_t sramOffset_IP_ADDRESS;
	uint32_t sramOffset_NETMASK_ADDRESS;
	uint32_t sramOffset_GATEWAY_ADDRESS;

	uint32_t sramOffset_ReadCoef_k_0;
	uint32_t sramOffset_ReadCoef_k_1;
	uint32_t sramOffset_ReadCoef_k_2;
	uint32_t sramOffset_ReadCoef_k_3;
	uint32_t sramOffset_ReadCoef_k_4;
	uint32_t sramOffset_ReadCoef_k_5;
	uint32_t sramOffset_ReadCoef_q_0;
	uint32_t sramOffset_ReadCoef_q_1;
	uint32_t sramOffset_ReadCoef_q_2;
	uint32_t sramOffset_ReadCoef_q_3;
	uint32_t sramOffset_ReadCoef_q_4;
	uint32_t sramOffset_ReadCoef_q_5;

	uint32_t sramOffset_AdjCoef_k_ch0;
	uint32_t sramOffset_AdjCoef_k_ch1;
	uint32_t sramOffset_AdjCoef_k_ch2;
	uint32_t sramOffset_AdjCoef_q_ch0;
	uint32_t sramOffset_AdjCoef_q_ch1;
	uint32_t sramOffset_AdjCoef_q_ch2;
}FlashSectorParams;


extern FlashSectorParams MainParams;
extern FlashSectorParams DefaultParams;


void ParamsDefaultValues();
void ParamsLoad();

#endif /* INC_APP_PARAMS_H_ */
