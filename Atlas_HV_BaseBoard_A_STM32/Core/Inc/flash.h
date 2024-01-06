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
#include "app_params.h"

/*Base address of sector 7*/
#define BASE_PARAM_ADR 0x08060000


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
