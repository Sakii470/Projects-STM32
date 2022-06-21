/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define LED_N			NELEMS(LEDs)

typedef enum {
	SW_RIGHT, SW_LEFT, SW_DOWN, SW_UP, SW_OK, SW_NULL
} SW_State;

#define SW_RefreshPeriodMs		(20)
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void LED_On(uint8_t led);
void LED_Off(uint8_t led);
void LED_Toggle(uint8_t led);

void LEDs_SetValue(uint8_t value);
uint8_t LEDs_GetValue(void);

SW_State SW_GetState(void);
SW_State SW_StateIsOK(void);

SW_State SW_GetStateLast(void);
uint8_t SW_GetChange(void);

int8_t SW_GetHorizontal(void);
int8_t SW_GetVertical(void);

void SW_SysTickCallback(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

