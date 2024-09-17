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
#define MCP9804_ADDR 0b0011000 // the last 3 digits change for each pin
#define MCP9804_REG_TEMP 0x05

uint16_t Size = 8;

/*FATFS SDFatFs;    // File system object for SD card logical drive
FIL MyFile;       // File object
char SDPath[4];   // SD card logical drive path*/
/* USER CODE BEGIN PV */
//static void MX_SDMMC1_SD_Init(void);

int32_t readMCP9804Temp(uint8_t tempRegAddr) {
	uint8_t tempData[2];
	int32_t tempC = -100;
	uint8_t store = MCP9804_REG_TEMP;
	if (HAL_I2C_IsDeviceReady (&hi2c2, MCP9804_ADDR, 2, HAL_MAX_DELAY) == HAL_OK) { // Ready is unsuccessfull
			// Reception error
		if (HAL_I2C_Master_Transmit(&hi2c2, MCP9804_ADDR, &store, 1, HAL_MAX_DELAY) != HAL_OK) {
			HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
			HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
			HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
		} else {
			HAL_I2C_Master_Receive(&hi2c2, MCP9804_ADDR, tempData, 2, HAL_MAX_DELAY);
			uint16_t rawTemp = (tempData[0] << 8) | tempData[1];
			rawTemp &= 0x0FFF;  // Clear flags and keep 12 bits

			tempC = rawTemp & 0x0FFF;
			tempC /= 16.0;

			if (rawTemp & 0x1000) {  // Check sign bit
			  tempC -= 256.0;
			}
		}
	}
    return tempC;
}


uint8_t UpperByte, LowerByte;


int32_t Read_Temperature(void) {
	int32_t Temperature = -100;
    uint8_t AddressByte = (MCP9804_ADDR << 1); // Convert 7-bit to 8-bit address
    uint8_t TA_Register = 0x05;
    uint8_t anded = (AddressByte & 0xFE);
    uint8_t read = (AddressByte | 0x01);
    uint8_t data[2];
    // WRITE command
    if (HAL_I2C_Master_Transmit(&hi2c2, MCP9804_ADDR, &TA_Register, 5, HAL_MAX_DELAY) != HAL_OK) {
    	//HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
    	HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    	HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
        //return;
    }
    // Send REPEAT START and READ command
    if (HAL_I2C_Master_Receive_IT(&hi2c2, read, &data, 2) != HAL_OK) {
    	//HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
    	HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    	HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
        //return;
    }
    // Convert to temperature
    if ((UpperByte & 0x10) == 0x10) {
        // TA < 0°C
        UpperByte = UpperByte & 0x0F; // Clear SIGN
        Temperature = 256 - (UpperByte * 16 + LowerByte / 16.0);
    } else {
        // TA ≥ 0°C
        Temperature = (UpperByte * 16 + LowerByte / 16.0);
    }
    return Temperature;
}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

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
  uint32_t status = HAL_ERROR;

    int num_bytes = 4;

    uint8_t dataToSend[4];
    dataToSend[0] = 0xFF;// Example data
    dataToSend[1] = 0x5;// Example data
    dataToSend[2] = 0xF0;// Example data
    dataToSend[3] = 0xF;// Example data

    //HAL_StatusTypeDef sts = HAL_OK;

    HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn off success LED
    HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn off error LED
    HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_SET); // Turn off error LED


    if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
            // Initialization error
  	  HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on status LED
        }
    uint8_t tempRegAddr = 0x05;
    uint8_t buffer[255];

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    	HAL_Delay(1000);
    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // CS low Digital IO 1 COMM_EN_3
    	status = HAL_SPI_Transmit(&hspi1, (uint8_t *)&dataToSend, num_bytes, HAL_MAX_DELAY);
    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // CS high Digital IO 1 COMM_EN_3

    	if (status == HAL_OK)
    	{
    		HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
    		HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    		HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    	} else if (status == HAL_BUSY){
    		HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    		HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_RESET); // Turn on error LED
    		HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
    	}
    	else
    	{
    		HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on error LED
    		HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    		HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
    	}


    	HAL_Delay(1000);
    	HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_SET); // Turn off error LED
    	HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
    	HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
    	//int32_t tempC = readMCP9804Temp(MCP9804_ADDR);
    	uint8_t tempData[2];
		int32_t tempC = -100;
		uint8_t store = MCP9804_REG_TEMP;
		if (HAL_I2C_IsDeviceReady (&hi2c2, MCP9804_ADDR, 2, HAL_MAX_DELAY) == HAL_OK) { // Ready is unsuccessfull
				// Reception error
			if (HAL_I2C_Master_Transmit(&hi2c2, MCP9804_ADDR, &store, 1, HAL_MAX_DELAY) != HAL_OK) {
				HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
				HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
				HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
			} else {
				HAL_I2C_Master_Receive(&hi2c2, MCP9804_ADDR, tempData, 2, HAL_MAX_DELAY);
				uint16_t rawTemp = (tempData[0] << 8) | tempData[1];
				rawTemp &= 0x0FFF;  // Clear flags and keep 12 bits

				tempC = rawTemp & 0x0FFF;
				tempC /= 16.0;

				if (rawTemp & 0x1000) {  // Check sign bit
				  tempC -= 256.0;
				}
			}
		} else {
			HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
			HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_SET); // Turn of error LED
			HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_SET); // Turn of success LED
		}
    	//int32_t tempC = tempRegAddrRead_Temperature();
    	/*if ((tempC >= 120)) {
    		//temp read error
    		HAL_GPIO_WritePin(ERROR_STATUS_GPIO_Port, ERROR_STATUS_Pin, GPIO_PIN_RESET); // Turn on error LED
    		HAL_GPIO_WritePin(WARN_STATUS_GPIO_Port, WARN_STATUS_Pin, GPIO_PIN_RESET); // Turn on error LED
    		HAL_GPIO_WritePin(OK_STATUS_GPIO_Port, OK_STATUS_Pin, GPIO_PIN_RESET); // Turn on success LED
    	} */
    	dataToSend[0] = (tempC >> 24) & 0xFF;
    	dataToSend[1] = (tempC >> 16) & 0xFF;
    	dataToSend[2] = (tempC >> 8) & 0xFF;
    	dataToSend[3] = tempC & 0xFF;

    	HAL_Delay(100);
    	int amount_of_bytes = snprintf((char*) buffer, sizeof(buffer), "Temp:%ld \r\n" , tempC);
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




        /* USER CODE BEGIN 3 */
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
