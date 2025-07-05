/*
 * lcd.h
 *
 *  Created on: Jul 2, 2025
 *      Author: durgesh
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define BV(x) (1 << (x))

#define LCD_SLAVE_ADDR_W  0x4E
#define LCD_SLAVE_ADDR_R  0x4F

void LcdInit(I2C_HandleTypeDef *hi2c);
void LcdWriteNibble(uint8_t cmd, uint8_t data);
void LcdWriteByte(uint8_t cmd, uint8_t data);
void LcdPuts(uint8_t line, char *str);

#define LCD_CMD			0
#define LCD_DATA		1
#define LCD_LINE1		0x80
#define LCD_LINE2		0xC0
#define LCD_CLEAR		0x01
#define LCD_ENTRYMODE	0x06
#define LCD_DISP_OFF	0x08
#define LCD_DISP_ON		0x0C
#define LCD_FNSET_1LINE		0x20
#define LCD_FNSET_2LINE		0x28

#define LCD_RS_Pos		0
#define LCD_RW_Pos		1
#define LCD_EN_Pos		2
#define LCD_BL_Pos		3

#endif /* INC_LCD_H_ */
