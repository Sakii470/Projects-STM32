#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/* Includes ------------------------------------------------------------------*/
#define SEG_RefreshPeriodMs		(5)

/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
void SEG_SetSegment(uint16_t value);
void SEG_SetModule(uint8_t module);

void SEG_DisplayDec(int16_t value);
void BSP_SEG_DisplayFixedPoint(int16_t value, uint8_t fraction_digits);

void SEG_Callback(void);

#endif /* INC_DISPLAY_H_ */
