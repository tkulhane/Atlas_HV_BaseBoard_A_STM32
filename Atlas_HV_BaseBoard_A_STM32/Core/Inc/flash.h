/*
 * Flash.h
 *
 *  Created on: Oct 27, 2023
 *      Author: FarkasM
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/*Base address of sector 7*/
#define BASE_PARAM_ADR 0x08060000

/*Struct of parameters in flash*/
typedef struct FlashSectorParams
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

/*Number of members in struct FlashSectorParams*/
#define NUMBER_OF_PARAMS (sizeof(FlashSectorParams) / sizeof(uint32_t))

//Generic Functions
uint32_t Flash_GetSector(uint32_t StartSectorAddress);
uint32_t Flash_WriteData (uint32_t StartSectorAddress, uint32_t *Data, uint16_t NumOfWords);


//Functions for Power Params
void     Flash_ReadParamStruct(FlashSectorParams* s_data);
uint32_t Flash_WriteParamStruct(FlashSectorParams ParamsData);

#ifdef __cplusplus
}
#endif

#endif /* INC_FLASH_H_ */
