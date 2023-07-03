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

/*Functions--------------------------------------------------------------------*/
void W5500_SPI_Send(uint16_t offset_address, uint8_t BSB,
		uint16_t send_dataLength, uint8_t* pData){

	/*Little endian to big endian*/
	uint16_t offset_address_temp = (offset_address & 0xFF00)>>8;
	offset_address = (offset_address & 0x00FF)<<8;
	offset_address = offset_address | offset_address_temp;

	uint8_t frame[send_dataLength+3];
	memcpy(frame, &offset_address, 2);
	BSB=(BSB<<3)|0x04;
	memcpy(frame+2, &BSB,1);
	memcpy(frame+3, pData, send_dataLength);
	SPI_Send(frame, send_dataLength);
}

void W5500_SPI_Recieve(uint16_t offset_address, uint8_t BSB,
		uint16_t recv_dataLength, uint8_t* pDestination){

	/*Little endian to big endian*/
	uint16_t offset_address_temp = (offset_address & 0xFF00)>>8;
	offset_address = (offset_address & 0x00FF)<<8;
	offset_address = offset_address | offset_address_temp;

	uint8_t frame[3];
	memcpy(frame, &offset_address, 2);
	BSB=BSB<<3;
	memcpy(frame+2, &BSB,1);
	SPI_Receive(frame, recv_dataLength, pDestination);
}
