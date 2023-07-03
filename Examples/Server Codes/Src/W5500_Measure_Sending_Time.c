/*
 * W5500_Measure_Sending_Time.c
 *
 *  Created on: Jun 28, 2023
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


void W5500_Measure_Sending_Time_Run(SPI_HandleTypeDef* hspi1, TIM_HandleTypeDef* htim1){
	uint16_t send_DataSize;
	uint16_t recv_DataSize;
	uint8_t spi_recv[(16*1024)];
	uint8_t spi_send[(16*1024)];
	uint8_t socketStatus;
	uint32_t timer;
	SocketRegisterInit_HandleTypeDef socket;
	uint8_t x = 0;


	SPI_Init(GPIOD, GPIO_PIN_14, hspi1);
	W5500_SocketNumberInit(&socket, 0);

	W5500_TcpipCommonRegInit(0xc0a80001,0xffffff00,0x0008DC010203,0xc0a80016);
	W5500_TcpipSocketRegInit(0, 15200);
	/*Give the whole RX and TX memory for the socket 0.*/
	W5500_SetSocketRegister(0, S_RXBUF_SIZE, 0x1010);
	W5500_SetSocketRegister(0, S_TXBUF_SIZE, 0x1010);

	W5500_SocketCommand(0,OPEN);
	W5500_SocketCommand(0,LISTEN);

	HAL_TIM_Base_Start(htim1);

	while (1){
		W5500_GetSocketStatus(0, &socketStatus);

		if(socketStatus == SOCK_ESTABLISHED){
			recv_DataSize = W5500_Receive(0, spi_recv);

			if(recv_DataSize > 0){
				x = 0;
				__HAL_TIM_SET_COUNTER(htim1,0);
				W5500_Send(0, spi_send, send_DataSize);
				while(x==0){
					W5500_SPI_Recieve(S_IR_ADDR, socket.S_BSB_REG, 1, &socket.S_IR.data);
					if(socket.S_IR._SEND_OK == 1){
						timer = __HAL_TIM_GET_COUNTER(htim1);
						send_DataSize = 2;
						copyToArray(&timer, spi_send, send_DataSize);
						W5500_Send(0, spi_recv, recv_DataSize);
						x = 1;
					}
				}
			}
		}
		if((socketStatus == SOCK_CLOSE_WAIT) || (socketStatus == SOCK_CLOSED)){
			W5500_SocketReopen(0);
		}
	}
}






























