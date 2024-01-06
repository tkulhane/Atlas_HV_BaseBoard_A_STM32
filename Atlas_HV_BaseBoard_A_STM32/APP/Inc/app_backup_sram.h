/*
 * app_backup_sram.h
 *
 *  Created on: Apr 2, 2022
 *      Author: tomas
 */

#ifndef INC_APP_BACKUP_SRAM_H_
#define INC_APP_BACKUP_SRAM_H_

#include "main.h"

//#define STORE_VALIDE_CODE 0xA4B7A4B7

typedef enum
{
	sramOffset_StoreControl_0,
	sramOffset_StoreControl_1,
	sramOffset_IP_ADDRESS,
	sramOffset_NETMASK_ADDRESS,
	sramOffset_GATEWAY_ADDRESS,
	sramOffset_ReadCoef_k_0,
	sramOffset_ReadCoef_k_1,
	sramOffset_ReadCoef_k_2,
	sramOffset_ReadCoef_k_3,
	sramOffset_ReadCoef_k_4,
	sramOffset_ReadCoef_k_5,
	sramOffset_ReadCoef_q_0,
	sramOffset_ReadCoef_q_1,
	sramOffset_ReadCoef_q_2,
	sramOffset_ReadCoef_q_3,
	sramOffset_ReadCoef_q_4,
	sramOffset_ReadCoef_q_5,
	sramOffset_AdjCoef_k_ch0,
	sramOffset_AdjCoef_k_ch1,
	sramOffset_AdjCoef_k_ch2,
	sramOffset_AdjCoef_q_ch0,
	sramOffset_AdjCoef_q_ch1,
	sramOffset_AdjCoef_q_ch2

}eSRAM_Offsets;

void BACKUP_SRAM_enable(void);
bool BACKUP_SRAM_read_StoreControl(int id);
void BACKUP_SRAM_write_StoreControl(int id, bool flag);
uint32_t BACKUP_SRAM_read(int word_offset);
void BACKUP_SRAM_write(int word_offset, uint32_t value);
float BACKUP_SRAM_read_float(int word_offset);
void BACKUP_SRAM_write_float(int word_offset, float value);

#endif /* INC_APP_BACKUP_SRAM_H_ */
