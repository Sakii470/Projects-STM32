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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sensor.h"
#include "display.h"
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct {
	uint16_t second;
	uint16_t milisecond;
	uint16_t microsecond;
}TimeStamp_t;;

#define TS30    ((uint16_t*)((uint32_t)0x1FFF75A8)) * 1.1
#define TS110   ((uint16_t*)((uint32_t)0x1FFF75CA)) * 1.1

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

TimeStamp_t timeStamp;
uint16_t second = 0;
FlagStatus update=RESET;

uint32_t analogWatchdogStatus = RESET;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

float calc_pwm(float val)
{
    const float k = 0.13f;
    const float x0 = 70.0f;
    return 10000.0f / (1.0f + exp(-k * (val - x0)));
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
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  char lcd[16];
  LCD_Init();
  LCD_BacklightOn();
uint32_t i=0;
uint16_t adcConversionValue[]={0,0};

 uint16_t  ADC_TEMP_3V3_30C =  (uint16_t*)(0x1FFF7A2C);
 uint16_t  ADC_TEMP_3V3_110C = (uint16_t*)(0x1FFF7A2E);

float adcCalTemp30C = ADC_TEMP_3V3_30C * 1.1;
float adcCalTemp110C = ADC_TEMP_3V3_110C * 1.1;






if(HAL_ADCEx_Calibration_Start(&hadc3, ADC_SINGLE_ENDED) != HAL_OK)
	Error_Handler();

	while (1) {



		if(HAL_ADC_Start(&hadc3) != HAL_OK)
			Error_Handler();

		//oczekiewanie na zakonczenie pomiaru na czujniku tempteratury
		while(__HAL_ADC_GET_FLAG(&hadc3, ADC_FLAG_EOC) != SET)
			;


		adcConversionValue[0] = HAL_ADC_GetValue(&hadc3);



		//oczekiwanie na zakonczenie pomiaru na potencjometrze
		while(__HAL_ADC_GET_FLAG(&hadc3, ADC_FLAG_EOC) != SET);


		adcConversionValue[1] = HAL_ADC_GetValue(&hadc3);
		//Naprzemienne wys zmierzonej wartosci


		sprintf(lcd, "%f",  adcConversionValue[1] * 3.3f/4096.0f);
				 LCD_WriteTextXY((uint8_t*) lcd, strlen(lcd), 1, 1);

				 float temperature = ((float)(adcConversionValue[0]) - adcCalTemp30C)/(adcCalTemp110C - adcCalTemp30C) * (110.0F - 30.0F) + 30.0F;

				   sprintf(lcd, "%f",  temperature);
				   				 LCD_WriteTextXY((uint8_t*) lcd, strlen(lcd), 2, 1);




		LEDs_SetValue((1<<(i++ & 1)) | (analogWatchdogStatus << 7));
		HAL_Delay(1000);
		analogWatchdogStatus = RESET;
	}

	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback(void) {
	SEG_Callback();
	SW_SysTickCallback();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM16){
		second++;
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM16){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			uint32_t microsecond = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) * 20;
			timeStamp.second=second;
			timeStamp.milisecond = (uint16_t)(microsecond/1000);
			timeStamp.microsecond= (uint16_t)(microsecond%1000);
			update=SET;
		}
	}
}

void HAL_ADC_LevelOutOfWindowcCallback(ADC_HandleTypeDef *hadc){
	analogWatchdogStatus= SET;
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