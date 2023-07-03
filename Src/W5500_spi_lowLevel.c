/*
 * W5500_spi_lowLevel.c
 *
 *  Created on: Jul 14, 2022
 *      Author: MateKocsis
 */

/*Includes--------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <W5500_spi_lowLevel.h>
#include <SPI_Communication.h>

/* Private variables ---------------------------------------------------------*/
/*
struct SPI_Init{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PIN_x;
	SPI_HandleTypeDef* hspi;
}SPI_Init;

void W5500_SPI_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, SPI_HandleTypeDef* hspi1){
	SPI_Init.GPIOx = GPIOx;
	SPI_Init.GPIO_PIN_x = GPIO_Pin_x;
	SPI_Init.hspi = hspi1;
}*/

void W5500_SPI_Send(uint16_t offset_address, uint8_t BSB,
		uint16_t send_dataLength, uint8_t* pData){

	/*to big endian from little endian*/
	uint16_t offset_address_temp = (offset_address & 0xFF00)>>8;
	offset_address = (offset_address & 0x00FF)<<8;
	offset_address = offset_address | offset_address_temp;

	uint8_t frame[send_dataLength+3];
	memcpy(frame, &offset_address, 2);
	BSB=(BSB<<3)|0x04;
	memcpy(frame+2, &BSB,1);
	memcpy(frame+3, pData, send_dataLength);
/*
	HAL_GPIO_WritePin(SPI_Init.GPIOx, SPI_Init.GPIO_PIN_x, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI_Init.hspi, frame, send_dataLength+3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_Init.GPIOx, SPI_Init.GPIO_PIN_x, GPIO_PIN_SET);
*/

	SPI_Send(frame, send_dataLength);
}

/*You can use only VDB mode*/
void W5500_SPI_Recieve(uint16_t offset_address, uint8_t BSB,
		uint16_t recv_dataLength, uint8_t* pDestination){

	/*to big endian from little endian*/
	uint16_t offset_address_temp = (offset_address & 0xFF00)>>8;
	offset_address = (offset_address & 0x00FF)<<8;
	offset_address = offset_address | offset_address_temp;

	uint8_t frame[3];
	memcpy(frame, &offset_address, 2);
	BSB=BSB<<3;
	memcpy(frame+2, &BSB,1);

/*
	HAL_GPIO_WritePin(SPI_Init.GPIOx, SPI_Init.GPIO_PIN_x, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI_Init.hspi, frame, 3, HAL_MAX_DELAY);
	HAL_SPI_Receive(SPI_Init.hspi, pDestination, recv_dataLength, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_Init.GPIOx, SPI_Init.GPIO_PIN_x, GPIO_PIN_SET);
*/

	SPI_Receive(frame, recv_dataLength, pDestination);
}
