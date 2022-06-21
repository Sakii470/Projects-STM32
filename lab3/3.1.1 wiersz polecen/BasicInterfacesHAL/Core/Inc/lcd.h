#ifndef INC_LCD_H_
#define INC_LCD_H_

/* Includes ------------------------------------------------------------------*/
#include "hd44780.h"
/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Initialize HD44780 2x16 LCD display.
 * The function should be called before using any other LCD display function.
 * It initializes GPIO lines and performs HD44780 initialization sequence. */
void LCD_Init(void);
/* Turn on LDC backlight. */
void LCD_BacklightOn(void);
/* Turn off LDC backlight. */
void LCD_BacklightOff(void);
/* Clear the LCD display. */
void LCD_Clear(void);
/* Set Cursor to a specified location given by row and column information
 * @param  Row Number (1 to 2)
 * @param  Column Number (1 to 16) Assuming a 2 X 16 characters display */
void LCD_GoTo(uint8_t row, uint8_t column);
/* Display a character string of a given length on the LCD display.
 * @param data: string to display
 * @param len:  length of the string to display
 */
void LCD_WriteText(uint8_t *text);
/* Display a character string of a given length on the LCD display.
 * The string is displayed in a given row, starting from a given column.
 * @param data: string to display
 * @param len:  length of the string to display
 * @param row:  row to display string in - can be 1 - first row - or 2 - second row
 * @param col:  column to put the first character of the string in - can be 1-16
 */
void LCD_WriteTextXY(uint8_t *data, uint8_t len, uint8_t row, uint8_t col);
void LCD_WriteFormatInt(uint8_t *buffor, const uint8_t *formater, int32_t num);

void LCD_SetUserChar(int8_t charNum, uint8_t n, const int8_t *p);
void LCD_WriteBinary(uint32_t var, uint8_t bitCount);

void LCD_ShiftLeft(void);
void LCD_ShiftRight(void);

#endif /* INC_LCD_H_ */
