/*
 * lcd.c
 *
 *  Created on: Nov 24, 2021
 *      Author: pdabal
 */

#include "main.h"
#include "lcd.h"

#include <stdio.h>

#define LCD_DATA_GPIOD_MSK	(LCD_D0_Pin | LCD_D1_Pin | LCD_D2_Pin | LCD_D3_Pin)
#define LCD_DATA_GPIOE_MSK	(LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin)

struct LCD_TypeDef {
	GPIO_TypeDef *port;
	uint16_t pin;
};

// @formatter:off
struct LCD_TypeDef LCD_Defs[8] = {
		{ LCD_D0_GPIO_Port, LCD_D0_Pin }, { LCD_D1_GPIO_Port, LCD_D1_Pin },
		{ LCD_D2_GPIO_Port, LCD_D2_Pin }, { LCD_D3_GPIO_Port, LCD_D3_Pin },
		{ LCD_D4_GPIO_Port, LCD_D4_Pin }, { LCD_D5_GPIO_Port, LCD_D5_Pin },
		{ LCD_D6_GPIO_Port, LCD_D6_Pin }, { LCD_D7_GPIO_Port, LCD_D7_Pin },
};
// @formatter:on

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
static void LCD_Write(uint8_t data) {
	HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);

	for (uint32_t i = 0; i < 8; ++i) {
		HAL_GPIO_WritePin(LCD_Defs[i].port, LCD_Defs[i].pin, (data >> i) & 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}

	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
	HAL_Delay(2);
}

static uint8_t LCD_Read(void) {
	uint8_t data;

	HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);

	for (uint32_t i = 0; i < 8; ++i) {
		data |= ((uint8_t) HAL_GPIO_ReadPin(LCD_Defs[i].port, LCD_Defs[i].pin) << i);
	}
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);

	return data;
}

static uint8_t LCD_ReadStatus(void) {
	unsigned char status = 0;
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;

	GPIO_InitStruct.Pin = LCD_D0_Pin | LCD_D1_Pin | LCD_D2_Pin | LCD_D3_Pin;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);

	status = LCD_Read();

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	GPIO_InitStruct.Pin = LCD_D0_Pin | LCD_D1_Pin | LCD_D2_Pin | LCD_D3_Pin;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	return status;
}
/* Send command to LCD module */
static void LCD_Cmd(unsigned char cmd) {
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	LCD_Write(cmd);

	while (LCD_ReadStatus() & 0x80)
		;
}

/* Send data to LCD module */
static void LCD_Data(uint8_t data) {
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	LCD_Write(data);

	while (LCD_ReadStatus() & 0x80)
		;
}

/* Activate Power Pin that supplies LCD module */
void LCD_BacklightOn(void) {
	HAL_GPIO_WritePin(LCD_BKL_GPIO_Port, LCD_BKL_Pin, GPIO_PIN_SET);
}

/* Disable Power Pin that supplies LCD module */
void LCD_BacklightOff(void) {
	HAL_GPIO_WritePin(LCD_BKL_GPIO_Port, LCD_BKL_Pin, GPIO_PIN_RESET);
}

/* Clear LCD module display */
void LCD_Clear(void) {
	LCD_Cmd(HD44780_CLEAR);
}

/* Initializes HD44780 LCD module in 4-bit mode */
void LCD_Init(void) {
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_Delay(40); 		//
	LCD_Cmd(HD44780_FUNCTION_SET | HD44780_8_BIT);
	HAL_Delay(5); 		//
	LCD_Cmd(HD44780_FUNCTION_SET | HD44780_8_BIT);
	HAL_Delay(1); 		//
	LCD_Cmd(HD44780_FUNCTION_SET | HD44780_8_BIT);

	LCD_Cmd(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_8_BIT);
	LCD_Cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF);
	LCD_Cmd(HD44780_CLEAR);
	HAL_Delay(5);
	LCD_Cmd(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);
	LCD_Cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON);
}

/* Set Cursor to a specified location given by row and column information
 * @param  Row Number (1 to 2)
 * @param  Column Number (1 to 16) Assuming a 2 X 16 characters display */
void LCD_GoTo(uint8_t row, uint8_t column) {
	column--;
	switch (row) {
	case 1:
		/* Set cursor to 1st row address and add index*/
		LCD_Cmd(column |= 0x80);
		break;
	case 2:
		/* Set cursor to 2nd row address and add index*/
		LCD_Cmd(column |= 0x40 | 0x80);
		break;
	default:
		break;
	}
}

/* Display a characters string */
void LCD_WriteTextXY(uint8_t *data, uint8_t len, uint8_t row, uint8_t col) {
	LCD_GoTo(row, col);
	while (len-- > 0) {
		LCD_Data(*data++);
	}
}

void LCD_WriteText(uint8_t *text) {
	while (*text)
		LCD_Data(*text++);
}

void LCD_WriteFormatInt(uint8_t *buffor, const uint8_t *formater, int32_t num) {
	sprintf((char*) buffor, (const char*) formater, num);
	while (*buffor)
		LCD_Data(*buffor++);
}

void LCD_SetUserChar(int8_t charNum, uint8_t n, const int8_t *p) {
	LCD_Cmd(HD44780_CGRAM_SET | charNum * 8);
	n *= 8;
	do {
		LCD_Data(*p++);
	} while (--n);
}

void LCD_WriteBinary(uint32_t var, uint8_t bitCount) {
	signed char i;

	for (i = (bitCount - 1); i >= 0; i--) {
		LCD_Data((var & (1 << i)) ? '1' : '0');
	}
}

void LCD_ShiftLeft(void) {
	LCD_Cmd(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_LEFT | HD44780_SHIFT_DISPLAY);
}

void LCD_ShiftRight(void) {
	LCD_Cmd(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_RIGHT | HD44780_SHIFT_DISPLAY);
}

