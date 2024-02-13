/*
 * magnetometer.h
 *
 *  Created on: Jan 19, 2024
 *      Author: Alexandr Yermakov
 */

/*

Datasheet URL:
https://media.digikey.com/pdf/Data%20Sheets/MEMSIC%20PDFs/MMC5983MA_RevA_4-3-19.pdf
*/

#ifndef __MAGNETOMETER_H__
#define __MAGNETOMETER_H__

#include "stm32l4xx_hal.h"

#define MAGNETOMETER_SPI &hspi1 // SPI interface
#define MAGNETOMETER_CS_PIN GPIO_PIN_4 // Chip select pin
#define MAGNETOMETER_CS_GPIO_PORT GPIOA // Chip select port

// MMC5983MA register addresses
#define MAGNETOMETER_XOUT_L 0x00
#define MAGNETOMETER_XOUT_H 0x01
#define MAGNETOMETER_YOUT_L 0x02
#define MAGNETOMETER_YOUT_H 0x03
#define MAGNETOMETER_ZOUT_L 0x04
#define MAGNETOMETER_ZOUT_H 0x05
#define MAGNETOMETER_TEMP_L 0x06
#define MAGNETOMETER_TEMP_H 0x07
#define MAGNETOMETER_STATUS 0x08
#define MAGNETOMETER_CONTROL_0 0x09
#define MAGNETOMETER_CONTROL_1 0x0A
#define MAGNETOMETER_CONTROL_2 0x0B
#define MAGNETOMETER_PRODUCT_ID 0x2F

// Function to write to MAGNETOMETER register
void MAGNETOMETER_WriteReg(uint8_t reg, uint8_t data);

// Function to read from MAGNETOMETER register
uint8_t MAGNETOMETER_ReadReg(uint8_t reg);

// Function to read magnetic field data
// pData: Pointer to an array where the magnetic field data will be stored
// The array should have 3 elements for X, Y, and Z
void MAGNETOMETER_ReadMagneticField(int16_t* pData);

// Function to initialize MAGNETOMETER
void MAGNETOMETER_Init(void);

#endif /* __MAGNETOMETER_H__ */
