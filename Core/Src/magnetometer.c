/*
 * magnetometer.c
 *
 *  Created on: Jan 19, 2024
 *      Author: Alexandr Yermakov
 */

/*

Datasheet URL:
https://media.digikey.com/pdf/Data%20Sheets/MEMSIC%20PDFs/MMC5983MA_RevA_4-3-19.pdf
*/

#include "magnetometer.h"
#include <stdio.h>
#include "stm32l4xx_hal.h"
//#include "main.h"
//
//extern SPI_HandleTypeDef hspi2;


// Function to write to MAGNETOMETER register
void MAGNETOMETER_Read(uint8_t reg, uint8_t data) {
	HAL_GPIO_WritePin(MAGNETOMETER_CS_GPIO_PORT, MAGNETOMETER_CS_PIN, GPIO_PIN_RESET);
	uint8_t txData[2] = {reg, data};
	HAL_SPI_Transmit(MAGNETOMETER_SPI, txData, 2, 100);
	HAL_GPIO_WritePin(MAGNETOMETER_CS_GPIO_PORT, MAGNETOMETER_CS_PIN, GPIO_PIN_SET);
}

// Function to read from MAGNETOMETER register
uint8_t MAGNETOMETER_ReadReg(uint8_t reg) {
	HAL_GPIO_WritePin(MAGNETOMETER_CS_GPIO_PORT, MAGNETOMETER_CS_PIN, GPIO_PIN_RESET);
	uint8_t txData = 0x80 | reg; // MSB must be set for read
	uint8_t rxData;
	HAL_SPI_Transmit(MAGNETOMETER_SPI, &txData, 1, 100);
	HAL_SPI_Receive(MAGNETOMETER_SPI, &rxData, 1, 100);
	HAL_GPIO_WritePin(MAGNETOMETER_CS_GPIO_PORT, MAGNETOMETER_CS_PIN, GPIO_PIN_SET);
	return rxData;
}

// Function to read magnetic field data
void MAGNETOMETER_ReadMagneticField(int16_t* pData) {
	uint8_t tempL, tempH;
	tempL = MAGNETOMETER_ReadReg(MAGNETOMETER_XOUT_L);
	tempH = MAGNETOMETER_ReadReg(MAGNETOMETER_XOUT_H);
	pData[0] = (tempH << 8) | tempL;
	tempL = MAGNETOMETER_ReadReg(MAGNETOMETER_YOUT_L);
	tempH = MAGNETOMETER_ReadReg(MAGNETOMETER_YOUT_H);
	pData[1] = (tempH << 8) | tempL;
	tempL = MAGNETOMETER_ReadReg(MAGNETOMETER_ZOUT_L);
	tempH = MAGNETOMETER_ReadReg(MAGNETOMETER_ZOUT_H);
	pData[2] = (tempH << 8) | tempL;
}

// Function to initialize MAGNETOMETER
void MAGNETOMETER_Init(void) {
	// Enable SPI interface
	__HAL_RCC_SPI1_CLK_ENABLE();
	// Configure CS pin as output
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = MAGNETOMETER_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(MAGNETOMETER_CS_GPIO_PORT, &GPIO_InitStruct);
	// Set CS pin high
	HAL_GPIO_WritePin(MAGNETOMETER_CS_GPIO_PORT, MAGNETOMETER_CS_PIN, GPIO_PIN_SET);
	// Configure magnetic sensor settings
	(MAGNETOMETER_CONTROL_0, 0x00); // Reset sensor
	HAL_Delay(1); // Wait for reset to complete
	(MAGNETOMETER_CONTROL_0, 0x01); // Start measurement
}
