/*
 * lcd.c
 *
 *  Created on: Jul 2, 2025
 *      Author: durgesh
 */
// lcd.c
#include "lcd.h"

static I2C_HandleTypeDef *lcd_i2c;

#define EN  (1 << 2)
#define RS  (1 << 0)
#define BL  (1 << 3)

static void LcdSendNibble(uint8_t nibble, uint8_t control) {
    uint8_t data = (nibble << 4) | control | BL | EN;
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_SLAVE_ADDR_W, &data, 1, HAL_MAX_DELAY);
    HAL_Delay(1);
    data &= ~EN;
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_SLAVE_ADDR_W, &data, 1, HAL_MAX_DELAY);
}

void LcdWriteByte(uint8_t cmd, uint8_t data) {
    uint8_t control = (cmd == LCD_DATA) ? RS : 0;
    LcdSendNibble((data >> 4), control);
    LcdSendNibble((data & 0x0F), control);
    HAL_Delay(1);
}

void LcdInit(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    HAL_Delay(50);
    LcdSendNibble(0x03, 0);
    HAL_Delay(5);
    LcdSendNibble(0x03, 0);
    HAL_Delay(5);
    LcdSendNibble(0x03, 0);
    HAL_Delay(5);
    LcdSendNibble(0x02, 0);

    LcdWriteByte(LCD_CMD, 0x28); // 2 lines
    LcdWriteByte(LCD_CMD, 0x0C); // Display ON
    LcdWriteByte(LCD_CMD, 0x06); // Entry mode
    LcdWriteByte(LCD_CMD, 0x01); // Clear
    HAL_Delay(5);
}

void LcdPuts(uint8_t line, char *str) {
    LcdWriteByte(LCD_CMD, line);
    while (*str) {
        LcdWriteByte(LCD_DATA, *str++);
    }
}

