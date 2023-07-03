/*
 * SPI_Communication.c
 *
 *  Created on: May 11, 2023
 *      Author: MateKocsis
 *
 *  In this file you must implement the microcontroller specific SPI communication.
 */

#include <SPI_Communication.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"

struct SPI_Init{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PIN_x;
	SPI_HandleTypeDef* hspi;
}SPI_Init_Params;

/*
 * SPI initialization.
 * */
void SPI_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, SPI_HandleTypeDef* hspi1){
	
	/* This is an example for STM32 Nucleo-F429ZI:*/
	SPI_Init_Params.GPIOx = GPIOx;
	SPI_Init_Params.GPIO_PIN_x = GPIO_Pin_x;
	SPI_Init_Params.hspi = hspi1;
}

/*
 * SPI send command. The function's parameters must be the same as below.
 * */
void SPI_Send(uint8_t frame[], uint16_t dataLength){

	/* This is an example for STM32 Nucleo-F429ZI:*/
	HAL_GPIO_WritePin(SPI_Init_Params.GPIOx, SPI_Init_Params.GPIO_PIN_x, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI_Init_Params.hspi, frame, dataLength+3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_Init_Params.GPIOx, SPI_Init_Params.GPIO_PIN_x, GPIO_PIN_SET);
};

/*
 * SPI receive command. The function's parameters must be the same as below.
 * */
void SPI_Receive(uint8_t frame[], uint16_t dataLength, uint8_t* pDestination){

	/* This is an example for STM32 Nucleo-F429ZI:*/
	HAL_GPIO_WritePin(SPI_Init_Params.GPIOx, SPI_Init_Params.GPIO_PIN_x, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI_Init_Params.hspi, frame, 3, HAL_MAX_DELAY);
	HAL_SPI_Receive(SPI_Init_Params.hspi, pDestination, dataLength, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_Init_Params.GPIOx, SPI_Init_Params.GPIO_PIN_x, GPIO_PIN_SET);
};
