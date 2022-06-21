/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "display.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SEG_Msk		(SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_F_Pin | SEG7_G_Pin | SEG7_DP_Pin)
#define SEG_MOD_Msk	(SEG7_DIG4_Pin | SEG7_DIG3_Pin | SEG7_DIG2_Pin | SEG7_DIG1_Pin)
#define SEG_SIGN	(SEG7_G_Pin)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// @formatter:off
const uint8_t SEG_Bin2Dec[] = {
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_F_Pin,// 0
		SEG7_B_Pin | SEG7_C_Pin,	// 1
		SEG7_A_Pin | SEG7_B_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_G_Pin,	// 2
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_G_Pin,	// 3
		SEG7_B_Pin | SEG7_C_Pin | SEG7_F_Pin | SEG7_G_Pin,	// 4
		SEG7_A_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_F_Pin | SEG7_G_Pin,	// 5
		SEG7_A_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_F_Pin	| SEG7_G_Pin,	// 6
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin,	// 7
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin	| SEG7_F_Pin | SEG7_G_Pin,	// 8
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_F_Pin	| SEG7_G_Pin,	// 9
		SEG7_A_Pin | SEG7_B_Pin | SEG7_C_Pin | SEG7_E_Pin | SEG7_F_Pin  | SEG7_G_Pin,  // A
		SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_F_Pin | SEG7_G_Pin,  // b
		SEG7_D_Pin | SEG7_E_Pin | SEG7_G_Pin,  // c
		SEG7_B_Pin | SEG7_C_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_G_Pin,  // d
		SEG7_A_Pin | SEG7_D_Pin | SEG7_E_Pin | SEG7_F_Pin | SEG7_G_Pin,  // E
		SEG7_A_Pin | SEG7_E_Pin | SEG7_F_Pin | SEG7_G_Pin,				 // F
};

const uint16_t SEG_Module[] = { SEG7_DIG4_Pin, SEG7_DIG3_Pin, SEG7_DIG2_Pin, SEG7_DIG1_Pin };
// @formatter:on
uint16_t SEG_Value[] = { 0, 0, 0, 0 };

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
void SEG_SetSegment(uint16_t value) {
	value &= SEG_Msk;
	HAL_GPIO_WritePin(GPIOG, SEG_Msk, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, value, GPIO_PIN_SET);
}

void SEG_SetModule(uint8_t module) {
	module &= 0x03;
	HAL_GPIO_WritePin(GPIOB, SEG_MOD_Msk, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_Module[module], GPIO_PIN_SET);
}

void SEG_Callback(void) {
	static uint16_t SEG_Delay = 0;
	static uint32_t module = 0;
	if ((++SEG_Delay) == SEG_RefreshPeriodMs) {
		HAL_GPIO_WritePin(GPIOB, SEG_MOD_Msk, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, SEG_Msk, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, SEG_Value[module], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_Module[module++], GPIO_PIN_SET);
		SEG_Delay = 0;
		module &= 0x03;
	}
}

void SEG_DisplayDec(int16_t value) {
	if ((value >= 0) && (value < 10000)) {
		SEG_Value[0] = (SEG_Bin2Dec[value % 10]);
		value /= 10;
		SEG_Value[1] = (value) ? (SEG_Bin2Dec[value % 10]) : 0;
		value /= 10;
		SEG_Value[2] = (value) ? (SEG_Bin2Dec[value % 10]) : 0;
		value /= 10;
		SEG_Value[3] = (value) ? (SEG_Bin2Dec[value % 10]) : 0;
	} else if ((value < 0) && (value > -1000)) {
		value = -value;
		SEG_Value[0] = (SEG_Bin2Dec[value % 10]);
		value /= 10;
		if (value != 0) {
			SEG_Value[1] = (SEG_Bin2Dec[value % 10]);
			value /= 10;
			if (value != 0) {
				SEG_Value[2] = (SEG_Bin2Dec[value % 10]);
				SEG_Value[3] = SEG7_G_Pin;
			} else {
				SEG_Value[2] = SEG7_G_Pin;
				SEG_Value[3] = 0;
			}
		} else {
			SEG_Value[1] = SEG7_G_Pin;
			SEG_Value[2] = 0;
			SEG_Value[3] = 0;
		}
	}
}

void BSP_SEG_DisplayFixedPoint(int16_t value, uint8_t fraction_digits) {
	if ((value >= 0) && (value < 10000)) {
		if ((fraction_digits > 0) && (fraction_digits < 4)) {
			SEG_Value[0] = SEG_Bin2Dec[value % 10];
			value /= 10;
			SEG_Value[1] =
					(value) ?
							SEG_Bin2Dec[value % 10] :
							((fraction_digits >= 1) ? SEG_Bin2Dec[0] : 0);
			value /= 10;
			SEG_Value[2] =
					(value) ?
							SEG_Bin2Dec[value % 10] :
							((fraction_digits >= 2) ? SEG_Bin2Dec[0] : 0);
			value /= 10;
			SEG_Value[3] =
					(value) ?
							SEG_Bin2Dec[value % 10] :
							((fraction_digits == 3) ? SEG_Bin2Dec[0] : 0);
		}
	} else if ((value < 0) && (value > -1000)) {
		if ((fraction_digits > 0) && (fraction_digits < 3)) {
			value = -value;
			SEG_Value[0] = SEG_Bin2Dec[value % 10];
			value /= 10;
			if (value) {
				SEG_Value[1] = SEG_Bin2Dec[value % 10];
				value /= 10;
				SEG_Value[2] =
						(value) ?
								SEG_Bin2Dec[value % 10] :
								((fraction_digits == 1) ?
										SEG7_G_Pin : SEG_Bin2Dec[0]);
				SEG_Value[3] = (fraction_digits == 2) ? SEG7_G_Pin : 0;

			} else {
				SEG_Value[1] = SEG_Bin2Dec[0];
				SEG_Value[2] =
						(fraction_digits == 1) ? SEG7_G_Pin : SEG_Bin2Dec[0];
				SEG_Value[3] = (fraction_digits == 2) ? SEG7_G_Pin : 0;
			}
		}
	}
	SEG_Value[fraction_digits] |= SEG7_DP_Pin;
}
