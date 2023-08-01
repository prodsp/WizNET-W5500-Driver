/*
 * W5500_Client_Server_Multiple_Thread.c
 *
 *  Created on: Jul 31, 2023
 *      Author: AttilaTakacs
 *
 *  *This example receives a number from the Client, calculates the length of the received data, and sends this information back.
 *  *Afterwards it sends the received number to a Server for validation, and after receiving the validation message transmits it to the Client.
 */


#include <main.h>
#include <stdio.h>
#include <string.h>
#include <w5500_driver.h>
#include <W5500_driver_advanced.h>
#include <SPI_Communication.h>

void W5500_Client_Server_Multiple_Thread_Run(SPI_HandleTypeDef* hspi1){

	uint16_t send_DataSize;
	uint16_t recv_DataSize;
	uint8_t spi_recv0[(8*1024)];
	uint8_t spi_send0[(8*1024)];
	uint8_t spi_recv1[(8*1024)];
	uint8_t spi_send1[(8*1024)];
	uint8_t socketStatus0;
	uint8_t socketStatus1;
	uint8_t socketNumber0 = 0;
	uint8_t socketNumber1 = 1;

	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(socketNumber0, 15200);
	W5500_TcpipSocketRegInit(socketNumber1, 15300);

	W5500_TcpipDestinationRegInit(socketNumber1, 0xc0a8006e, 15400);


	W5500_SetSocketRegister(socketNumber0, S_RXBUF_SIZE, 0x0008);
	W5500_SetSocketRegister(socketNumber0, S_TXBUF_SIZE, 0x0008);
	W5500_SetSocketRegister(socketNumber1, S_RXBUF_SIZE, 0x0008);
	W5500_SetSocketRegister(socketNumber1, S_TXBUF_SIZE, 0x0008);

	W5500_SocketCommand(socketNumber0,OPEN);
	W5500_SocketCommand(socketNumber0,LISTEN);
	W5500_SocketCommand(socketNumber1,OPEN);
	W5500_SocketCommand(socketNumber1,CONNECT);

	while (1){
		W5500_GetSocketStatus(socketNumber0, &socketStatus0);
		W5500_GetSocketStatus(socketNumber1, &socketStatus1);

		if(socketStatus0 == SOCK_ESTABLISHED){
			recv_DataSize = W5500_Receive(socketNumber0, spi_recv0);

			if(recv_DataSize > 0){
				sprintf(spi_send0, "%i", recv_DataSize);
				send_DataSize = strlen(spi_send0);
				W5500_Send(socketNumber0, spi_send0, send_DataSize);

				if(socketStatus1 == SOCK_ESTABLISHED){
					W5500_Send(socketNumber1, spi_recv0, recv_DataSize);
					recv_DataSize = 0;
					while (recv_DataSize == 0){
						recv_DataSize = W5500_Receive(socketNumber1, spi_recv1);
					}
				}

				W5500_Send(socketNumber0, spi_recv1, recv_DataSize);
			}
		}

		if((socketStatus0 == SOCK_CLOSE_WAIT) || (socketStatus0 == SOCK_CLOSED)){
			W5500_SocketReopen(socketNumber0);
		}
		if((socketStatus1 == SOCK_CLOSE_WAIT) || (socketStatus1 == SOCK_CLOSED)){
			W5500_SocketReconnect(socketNumber1);
		}

	}

}
