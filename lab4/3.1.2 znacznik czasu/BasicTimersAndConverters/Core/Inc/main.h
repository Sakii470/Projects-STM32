/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define SW_DOWN_Pin GPIO_PIN_2
#define SW_DOWN_GPIO_Port GPIOE
#define SW_UP_Pin GPIO_PIN_3
#define SW_UP_GPIO_Port GPIOE
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOE
#define LED6_Pin GPIO_PIN_5
#define LED6_GPIO_Port GPIOE
#define LED7_Pin GPIO_PIN_6
#define LED7_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_2
#define LCD_RS_GPIO_Port GPIOF
#define SEG7_DIG1_Pin GPIO_PIN_2
#define SEG7_DIG1_GPIO_Port GPIOB
#define SEG7_A_Pin GPIO_PIN_0
#define SEG7_A_GPIO_Port GPIOG
#define SEG7_B_Pin GPIO_PIN_1
#define SEG7_B_GPIO_Port GPIOG
#define LCD_D4_Pin GPIO_PIN_7
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_8
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_9
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_10
#define LCD_D7_GPIO_Port GPIOE
#define SW_OK_Pin GPIO_PIN_15
#define SW_OK_GPIO_Port GPIOE
#define LCD_BKL_Pin GPIO_PIN_13
#define LCD_BKL_GPIO_Port GPIOB
#define LCD_D0_Pin GPIO_PIN_14
#define LCD_D0_GPIO_Port GPIOD
#define LCD_D1_Pin GPIO_PIN_15
#define LCD_D1_GPIO_Port GPIOD
#define SEG7_C_Pin GPIO_PIN_2
#define SEG7_C_GPIO_Port GPIOG
#define SEG7_D_Pin GPIO_PIN_3
#define SEG7_D_GPIO_Port GPIOG
#define SEG7_E_Pin GPIO_PIN_4
#define SEG7_E_GPIO_Port GPIOG
#define SEG7_F_Pin GPIO_PIN_5
#define SEG7_F_GPIO_Port GPIOG
#define SEG7_G_Pin GPIO_PIN_6
#define SEG7_G_GPIO_Port GPIOG
#define LSM303C_I2C3_SCL_Pin GPIO_PIN_7
#define LSM303C_I2C3_SCL_GPIO_Port GPIOG
#define LSM303C_I2C3_SDA_Pin GPIO_PIN_8
#define LSM303C_I2C3_SDA_GPIO_Port GPIOG
#define LED0_Pin GPIO_PIN_6
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_9
#define LED3_GPIO_Port GPIOC
#define LCD_D2_Pin GPIO_PIN_0
#define LCD_D2_GPIO_Port GPIOD
#define LCD_D3_Pin GPIO_PIN_1
#define LCD_D3_GPIO_Port GPIOD
#define LED5_Pin GPIO_PIN_3
#define LED5_GPIO_Port GPIOD
#define LCD_RW_Pin GPIO_PIN_4
#define LCD_RW_GPIO_Port GPIOD
#define LCD_E_Pin GPIO_PIN_5
#define LCD_E_GPIO_Port GPIOD
#define SEG7_DP_Pin GPIO_PIN_9
#define SEG7_DP_GPIO_Port GPIOG
#define LSM303C_RDY_MAG_Pin GPIO_PIN_10
#define LSM303C_RDY_MAG_GPIO_Port GPIOG
#define LSM303C_RDY_MAG_EXTI_IRQn EXTI15_10_IRQn
#define LSM303C_INT_ACC_Pin GPIO_PIN_11
#define LSM303C_INT_ACC_GPIO_Port GPIOG
#define LSM303C_INT_ACC_EXTI_IRQn EXTI15_10_IRQn
#define LSM303C_INT_MAG_Pin GPIO_PIN_12
#define LSM303C_INT_MAG_GPIO_Port GPIOG
#define LSM303C_INT_MAG_EXTI_IRQn EXTI15_10_IRQn
#define LM75_I2C1_SDA_Pin GPIO_PIN_13
#define LM75_I2C1_SDA_GPIO_Port GPIOG
#define LM75_I2C1_SCL_Pin GPIO_PIN_14
#define LM75_I2C1_SCL_GPIO_Port GPIOG
#define LM75_INT_Pin GPIO_PIN_15
#define LM75_INT_GPIO_Port GPIOG
#define LM75_INT_EXTI_IRQn EXTI15_10_IRQn
#define SEG7_DIG2_Pin GPIO_PIN_3
#define SEG7_DIG2_GPIO_Port GPIOB
#define SEG7_DIG3_Pin GPIO_PIN_4
#define SEG7_DIG3_GPIO_Port GPIOB
#define SEG7_DIG4_Pin GPIO_PIN_5
#define SEG7_DIG4_GPIO_Port GPIOB
#define SW_RIGHT_Pin GPIO_PIN_0
#define SW_RIGHT_GPIO_Port GPIOE
#define SW_LEFT_Pin GPIO_PIN_1
#define SW_LEFT_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
