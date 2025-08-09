/*
 * lcd.c
 *
 *  Created on: Jul 2, 2025
 *      Author: durgesh
 */
#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;
static I2C_HandleTypeDef *lcd_i2c;

void LcdInit(I2C_HandleTypeDef *hi2c){
	lcd_i2c = hi2c;
	HAL_Delay(20);
	LcdWriteNibble(LCD_CMD, 0x03);
	HAL_Delay(5);
	LcdWriteNibble(LCD_CMD, 0x03);
	HAL_Delay(1);
	LcdWriteNibble(LCD_CMD, 0x03);
	HAL_Delay(1);
	LcdWriteNibble(LCD_CMD, 0x02);
	HAL_Delay(1);

	LcdWriteByte(LCD_CMD, LCD_FNSET_2LINE);
	LcdWriteByte(LCD_CMD, LCD_DISP_OFF);
	LcdWriteByte(LCD_CMD, LCD_CLEAR);
	LcdWriteByte(LCD_CMD, LCD_ENTRYMODE);
	LcdWriteByte(LCD_CMD, LCD_DISP_ON);
}

void LcdWriteNibble(uint8_t cmd, uint8_t data){
	uint8_t rsFlag = (cmd == LCD_DATA) ? BV(LCD_RS_Pos) : 0;
	uint8_t val;

	val = (data << 4) | rsFlag | BV(LCD_BL_Pos) | BV(LCD_EN_Pos);
	HAL_I2C_Master_Transmit(lcd_i2c, LCD_SLAVE_ADDR_W, &val, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
	val = (data << 4) | rsFlag | BV(LCD_BL_Pos);
	HAL_I2C_Master_Transmit(lcd_i2c, LCD_SLAVE_ADDR_W, &val, 1, HAL_MAX_DELAY);

}

void LcdWriteByte(uint8_t cmd, uint8_t data){
	uint8_t high = data >> 4;
	uint8_t low = data & 0x0F;
	LcdWriteNibble(cmd, high);
	LcdWriteNibble(cmd, low);
	HAL_Delay(1);
}

void LcdPuts(uint8_t line, char *str){
	LcdWriteByte(LCD_CMD, line);
	for(int i=0 ; str[i] != '\0'; i++){
		LcdWriteByte(LCD_DATA, str[i]);
	}
}

