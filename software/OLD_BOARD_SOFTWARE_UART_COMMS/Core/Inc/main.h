/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

#include "stm32g4xx_ll_ucpd.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_dma.h"

#include "stm32g4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define DOWN_BTN_Pin GPIO_PIN_13
#define DOWN_BTN_GPIO_Port GPIOC
#define UP_BTN_Pin GPIO_PIN_14
#define UP_BTN_GPIO_Port GPIOC
#define ENTER_BTN_Pin GPIO_PIN_15
#define ENTER_BTN_GPIO_Port GPIOC
#define SIG_4_Pin GPIO_PIN_0
#define SIG_4_GPIO_Port GPIOC
#define SIG_2_Pin GPIO_PIN_1
#define SIG_2_GPIO_Port GPIOC
#define ADC_9_Pin GPIO_PIN_2
#define ADC_9_GPIO_Port GPIOC
#define ADC_10_Pin GPIO_PIN_3
#define ADC_10_GPIO_Port GPIOC
#define ADC_1_Pin GPIO_PIN_0
#define ADC_1_GPIO_Port GPIOA
#define ADC_2_Pin GPIO_PIN_1
#define ADC_2_GPIO_Port GPIOA
#define WAKE_BTN_Pin GPIO_PIN_2
#define WAKE_BTN_GPIO_Port GPIOA
#define ADC_4_Pin GPIO_PIN_3
#define ADC_4_GPIO_Port GPIOA
#define ADC_DAC_1_Pin GPIO_PIN_4
#define ADC_DAC_1_GPIO_Port GPIOA
#define ADC_DAC_2_Pin GPIO_PIN_5
#define ADC_DAC_2_GPIO_Port GPIOA
#define ADC_12_Pin GPIO_PIN_5
#define ADC_12_GPIO_Port GPIOC
#define PWM_OUT_Pin GPIO_PIN_0
#define PWM_OUT_GPIO_Port GPIOB
#define DIGITAL_IO_6_Pin GPIO_PIN_1
#define DIGITAL_IO_6_GPIO_Port GPIOB
#define PWR_STATUS_Pin GPIO_PIN_2
#define PWR_STATUS_GPIO_Port GPIOB
#define DIGITAL_IO_5_Pin GPIO_PIN_10
#define DIGITAL_IO_5_GPIO_Port GPIOB
#define DIGITAL_IO_4_Pin GPIO_PIN_11
#define DIGITAL_IO_4_GPIO_Port GPIOB
#define ADC_3_Pin GPIO_PIN_12
#define ADC_3_GPIO_Port GPIOB
#define DIGITAL_IO_3_Pin GPIO_PIN_13
#define DIGITAL_IO_3_GPIO_Port GPIOB
#define DIGITAL_IO_1_Pin GPIO_PIN_15
#define DIGITAL_IO_1_GPIO_Port GPIOB
#define COMMS_EN_1_Pin GPIO_PIN_6
#define COMMS_EN_1_GPIO_Port GPIOC
#define COMMS_EN_2_Pin GPIO_PIN_7
#define COMMS_EN_2_GPIO_Port GPIOC
#define COMMS_EN_3_Pin GPIO_PIN_8
#define COMMS_EN_3_GPIO_Port GPIOC
#define SD_SELECT_Pin GPIO_PIN_9
#define SD_SELECT_GPIO_Port GPIOC
#define ERROR_STATUS_Pin GPIO_PIN_15
#define ERROR_STATUS_GPIO_Port GPIOA
#define WARN_STATUS_Pin GPIO_PIN_5
#define WARN_STATUS_GPIO_Port GPIOB
#define OK_STATUS_Pin GPIO_PIN_7
#define OK_STATUS_GPIO_Port GPIOB
#define SD_CARD_DETECT_Pin GPIO_PIN_9
#define SD_CARD_DETECT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */