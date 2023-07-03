/*
 * W5500_Multiple_Thread.c
 *
 *  Created on: Jun 29, 2023
 *      Author: MateKocsis
 */
#include <main.h>
#include <W5500_example_DataModifier.h>
#include <SPI_Communication.h>
#include <string.h>
#include <w5500_driver.h>
#include <W5500_driver_advanced.h>


void W5500_Multiple_Thread_Run(SPI_HandleTypeDef* hspi1){
	/*socket 0*/
	uint16_t send_DataSize0;
	uint16_t recv_DataSize0;
	uint8_t spi_recv0[(16*1024)];
	uint8_t spi_send0[(16*1024)];
	uint8_t socketStatus0;
	uint64_t dataSizeCounter0 = 1;
	uint8_t socketNumber0 = 0;

	/*socket 1*/
	uint16_t send_DataSize1;
	uint16_t recv_DataSize1;
	uint8_t spi_recv1[(16*1024)];
	uint8_t spi_send1[(16*1024)];
	uint8_t socketStatus1;
	uint64_t dataSizeCounter1 = 1;
	uint8_t socketNumber1 = 1;

	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(socketNumber0, 15200);
	W5500_TcpipSocketRegInit(socketNumber1, 16200);

	W5500_SocketCommand(socketNumber0,OPEN);
	W5500_SocketCommand(socketNumber0,LISTEN);
	W5500_SocketCommand(socketNumber1,OPEN);
	W5500_SocketCommand(socketNumber1,LISTEN);

	while (1){
		W5500_GetSocketStatus(socketNumber0, &socketStatus0);
		W5500_GetSocketStatus(socketNumber1, &socketStatus1);

		if((socketStatus0 == SOCK_ESTABLISHED) && (socketStatus1 == SOCK_ESTABLISHED )){
			recv_DataSize0 = W5500_Receive(socketNumber0, spi_recv0);
			recv_DataSize1 = W5500_Receive(socketNumber1, spi_recv1);

			if(recv_DataSize0 > 0){
				copyToArray(&dataSizeCounter0, spi_send0, 8);
				W5500_Send(socketNumber0, spi_send0, 8);
				dataSizeCounter0++;
			}
			if(recv_DataSize1 > 0){
				copyToArray(&dataSizeCounter1, spi_send1, 8);
				W5500_Send(socketNumber1, spi_send1, 8);
				dataSizeCounter1++;
			}
		}
		if((socketStatus0 == SOCK_CLOSE_WAIT) || (socketStatus0 == SOCK_CLOSED)){
			W5500_SocketReopen(socketNumber0);
		}
		if((socketStatus1 == SOCK_CLOSE_WAIT) || (socketStatus1 == SOCK_CLOSED)){
			W5500_SocketReopen(socketNumber1);
		}
	}
}



















