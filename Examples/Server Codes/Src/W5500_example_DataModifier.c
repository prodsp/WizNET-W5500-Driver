/*
 * W5500_example_DataModifier.c
 *
 *  Created on: Aug 2, 2022
 *      Author: MateKocsis
 *
 *   *  This example shows how could you receive data from the client, increase the data by one
 *   and transmit the increased data to the client.
 *
 */

#include <main.h>
#include <W5500_example_DataModifier.h>
#include <SPI_Communication.h>
#include <string.h>
#include <w5500_driver.h>
#include <W5500_driver_advanced.h>


void W5500_example_DataModifier_Run(SPI_HandleTypeDef* hspi1){
	uint16_t send_DataSize;
	uint16_t recv_DataSize;
	uint8_t spi_recv[(16*1024)];
	uint8_t spi_send[(16*1024)];
	uint8_t socketStatus;

	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(0, 15200);
	/*Give the whole RX and TX memory for the socket 0.*/
	W5500_SetSocketRegister(0, S_RXBUF_SIZE, 0x0010);
	W5500_SetSocketRegister(0, S_TXBUF_SIZE, 0x0010);

	W5500_SocketCommand(0,OPEN);
	W5500_SocketCommand(0,LISTEN);

	while (1){
		W5500_GetSocketStatus(0, &socketStatus);

		if(socketStatus == SOCK_ESTABLISHED){
			recv_DataSize = W5500_Receive(0, spi_recv);

			send_DataSize = recv_DataSize;

			for(int i = 0; i<send_DataSize;i++){
				spi_send[i] = spi_recv[i]+1;
			}

			if(recv_DataSize > 0){
				W5500_Send(0, spi_send, send_DataSize);
			}
		}
		if((socketStatus == SOCK_CLOSE_WAIT) || (socketStatus == SOCK_CLOSED)){
			W5500_SocketReopen(0);
		}
	}
}

