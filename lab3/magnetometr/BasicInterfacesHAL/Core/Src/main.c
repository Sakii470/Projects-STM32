/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display.h"
#include "lcd.h"
#include "lsm303c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} MGG_XYZ_TypeDef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMP_LM75_I2C_ADDR 0X48

#define TEMP_LM75_TEMP_REG 0
#define TEMP_LM75_CONF_REG 1
#define TEMP_LM75_THYS_REG 2
#define TEMP_LM75_TOS_REG 3
#define TEMP_LM75_MAG_REG 4


#define TEMP_LM75_RESOLUTION 0.5f
#define ACC_LSM303C_I2C_ADDR 0x1D
#define MGG_LSM303C_I2C_ADDR 0x1E
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t LM75_ReadReg8(uint8_t regAddr){
	uint8_t regValue;
	if (HAL_I2C_Mem_Read(&hi2c1, TEMP_LM75_I2C_ADDR << 1, regAddr, 1,
			(uint8_t*) &regValue, 1, 1000) != HAL_OK)
		Error_Handler();
	return regValue;
}

uint16_t LM75_ReadReg16(uint8_t regAddr){
	uint8_t regValue[2];
	if (HAL_I2C_Mem_Read(&hi2c1,TEMP_LM75_I2C_ADDR << 1, regAddr, 1,
			(uint8_t*) regValue, 2, 1000) != HAL_OK)
		Error_Handler();
	return ((((uint16_t)regValue[0]) << 8) | regValue[1]);
}

int16_t TEMP_GetTempI(void) {
	return (LM75_ReadReg16(TEMP_LM75_TEMP_REG) >> 8);
}

float TEMP_GetTempF(void) {
	return ((LM75_ReadReg16(TEMP_LM75_TEMP_REG) >> 7)
			* TEMP_LM75_RESOLUTION);
}




HAL_StatusTypeDef MGG_LSM303C_Init(uint8_t mgg_datarate, uint8_t mgg_fullscale){
	uint8_t reg[1];
	HAL_StatusTypeDef status;
	if (HAL_I2C_Mem_Read(&hi2c3, MGG_LSM303C_I2C_ADDR << 1,
			LSM303C_WHO_AM_I_ADDR, 1, reg, 1, 1000) != HAL_OK) {
		Error_Handler();
	} else {
		if (reg[0] != LMS303C_MAG_ID)
				return HAL_ERROR;
	}
	reg[0] = (mgg_datarate | LSM303C_MAG_OM_XY_HIGH);
	status = HAL_I2C_Mem_Write(&hi2c3, MGG_LSM303C_I2C_ADDR << 1,
			LSM303C_CTRL_REG1_A, 1, reg, 1, 1000);

	reg[0] = (mgg_fullscale | 4);
		status = HAL_I2C_Mem_Write(&hi2c3, MGG_LSM303C_I2C_ADDR << 1,
				LSM303C_CTRL_REG4_A, 1, reg, 1, 1000);

	return status;
}

void MGG_LSM303C_ReadXYZ(MGG_XYZ_TypeDef *res) {
	if (HAL_I2C_Mem_Read(&hi2c3, MGG_LSM303C_I2C_ADDR << 1,
			LSM303C_OUT_X_L_A | 0x80, 1, (uint8_t*)res, 6, 1000) != HAL_OK)
		Error_Handler();
}
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
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  MGG_XYZ_TypeDef mgg;
  MGG_LSM303C_Init(LSM303C_MAG_ODR_10_HZ,LSM303C_MAG_FS_16_GA );
	while (1) {
		LED_Toggle(0);
		MGG_LSM303C_ReadXYZ(&mgg);
		HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t *)&mgg, 6);
		HAL_Delay(100);
    /* USER CODE END WHILE */

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback(void) {
	SEG_Callback();
}
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
	while (1) {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
