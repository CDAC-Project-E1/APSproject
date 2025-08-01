/*
 * LM35.c
 *
 *  Created on: Jul 24, 2025
 *      Author: Vaishnavi
 */


#include "LM35.h"

ADC_ChannelConfTypeDef sConfig;

void LM35_Init(ADC_HandleTypeDef *hadc)
{
    // Assuming ADC is already initialized using CubeMX (MX_ADC1_Init)

    // Configure channel 5 (PA5)
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
    {
        // Handle error
        Error_Handler();
    }
}

float LM35_ReadTemperature(ADC_HandleTypeDef *hadc)
{
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    uint16_t adc_val = HAL_ADC_GetValue(hadc);
    HAL_ADC_Stop(hadc);

    // Convert to voltage (assuming Vref = 3.3V and 12-bit resolution)
    float voltage = (adc_val * 3.3f) / 4095.0f;

    // LM35 gives 10mV/°C → 0.01V/°C
    float temperature = voltage / 0.01f;

    return temperature;
}
