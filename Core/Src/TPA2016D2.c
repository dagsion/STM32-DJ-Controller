#include "stm32f4xx_hal.h"  // Change according to your STM32 series

#define TPA2016D2_I2C_ADDR 0x58 << 1  // I2C address for the TPA2016D2

extern I2C_HandleTypeDef hi2c1; // Change to the correct I2C instance

// Write a single register
HAL_StatusTypeDef TPA2016D2_WriteRegister(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    return HAL_I2C_Master_Transmit(&hi2c1, TPA2016D2_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

// Read a single register
HAL_StatusTypeDef TPA2016D2_ReadRegister(uint8_t reg, uint8_t *value) {
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, TPA2016D2_I2C_ADDR, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return status;
    return HAL_I2C_Master_Receive(&hi2c1, TPA2016D2_I2C_ADDR, value, 1, HAL_MAX_DELAY);
}

// Set gain (-28dB to +30dB in 2dB steps)
HAL_StatusTypeDef TPA2016D2_SetGain(int8_t gain) {
    if (gain < -28 || gain > 30 || gain % 2 != 0) return HAL_ERROR;
    uint8_t value = (gain + 28) / 2;
    return TPA2016D2_WriteRegister(0x01, value);
}

// Enable/disable AGC
HAL_StatusTypeDef TPA2016D2_SetAGC(uint8_t enable) {
    uint8_t reg_value;
    if (TPA2016D2_ReadRegister(0x02, &reg_value) != HAL_OK) return HAL_ERROR;
    if (enable) reg_value |= 0x40;
    else reg_value &= ~0x40;
    return TPA2016D2_WriteRegister(0x02, reg_value);
}

// Enable the amplifier
HAL_StatusTypeDef TPA2016D2_Enable(uint8_t enable) {
    uint8_t reg_value;
    if (TPA2016D2_ReadRegister(0x02, &reg_value) != HAL_OK) return HAL_ERROR;
    if (enable) reg_value |= 0x01;
    else reg_value &= ~0x01;
    return TPA2016D2_WriteRegister(0x02, reg_value);
}
