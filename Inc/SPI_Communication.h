/*
 * SPI_Communication.h
 *
 *  Created on: May 11, 2023
 *      Author: MateKocsis
 */

#ifndef INC_SPI_COMMUNICATION_H_
#define INC_SPI_COMMUNICATION_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"

void SPI_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, SPI_HandleTypeDef* hspi1);

void SPI_Send(uint8_t frame[], uint16_t dateLength);

void SPI_Receive(uint8_t frame[], uint16_t dataLength, uint8_t* pDestination);

#endif /*INC_SPI_COMMUNICATION_H_*/
