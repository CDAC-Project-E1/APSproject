/*
 * lcd.h
 *
 *  Created on: Jul 2, 2025
 *      Author: durgesh
 */

// lcd.h
#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

#define LCD_SLAVE_ADDR_W  0x4E  // 0x27 << 1

void LcdInit(I2C_HandleTypeDef *hi2c);
void LcdWriteByte(uint8_t cmd, uint8_t data);
void LcdPuts(uint8_t line, char *str);

#define LCD_CMD			0
#define LCD_DATA		1
#define LCD_LINE1		0x80
#define LCD_LINE2		0xC0

#endif
