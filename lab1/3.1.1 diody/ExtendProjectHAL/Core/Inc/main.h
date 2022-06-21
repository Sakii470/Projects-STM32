/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

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
#define SW1_DOWN_Pin GPIO_PIN_2
#define SW1_DOWN_GPIO_Port GPIOE
#define SW1_DOWN_EXTI_IRQn EXTI2_IRQn
#define SW1_UP_Pin GPIO_PIN_3
#define SW1_UP_GPIO_Port GPIOE
#define SW1_UP_EXTI_IRQn EXTI3_IRQn
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOE
#define LED6_Pin GPIO_PIN_5
#define LED6_GPIO_Port GPIOE
#define LED7_Pin GPIO_PIN_6
#define LED7_GPIO_Port GPIOE
#define SW1_OK_Pin GPIO_PIN_15
#define SW1_OK_GPIO_Port GPIOE
#define SW1_OK_EXTI_IRQn EXTI15_10_IRQn
#define LED0_Pin GPIO_PIN_6
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_9
#define LED3_GPIO_Port GPIOC
#define LED5_Pin GPIO_PIN_3
#define LED5_GPIO_Port GPIOD
#define SW1_RIGHT_Pin GPIO_PIN_0
#define SW1_RIGHT_GPIO_Port GPIOE
#define SW1_RIGHT_EXTI_IRQn EXTI0_IRQn
#define SW1_LEFT_Pin GPIO_PIN_1
#define SW1_LEFT_GPIO_Port GPIOE
#define SW1_LEFT_EXTI_IRQn EXTI1_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
