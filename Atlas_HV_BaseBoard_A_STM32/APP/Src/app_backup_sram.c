/*
 * app_backup_sram.c
 *
 *  Created on: Apr 2, 2022
 *      Author: tomas
 */

#include "app_backup_sram.h"

/********************************************************************************************
Tady mas ukazku fce na update toho parametru netusim kam si to budes chtit prcnout :D
void UpdateFlashParam(FlashSectorParams* s_Params,eSRAM_Offsets ParamType,uint32_t ParamValue)
{
/*
 * TODO : Tohle ti vezme tu tvoji strukturu (musi byt nekde tady se nevycte z flashky), a podle toho jaky zvolis parametr pomoci
 * enumu tak ti to k nemu priradi ParamValue hodnotu
 */
/*
	*((uint32_t*)(s_Params)+ParamType) = ParamValue;
}

********************************************************************************************/


/* @brief enable access to backup sram
 *
 */
void BACKUP_SRAM_enable(void)
{

    /* Enable the power interface clock */
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    /* Set the DBP bit to enable access to the backup domain */
    //PWR->CR |= PWR_CR_DBP;
    /* Enable the backup SRAM clock */
    //RCC->AHB1ENR |= RCC_AHB1ENR_BKPSRAMEN;
    /* Enable backup regulator */
    //PWR->CSR |= PWR_CSR_BRE;
    /* Wait for backup regulator to be ready  */
    //while (!(PWR->CSR & (PWR_FLAG_BRR)));

}

/* @brief read control registers with information about store information
 *
 * @param position -> position of data register
 * @param return valid of read data
 *
 */
bool BACKUP_SRAM_read_StoreControl(int position)
{
	/*
	uint32_t *addr_0 = (uint32_t *)BKPSRAM_BASE + (4 * sramOffset_StoreControl_0);
	if(*addr_0  != STORE_VALIDE_CODE) return false;

	uint32_t *addr_1 = (uint32_t *)BKPSRAM_BASE + (4 * sramOffset_StoreControl_1);

	uint32_t flag_reg = *addr_1;
	return  (flag_reg >> position) & 0x000001;
	*/

	return false;
}

/* @brief write to control registers with information about store information
 *
 * @param position -> position of data register
 * @param flag -> valid of data register
 *
 */
void BACKUP_SRAM_write_StoreControl(int position, bool flag)
{
	/*
	uint32_t *addr_0 = (uint32_t *)BKPSRAM_BASE + (4 * sramOffset_StoreControl_0);
	uint32_t *addr_1 = (uint32_t *)BKPSRAM_BASE + (4 * sramOffset_StoreControl_1);

	if((*addr_0)  != STORE_VALIDE_CODE)
	{
		*addr_0 = STORE_VALIDE_CODE;
		*addr_1 = 0;
	}

	uint32_t flag_reg = (*addr_1);

	if(flag)
	{
		flag_reg = flag_reg | (1 << position);
	}
	else
	{
		flag_reg = flag_reg &  ~(1 << position);
	}

	*addr_1 =  flag_reg;
*/
}

/* @brief read backup register
 *
 * @param word_offset -> position of data register
 * @return data register
 *
 */
uint32_t BACKUP_SRAM_read(int word_offset)
{
	/*
	uint32_t *addr = (uint32_t *)BKPSRAM_BASE + (4 * word_offset);

	return *addr;
	*/
	return 0;
}

/* @brief write to backup register
 *
 * @param word_offset -> position of data register
 * @param value -> data for write
 *
 */
void BACKUP_SRAM_write(int word_offset, uint32_t value)
{
	/*
	uint32_t *addr = (uint32_t *)BKPSRAM_BASE + (4 * word_offset);

	*addr = value;
	*/
}

/* @brief read backup register in float format
 *
 * @param word_offset -> position of data register
 * @return data register
 *
 */
float BACKUP_SRAM_read_float(int word_offset)
{
	/*
	float *addr = (float *)BKPSRAM_BASE + (4 * word_offset);

	return *addr;
	*/
	return 0;
}

/* @brief write to backup register in float format
 *
 * @param word_offset -> position of data register
 * @param value -> data for write
 *
 */
void BACKUP_SRAM_write_float(int word_offset, float value)
{
	/*
	float *addr = (float *)BKPSRAM_BASE + (4 * word_offset);

	*addr = value;
	*/
}
