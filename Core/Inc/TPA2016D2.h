#ifndef __TPA2016D2_H
#define __TPA2016D2_H

#include "main.h"

// I2C handle (assuming hi2c1 is used)
extern I2C_HandleTypeDef hi2c1;

// TPA2016D2 I2C Address
#define TPA2016D2_I2C_ADDR  0x58  // Default 7-bit address

// Register Definitions
#define TPA2016D2_REG_CONTROL      0x01
#define TPA2016D2_REG_ATTACK       0x02
#define TPA2016D2_REG_RELEASE      0x03
#define TPA2016D2_REG_HOLD         0x04
#define TPA2016D2_REG_GAIN         0x05
#define TPA2016D2_REG_NOISE_GATE   0x06

// Function Prototypes
HAL_StatusTypeDef TPA2016D2_WriteRegister(uint8_t reg, uint8_t value);
HAL_StatusTypeDef TPA2016D2_ReadRegister(uint8_t reg, uint8_t *value);
HAL_StatusTypeDef TPA2016D2_SetGain(int8_t gain);
HAL_StatusTypeDef TPA2016D2_EnableAGC(uint8_t enable);
HAL_StatusTypeDef TPA2016D2_SetNoiseGate(uint8_t level);

#endif /* __TPA2016D2_H */
