/*
 * W5500_Measure_Data_Loss.c
 *
 *  Created on: Jun 29, 2023
 *      Author: MateKocsis
 */
#include <main.h>
#include <W5500_example_DataModifier.h>
#include <SPI_Communication.h>
#include <string.h>
#include <W5500_driver_advanced.h>
#include <w5500_driver.h>
#include <W5500_Measure_Sending_Time.h>
#include <W5500_spi_lowLevel.h>
#include <W5500_Measure_Data_Loss.h>


void W5500_Measure_Data_Loss_Run(SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1){
	uint16_t send_DataSize;
	uint16_t recv_DataSize;
	uint8_t spi_recv[(16*1024)];
	uint8_t spi_send[(16*1024)];
	uint8_t socketStatus;
	SocketRegisterInit_HandleTypeDef socket;
	uint64_t DataSizeCounter = 0;

	uint8_t end[(16*1024)];
	end[0] = 'e';
	end[1] = 'n';
	end[2] = 'd';

	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);
	W5500_SocketNumberInit(&socket, 0);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(0, 15200);
	/*Give the whole RX and TX memory for the socket 0.*/
	W5500_SetSocketRegister(0, S_RXBUF_SIZE, 0x0010);
	W5500_SetSocketRegister(0, S_TXBUF_SIZE, 0x0010);

	W5500_SocketCommand(0,OPEN);
	W5500_SocketCommand(0,LISTEN);

	HAL_TIM_Base_Start(htim1);

	while (1){
		W5500_GetSocketStatus(0, &socketStatus);

		if(socketStatus == SOCK_ESTABLISHED){
			recv_DataSize = W5500_Receive(0, spi_recv);

				DataSizeCounter = 1;
				send_DataSize = 8;

				while(1){
					copyToArray(&DataSizeCounter, spi_send, 8);
					W5500_Send(0, spi_send, send_DataSize);
					DataSizeCounter++;
				}

				W5500_Send(0, end, 3);


		}
		if((socketStatus == SOCK_CLOSE_WAIT) || (socketStatus == SOCK_CLOSED)){
			W5500_SocketReopen(0);
		}
	}
}



















