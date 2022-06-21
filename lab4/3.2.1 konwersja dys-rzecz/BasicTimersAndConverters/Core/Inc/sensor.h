/*
 * sensor.h
 *
 *  Created on: Dec 13, 2021
 *      Author: pdabal
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

/* Includes ------------------------------------------------------------------*/
#include "lsm303c.h"

#define TEMP_LM75_RESOLUTION 		0.5f


typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
}ACC_XYZ_TypeDef;


int16_t TEMP_GetTempI(void);
float TEMP_GetTempF(void);

HAL_StatusTypeDef ACC_LSM303C_Init(uint8_t acc_datarate, uint8_t acc_fullscale);
void ACC_LSM303C_ReadXYZ(ACC_XYZ_TypeDef *res);

#endif /* INC_SENSOR_H_ */
