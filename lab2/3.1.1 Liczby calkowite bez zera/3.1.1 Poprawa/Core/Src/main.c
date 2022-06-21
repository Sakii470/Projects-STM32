/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEG7_Msk       (SEG7_A_Pin|SEG7_B_Pin|SEG7_C_Pin|SEG7_D_Pin|SEG7_E_Pin|SEG7_F_Pin|SEG7_G_Pin|SEG7_DP_Pin)

#define SEG7_MOD_Msk   (SEG7_DIG4_Pin|SEG7_DIG3_Pin|SEG7_DIG2_Pin|SEG7_DIG1_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

const uint8_t SEG_Bin2Dec[]=
{
		SEG7_A_Pin |SEG7_B_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_E_Pin |SEG7_F_Pin,
		SEG7_B_Pin |SEG7_C_Pin , //1
		SEG7_A_Pin |SEG7_B_Pin |SEG7_D_Pin |SEG7_E_Pin |SEG7_G_Pin, //2
		SEG7_A_Pin |SEG7_B_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_G_Pin,  //3
		SEG7_B_Pin |SEG7_C_Pin |SEG7_F_Pin |SEG7_G_Pin , //4
		SEG7_A_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_F_Pin |SEG7_G_Pin ,//5
		SEG7_A_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_E_Pin |SEG7_F_Pin |SEG7_G_Pin, //6
		SEG7_A_Pin |SEG7_B_Pin |SEG7_C_Pin, //7
		SEG7_A_Pin |SEG7_B_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_E_Pin |SEG7_F_Pin |SEG7_G_Pin , //8
		SEG7_A_Pin |SEG7_B_Pin |SEG7_C_Pin |SEG7_D_Pin |SEG7_F_Pin |SEG7_G_Pin ,//9

};

const uint16_t SEG_Module[]= {SEG7_DIG4_Pin, SEG7_DIG3_Pin, SEG7_DIG2_Pin, SEG7_DIG1_Pin};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void SEG_SetSegment (uint8_t value){
	value &= 0x0F;
	HAL_GPIO_WritePin(GPIOG, SEG7_Msk, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, SEG_Bin2Dec[value], GPIO_PIN_SET);

}

void SEG_SetModule(uint8_t module){
	module &= 0x03;
	HAL_GPIO_WritePin(GPIOB, SEG7_MOD_Msk, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_Module[module], GPIO_PIN_SET);
}

#define SEG_RefreshPeriodMs (5)

uint8_t SEG_Value[]={0,0,0,0};

 void SEG_Mux(void){
	static uint32_t module=0;
	if(SEG_Value[3] == 0 && SEG_Value[2] == 0 && SEG_Value[1] == 0)
			module = 0;
	else if (SEG_Value[3] == 0 && SEG_Value[2] == 0)
		module %= 2;
	else if (SEG_Value[3] == 0)
			module %= 3;

	SEG_SetSegment(SEG_Value[module]);
		SEG_SetModule(module++);

		module&=0x03;
}

void HAL_SYSTICK_Callback(void){
	static uint16_t SEG_Delay = 0;
	if((++SEG_Delay) == SEG_RefreshPeriodMs){
		SEG_Mux();
		SEG_Delay=0;
	}
}

void SEG_DisplayDec(uint16_t value){
	if((value >=0)&&(value<10000)){
		SEG_Value[0]=(value % 10);
		value /=10;
		SEG_Value[1]= value ? (value % 10) : 0;
		value /= 10;
		SEG_Value[2]= value ? (value % 10) : 0;
		value /= 10;
		SEG_Value[3]= value ? (value % 10) : 0;
		value /= 10;
	}
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  SEG_SetModule(0);
	  		for(int i=0; i<10000; i++)
	  		{
	  			SEG_DisplayDec(i);
	  			HAL_Delay(20);
	  		}

	  	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
