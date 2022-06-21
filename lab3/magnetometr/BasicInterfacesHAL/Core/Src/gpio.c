/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
struct LED_TypeDef {
	GPIO_TypeDef *port;
	uint16_t pin;
};

struct LED_TypeDef LEDs[] = { { LED0_GPIO_Port, LED0_Pin }, { LED1_GPIO_Port,
LED1_Pin }, { LED2_GPIO_Port, LED2_Pin }, { LED3_GPIO_Port, LED3_Pin }, {
LED4_GPIO_Port, LED4_Pin }, { LED5_GPIO_Port, LED5_Pin }, {
LED6_GPIO_Port, LED6_Pin }, { LED7_GPIO_Port, LED7_Pin } };

void LED_On(uint8_t led) {
	if (led < LED_N) {
		HAL_GPIO_WritePin(LEDs[led].port, LEDs[led].pin, GPIO_PIN_SET);
	}
}

void LED_Off(uint8_t led) {
	if (led < LED_N) {
		HAL_GPIO_WritePin(LEDs[led].port, LEDs[led].pin, GPIO_PIN_RESET);
	}
}

void LED_Toggle(uint8_t led) {
	if (led < LED_N) {
		HAL_GPIO_TogglePin(LEDs[led].port, LEDs[led].pin);
	}
}

void LEDs_SetValue(uint8_t value) {
	for (uint32_t i = 0; i < LED_N; i++) {
		if (value & 1)
			HAL_GPIO_WritePin(LEDs[i].port, LEDs[i].pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(LEDs[i].port, LEDs[i].pin, GPIO_PIN_RESET);
		value >>= 1;
	}
}

uint8_t LEDs_GetValue(void) {
	uint8_t value = 0;
	for (uint32_t i = 0; i < LED_N; i++) {
		if (HAL_GPIO_ReadPin(LEDs[i].port, LEDs[i].pin) == GPIO_PIN_SET) {
			value |= (1 << i);
		}
	}
	return value;
}

struct SW_TypeDef {
	GPIO_TypeDef *port;
	uint16_t pin;
};

struct SW_TypeDef SWs[] = { { SW_RIGHT_GPIO_Port, SW_RIGHT_Pin }, {
		SW_LEFT_GPIO_Port, SW_LEFT_Pin }, { SW_DOWN_GPIO_Port, SW_DOWN_Pin }, {
		SW_UP_GPIO_Port, SW_UP_Pin }, { SW_OK_GPIO_Port, SW_OK_Pin } };

static SW_State SwStateLast = SW_NULL;
static int8_t SwHorizontal = 0;
static int8_t SwVertical = 0;

SW_State SW_GetState(void) {
	SW_State state = SW_NULL;

	for (uint32_t i = 0; i < NELEMS(SWs); i++) {
		if (HAL_GPIO_ReadPin(SWs[i].port, SWs[i].pin) == GPIO_PIN_RESET) {
			state = (SW_State) i;
		}
	}
	return state;
}

SW_State SW_StateIsOK(void) {
	SW_State state = SW_NULL;

	if (HAL_GPIO_ReadPin(SWs[(uint32_t) SW_OK].port, SWs[(uint32_t) SW_OK].pin)
			== GPIO_PIN_RESET) {
		state = SW_OK;
	}
	return state;
}

SW_State SW_GetStateLast(void) {
	return SwStateLast;
}

int8_t SW_GetHorizontal(void) {
	return SwHorizontal;
}

int8_t SW_GetVertical(void) {
	return SwVertical;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	case SW_OK_Pin:
		SwStateLast = SW_OK;
		break;
	case SW_UP_Pin:
		SwStateLast = SW_UP;
		SwVertical++;
		break;
	case SW_DOWN_Pin:
		SwStateLast = SW_DOWN;
		SwVertical--;
		break;
	case SW_RIGHT_Pin:
		SwStateLast = SW_RIGHT;
		SwHorizontal++;
		break;
	case SW_LEFT_Pin:
		SwStateLast = SW_LEFT;
		SwHorizontal--;
		break;
	default:
		SwStateLast = SW_NULL;
		break;
	}
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED4_Pin|LED6_Pin|LED7_Pin|LCD_D4_Pin
                          |LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG7_DIG1_Pin|LCD_BKL_Pin|SEG7_DIG2_Pin|SEG7_DIG3_Pin
                          |SEG7_DIG4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, SEG7_A_Pin|SEG7_B_Pin|SEG7_C_Pin|SEG7_D_Pin
                          |SEG7_E_Pin|SEG7_F_Pin|SEG7_G_Pin|SEG7_DP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
                          |LED5_Pin|LCD_RW_Pin|LCD_E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin */
  GPIO_InitStruct.Pin = SW_DOWN_Pin|SW_UP_Pin|SW_OK_Pin|SW_RIGHT_Pin
                          |SW_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = LED4_Pin|LED6_Pin|LED7_Pin|LCD_D4_Pin
                          |LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = SEG7_DIG1_Pin|LCD_BKL_Pin|SEG7_DIG2_Pin|SEG7_DIG3_Pin
                          |SEG7_DIG4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = SEG7_A_Pin|SEG7_B_Pin|SEG7_C_Pin|SEG7_D_Pin
                          |SEG7_E_Pin|SEG7_F_Pin|SEG7_G_Pin|SEG7_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
                          |LED5_Pin|LCD_RW_Pin|LCD_E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/