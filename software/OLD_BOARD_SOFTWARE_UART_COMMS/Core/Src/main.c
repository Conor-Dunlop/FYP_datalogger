/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "ucpd.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// SPI_HandleTypeDef hspi1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char fmt[] = "ADC:%d,count:%d,count_btn:%d,state:\"%.4s\"\r\n";
char states[][5] = {
  "work",
  "off ",
  "low ",
  "help",
  "okok",
};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void){

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_DAC1_Init();
  MX_SPI1_Init();
  MX_UCPD1_Init();
  MX_I2C2_Init();
  MX_RTC_Init();
  MX_USB_Device_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  adc_t ADC_1 = {
    .config = {
      .Channel = ADC_CHANNEL_1,
      .Rank = ADC_REGULAR_RANK_1,
      .SamplingTime = ADC_SAMPLETIME_6CYCLES_5,
      .SingleDiff = ADC_SINGLE_ENDED,
      .OffsetNumber = ADC_OFFSET_NONE,
      .Offset = 0
    },
    .hadc = &hadc1
  };
  

  uint8_t count = 0;
  uint8_t count_btn = 0;
  uint8_t count_state = 0;
  uint8_t buffer[255];
  // uint16_t ADC = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  if (HAL_GPIO_ReadPin(DOWN_BTN_GPIO_Port, DOWN_BTN_Pin) == GPIO_PIN_SET) count_btn--;
  if (HAL_GPIO_ReadPin(UP_BTN_GPIO_Port, UP_BTN_Pin) == GPIO_PIN_SET) count_btn++;
  if (HAL_GPIO_ReadPin(ENTER_BTN_GPIO_Port, ENTER_BTN_Pin) == GPIO_PIN_SET) count_state++;
  if (count_state >= 5) count_state = 0; 

  int amount_of_bytes = snprintf((char*) buffer, sizeof(buffer), fmt, ADC_Get_val(&ADC_1), count++, count_btn, states[count_state]);
  // int amount_of_bytes = snprintf((char*) spi_buf, sizeof(spi_buf), "%d    ", count++);
  // HAL_GPIO_WritePin(COMMS_EN_1_GPIO_Port, COMMS_EN_1_Pin, GPIO_PIN_RESET); 
  // int status = HAL_SPI_Transmit(&hspi3, spi_buf, amount_of_bytes+4, 1);
  // int status = HAL_SPI_Transmit(&hspi3, &count, 1, 1);
  // HAL_GPIO_WritePin(COMMS_EN_1_GPIO_Port, COMMS_EN_1_Pin, GPIO_PIN_SET);   
  // USB_Print("count : %d", count++);

  switch (CDC_Transmit_FS((uint8_t*)buffer, amount_of_bytes)){
  case USBD_OK: // if the usb serial is ok it will blink green
    HAL_GPIO_TogglePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin);
    break;
   case USBD_BUSY: // if the device is busy i.e. plugged in but not monitoring it will blink blue
    HAL_GPIO_TogglePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin);
    break;
  case USBD_FAIL: // if the device can support USB coms device it will blink red
    HAL_GPIO_TogglePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin);
    break; 
  default:
    break;
  }
  HAL_UART_Transmit(&huart4, (uint8_t *)&buffer, amount_of_bytes, 0xFFFF);
  HAL_Delay(100);
  amount_of_bytes = snprintf((char*) buffer, sizeof(buffer), "DOWN : %d, UP : %d, enter : %d\r\n", HAL_GPIO_ReadPin(DOWN_BTN_GPIO_Port, DOWN_BTN_Pin),HAL_GPIO_ReadPin(UP_BTN_GPIO_Port, UP_BTN_Pin),HAL_GPIO_ReadPin(ENTER_BTN_GPIO_Port, ENTER_BTN_Pin));
  
  // i should really make this in to a function
  switch (CDC_Transmit_FS((uint8_t*)buffer, amount_of_bytes)){
  case USBD_OK: // if the usb serial is ok it will blink green
    HAL_GPIO_TogglePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin);
    break;
   case USBD_BUSY: // if the device is busy i.e. plugged in but not monitoring it will blink blue
    HAL_GPIO_TogglePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin);
    break;
  case USBD_FAIL: // if the device can support USB coms device it will blink red
    HAL_GPIO_TogglePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin);
    break; 
  default:
    break;
  }


  HAL_Delay(400);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
