/*
 * Flash.c
 *
 *  Created on: Oct 27, 2023
 *      Author: FarkasM
 */

#include "flash.h"



/*
 * Function returns Flash Sector by given address
 */
uint32_t Flash_GetSector(uint32_t StartSectorAddress)
{

  uint32_t sector = 0;

  if((StartSectorAddress < 0x08003FFF) && (StartSectorAddress >= 0x08000000))
	{
	  sector = FLASH_SECTOR_0;
	}
  else if((StartSectorAddress < 0x08007FFF) && (StartSectorAddress >= 0x08004000))
	{
	  sector = FLASH_SECTOR_1;
	}
  else if((StartSectorAddress < 0x0800BFFF) && (StartSectorAddress >= 0x08008000))
	{
	  sector = FLASH_SECTOR_2;
	}
  else if((StartSectorAddress < 0x0800FFFF) && (StartSectorAddress >= 0x0800C000))
	{
	  sector = FLASH_SECTOR_3;
	}
  else if((StartSectorAddress < 0x0801FFFF) && (StartSectorAddress >= 0x08010000))
	{
	  sector = FLASH_SECTOR_4;
	}
  else if((StartSectorAddress < 0x0803FFFF) && (StartSectorAddress >= 0x08020000))
	{
	  sector = FLASH_SECTOR_5;
	}
  else if((StartSectorAddress < 0x0805FFFF) && (StartSectorAddress >= 0x08040000))
	{
	  sector = FLASH_SECTOR_6;
	}
  else if((StartSectorAddress < 0x0807FFFF) && (StartSectorAddress >= 0x08060000))
	{
	  sector = FLASH_SECTOR_7;
	}

  return sector;
}


/*
 * Function writes given number of uint32_t words to given flash address
 * Function unlocks flash, erases needed sector(s), flash given memmory and locks Flash
 * Function returns 0 if there was no error
 */
uint32_t Flash_WriteData (uint32_t StartSectorAddress, uint32_t *Data, uint16_t NumOfWords)
{
  static FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t loc_Error;

  /* Unlock the Flash to enable the flash control register access */
  HAL_FLASH_Unlock();


  /* Get the number of sector to erase from 1st sector */

  uint32_t StartSector = Flash_GetSector(StartSectorAddress);
  uint32_t EndSectorAddress = StartSectorAddress + NumOfWords*4;
  uint32_t EndSector = Flash_GetSector(EndSectorAddress);

  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector        = StartSector;
  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

  /* Erase the user Flash area with given setting */
  /* Note!: Erase is done on whole sector/page */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &loc_Error) != HAL_OK)
  {
	  return HAL_FLASH_GetError ();
  }

  /* Program the user Flash area word by word*/

  for (uint16_t i = 0;  i < NumOfWords; i++) 
  {


	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, Data[i]) == HAL_OK)
    {
        //Shift address by 4 (Word Size)
    	StartSectorAddress += 4;  // StartPageAddress += 2 for half word and 8 for double word
    	//i++;
    }
    else
    {
      /* Error occurred while writing data in Flash memory*/
      return HAL_FLASH_GetError ();
    }
  }

  /* Lock the Flash to disable the flash control register access */
  HAL_FLASH_Lock();

  return 0;
}




/**************** FUNCTIONS SPECIFIC TO PARAMS IN SECTOR 7 **************/

/*
 * Read Data from fixed address in sector 7 given by BASE_PARAM_ADR
 * Data are read to FlashSectorParams struct
 */
void Flash_ReadParamStruct(FlashSectorParams* s_data)
{
	for (int i = 0; i < NUMBER_OF_PARAMS; i++)
	{
		*((uint32_t*)(s_data)+i)=*((uint32_t*)(BASE_PARAM_ADR+4*i));
	}
}

/*
 * Write Data to fixed address in sector 7 given by BASE_PARAM_ADR
 * Write data have FlashSectorParams struct format.. number of parametrs are given by NUMBER_OF_PARAMS define
 * Function returns 0 if there was no error
 */
uint32_t Flash_WriteParamStruct(FlashSectorParams ParamsData)
{
	 uint32_t loc_Error;

	 loc_Error = Flash_WriteData(BASE_PARAM_ADR,(uint32_t*)&ParamsData,NUMBER_OF_PARAMS);

	 return loc_Error;
}
