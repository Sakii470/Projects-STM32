/*
 * sensor.c
 *
 *  Created on: Dec 13, 2021
 *      Author: pdabal
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sensor.h"
#include "i2c.h"
#include "lsm303c.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ACC_LSM303C_I2C_ADDR 		 0x1D

#define TEMP_LM75_I2C_ADDR 			 0x48

#define TEMP_LM75_TEMP_REG 				0
#define TEMP_LM75_CONF_REG 				1
#define TEMP_LM75_THYS_REG 				2
#define TEMP_LM75_TOS_REG 				3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

uint8_t LM75_ReadRed8(uint8_t regAddr) {
	uint8_t regValue;
	if (HAL_I2C_Mem_Read(&hi2c1, TEMP_LM75_I2C_ADDR << 1, regAddr, 1,
			(uint8_t*) &regValue, 1, 1000) != HAL_OK)
		Error_Handler();
	return regValue;
}

uint16_t LM75_ReadReg16(uint8_t regAddr) {
	uint8_t regValue[2];
	if (HAL_I2C_Mem_Read(&hi2c1, TEMP_LM75_I2C_ADDR << 1, regAddr, 1,
			(uint8_t*) &regValue, 2, 1000) != HAL_OK)
		Error_Handler();
	return ((((uint16_t) regValue[0]) << 8) | regValue[1]);
}

int16_t TEMP_GetTempI(void) {
	return (LM75_ReadReg16(TEMP_LM75_TEMP_REG) >> 8);
}

float TEMP_GetTempF(void) {
	return ((LM75_ReadReg16(TEMP_LM75_TEMP_REG) >> 7) * TEMP_LM75_RESOLUTION);
}

/*----------------------------------------------------------------------------*/
HAL_StatusTypeDef ACC_LSM303C_Init(uint8_t acc_datarate, uint8_t acc_fullscale) {
	uint8_t reg[1];
	HAL_StatusTypeDef status;
	if (HAL_I2C_Mem_Read(&hi2c3, ACC_LSM303C_I2C_ADDR << 1,
	LSM303C_WHO_AM_I_ADDR, 1, reg, 1, 1000) != HAL_OK) {
		Error_Handler();
	} else {
		if (reg[0] != LSM303C_ACC_ID)
			return HAL_ERROR;
	}
	reg[0] = (acc_datarate | LSM303C_ACC_AXES_ENABLE);
	status = HAL_I2C_Mem_Write(&hi2c3, ACC_LSM303C_I2C_ADDR << 1,
	LSM303C_CTRL_REG1_A, 1, reg, 1, 1000);

	reg[0] = (acc_fullscale | 4);
	status = HAL_I2C_Mem_Write(&hi2c3, ACC_LSM303C_I2C_ADDR << 1,
	LSM303C_CTRL_REG4_A, 1, reg, 1, 1000);
	return status;
}

void ACC_LSM303C_ReadXYZ(ACC_XYZ_TypeDef *res) {
	if (HAL_I2C_Mem_Read(&hi2c3, ACC_LSM303C_I2C_ADDR << 1,
	LSM303C_OUT_X_L_A | 0x80, 1, (uint8_t*) res, 6, 1000) != HAL_OK)
		Error_Handler();
}
