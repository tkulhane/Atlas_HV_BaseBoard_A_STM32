/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SWREV_3_Pin GPIO_PIN_13
#define SWREV_3_GPIO_Port GPIOC
#define SWREV_2_Pin GPIO_PIN_14
#define SWREV_2_GPIO_Port GPIOC
#define SWREV_1_Pin GPIO_PIN_15
#define SWREV_1_GPIO_Port GPIOC
#define SWDIR_3_Pin GPIO_PIN_0
#define SWDIR_3_GPIO_Port GPIOC
#define SWDIR_2_Pin GPIO_PIN_1
#define SWDIR_2_GPIO_Port GPIOC
#define SWDIR_1_Pin GPIO_PIN_2
#define SWDIR_1_GPIO_Port GPIOC
#define EN_1_Pin GPIO_PIN_3
#define EN_1_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define PG_1_Pin GPIO_PIN_4
#define PG_1_GPIO_Port GPIOC
#define PG_2_Pin GPIO_PIN_5
#define PG_2_GPIO_Port GPIOC
#define PG_3_Pin GPIO_PIN_2
#define PG_3_GPIO_Port GPIOB
#define PWR_EN_Pin GPIO_PIN_10
#define PWR_EN_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define OC_1_Pin GPIO_PIN_6
#define OC_1_GPIO_Port GPIOC
#define OC_2_Pin GPIO_PIN_7
#define OC_2_GPIO_Port GPIOC
#define OC_3_Pin GPIO_PIN_8
#define OC_3_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_9
#define LED_0_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_8
#define LED_1_GPIO_Port GPIOA
#define EXT_0_Pin GPIO_PIN_9
#define EXT_0_GPIO_Port GPIOA
#define EXT_1_Pin GPIO_PIN_11
#define EXT_1_GPIO_Port GPIOA
#define SPI3_CS_Pin GPIO_PIN_15
#define SPI3_CS_GPIO_Port GPIOA
#define W55_RST_Pin GPIO_PIN_3
#define W55_RST_GPIO_Port GPIOB
#define W55_INT_Pin GPIO_PIN_4
#define W55_INT_GPIO_Port GPIOB
#define LED_2_Pin GPIO_PIN_5
#define LED_2_GPIO_Port GPIOB
#define EN_3_Pin GPIO_PIN_8
#define EN_3_GPIO_Port GPIOB
#define EN_2_Pin GPIO_PIN_9
#define EN_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
