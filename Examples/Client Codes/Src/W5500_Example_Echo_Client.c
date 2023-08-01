/*
 * W5500_Example_Echo_Client.c
 *
 *  Created on: Jul 31, 2023
 *      Author: AttilaTakacs
 *
 *  *This example sends a character to the server, starting from '0', and receives the response (echo).
 *  *By incrementing the response every time it counts from 0 to 9.
 */


#include <main.h>
#include <w5500_driver.h>
#include <W5500_driver_advanced.h>
#include <SPI_Communication.h>


void W5500_Example_Echo_Client_Run(SPI_HandleTypeDef* hspi1){

	uint16_t send_DataSize;
	uint16_t recv_DataSize;

	uint8_t spi_recv[(16*1024)];
	uint8_t spi_send[(16*1024)];
	uint8_t socketStatus;
	uint8_t socketNumber = 0;

	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(socketNumber, 15200);
	W5500_TcpipDestinationRegInit(socketNumber, 0xc0a8006e, 15400);

	W5500_SetSocketRegister(socketNumber, S_RXBUF_SIZE, 0x0010);
	W5500_SetSocketRegister(socketNumber, S_TXBUF_SIZE, 0x0010);

	W5500_SocketCommand(socketNumber,OPEN);
	W5500_SocketCommand(socketNumber,CONNECT);


	send_DataSize = 1;
	spi_send[0] = '0';
	while (1){
		W5500_GetSocketStatus(socketNumber, &socketStatus);

		if(socketStatus == SOCK_ESTABLISHED){
			W5500_Send(socketNumber, spi_send, send_DataSize);
			recv_DataSize = 0;
			while (recv_DataSize == 0){
				recv_DataSize = W5500_Receive(socketNumber, spi_recv);
			}
			spi_send[0] = spi_recv[0] + 1;
			if (spi_send[0] > '9'){
				spi_send[0] = '0';
			}
		}

		if((socketStatus == SOCK_CLOSE_WAIT) || (socketStatus == SOCK_CLOSED)){
			W5500_SocketReconnect(socketNumber);
		}

		HAL_Delay(1000);
	}
}
