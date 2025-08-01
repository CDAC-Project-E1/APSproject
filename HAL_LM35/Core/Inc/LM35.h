/*
 * LM35.H
 *
 *  Created on: Jul 24, 2025
 *      Author: Vaishnavi
 */

#ifndef INC_LM35_H_
#define INC_LM35_H_

#include "stm32f4xx_hal.h"

void LM35_Init(ADC_HandleTypeDef *hadc);
float LM35_ReadTemperature(ADC_HandleTypeDef *hadc);

#endif /* INC_LM35_H_ */
