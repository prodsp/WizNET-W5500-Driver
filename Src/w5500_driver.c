/*
 * w5500_driver.c
 *
 *  Created on: Jul 15, 2022
 *      Author: MateKocsis
 */

#include "main.h"
#include "w5500_driver.h"
#include <stdio.h>
#include <string.h>
#include <W5500_spi_lowLevel.h>
#include <W5500_driver_advanced.h>

void W5500_SocketCommand(uint8_t socketNumber, uint8_t command){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	switch (command){

		case OPEN:
			socket.S_CR = OPEN;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case LISTEN:
			socket.S_CR = LISTEN;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1,&socket.S_CR);
			break;
		case CONNECT:
			socket.S_CR = CONNECT;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case DISCON:
			socket.S_CR = DISCON;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case CLOSE:
			socket.S_CR = CLOSE;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case SEND:
			socket.S_CR = SEND;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case SEND_KEEP:
			socket.S_CR = SEND_KEEP;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case RECV:
			socket.S_CR = RECV;
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;

	}
}

void W5500_Send(uint8_t socketNumber, uint8_t* dataBuffer, uint16_t dataSize){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);
	uint16_t tempTX_WR;

	socket.S_IR._SEND_OK = 1;
	W5500_SPI_Send(S_IR_ADDR, socket.S_BSB_REG, 1,&socket.S_IR.data);

	W5500_SPI_Recieve(S_TX_WR_ADDR, socket.S_BSB_REG, 2, socket.S_TX_WR);
	W5500_SPI_Recieve(S_TX_RD_ADDR, socket.S_BSB_REG, 2, socket.S_TX_RD);
	W5500_SPI_Send(intFromArray(socket.S_TX_RD), socket.S_BSB_TX, dataSize, dataBuffer);
	socket.S_TX_WR[0] = socket.S_TX_RD[0];
	socket.S_TX_WR[1] = socket.S_TX_RD[1];

	tempTX_WR = intFromArray(socket.S_TX_WR);
	tempTX_WR = tempTX_WR + dataSize;
	copyToArray(&tempTX_WR, socket.S_TX_WR, 2);

	W5500_SPI_Send(S_TX_WR_ADDR, socket.S_BSB_REG, 2,socket.S_TX_WR);
	W5500_SocketCommand(socketNumber,SEND);
	socket.S_IR._SEND_OK = 0;
	socket.S_IR._RECV = 1;
	W5500_SPI_Send(S_IR_ADDR, socket.S_BSB_REG, 1,&socket.S_IR.data);
}

uint16_t W5500_Receive(uint8_t socketNumber, uint8_t* recvBuffer){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	uint8_t rsrFlag;
	uint8_t recvDataSize1[2];
	uint8_t recvDataSize2[2];
	uint16_t recv_DataSize;

	W5500_SPI_Recieve(S_IR_ADDR, socket.S_BSB_REG, 1, &socket.S_IR.data);

	if(socket.S_IR._RECV == 1){

		rsrFlag = 1;
		while(rsrFlag == 1){
			W5500_SPI_Recieve(S_RX_RSR_ADDR,socket.S_BSB_REG , 2, recvDataSize1);
			W5500_SPI_Recieve(S_RX_RSR_ADDR,socket.S_BSB_REG , 2, recvDataSize2);
			if(recvDataSize1[0]==recvDataSize2[0] && recvDataSize1[1]==recvDataSize2[1]){
				rsrFlag = 0;
			}
		 }
		 recv_DataSize = intFromArray(recvDataSize1);
		 W5500_SPI_Recieve(S_RX_RD_ADDR, socket.S_BSB_REG, 2, socket.S_RX_RD);
		 W5500_SPI_Recieve(S_RX_WR_ADDR, socket.S_BSB_REG, 2, socket.S_RX_WR);
		 W5500_SPI_Recieve(intFromArray(socket.S_RX_RD), socket.S_BSB_RX, recv_DataSize, recvBuffer);
		 socket.S_RX_RD[0] = socket.S_RX_WR[0];
		 socket.S_RX_RD[1] = socket.S_RX_WR[1];
		 W5500_SPI_Send(S_RX_RD_ADDR, socket.S_BSB_REG, 2, socket.S_RX_RD);
		 W5500_SocketCommand(socketNumber,RECV);
		 return recv_DataSize;
	}
	else{
		return 0;
	}
}

void W5500_SocketReopen(uint8_t socketNumber){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	W5500_SocketCommand(socketNumber,CLOSE);
	W5500_SocketCommand(socketNumber,OPEN);
	W5500_SocketCommand(socketNumber,LISTEN);
}

void W5500_SocketReconnect(uint8_t socketNumber){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	W5500_SocketCommand(socketNumber,CLOSE);
	W5500_SocketCommand(socketNumber,OPEN);
	W5500_SocketCommand(socketNumber,CONNECT);
}

void W5500_GetSocketStatus(uint8_t socketNumber, uint8_t* statusHandler){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	W5500_SPI_Recieve(S_SR_ADDR, socket.S_BSB_REG, 1, statusHandler);
}

void W5500_TcpipCommonRegInit(uint32_t GatewayIpAddress, uint32_t SubnetMask, uint64_t SourceHardwareAddress,uint32_t SourceIpAddress){
	CommonRegisterInit_HandleTypeDef comreg;

	copyToArray(&GatewayIpAddress, comreg.GAR, 4);
	copyToArray(&SubnetMask, comreg.SUBR, 4);
	copyToArray(&SourceHardwareAddress, comreg.SHAR, 6);
	copyToArray(&SourceIpAddress, comreg.SIPR, 4);
	comreg.MR = 0b00000000;
	/*Enable all of the interrupts*/
	comreg.IMR=0;
	/*RTR configures the retransmission timeout period. unit = 100us*/
	comreg.RTR[0]=0x0F;
	comreg.RTR[1]=0xA0;
	/*RCR configures the number of retransmission's time.*/
	comreg.RCR=0x07;
	/*7.bit -> reset disable
		 * 6.bit ->  Configure with OPMDC
		 * 5-3.bits -> 100BT Full-duplex, Auto-negotiation disabled
		 * 2.bit -> Full duplex
		 * 1.bit -> 100Mpbs based
		 * 0.bit -> Link up
		 * */
	comreg.PHYCFGR=0b11011111;

	W5500_SPI_Send(MR_ADDR, COMM_REG, 1, &comreg.MR);
	W5500_SPI_Send(GAR_ADDR, COMM_REG, 4, comreg.GAR);
	W5500_SPI_Send(SUBR_ADDR, COMM_REG, 4, comreg.SUBR);
	W5500_SPI_Send(SHAR_ADDR, COMM_REG, 6, comreg.SHAR);
	W5500_SPI_Send(SIPR_ADDR, COMM_REG, 4, comreg.SIPR);
	W5500_SPI_Send(IMR_ADDR, COMM_REG, 1, &comreg.IMR);
	W5500_SPI_Send(RTR_ADDR, COMM_REG, 2, comreg.RTR);
	W5500_SPI_Send(RCR_ADDR, COMM_REG, 1, &comreg.RCR);
	W5500_SPI_Send(PHYCFGR_ADDR, COMM_REG, 1, &comreg.PHYCFGR);
}

void W5500_TcpipSocketRegInit(uint8_t socketNumber, uint16_t sourcePort){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	/*TCP mode usage.*/
	socket.S_MR=0b00100001;
	/*This is the maximum size of the socket segment.*/
	socket.S_MSSR[0]=0x05;
	socket.S_MSSR[1]=0xB3;
	/*WIZnet's socket timeout. unit = 5s */
	socket.S_KPALVTR=0x01;
	/*Set the source port*/
	copyToArray(&sourcePort, socket.S_PORT, 2);

	W5500_SPI_Send(S_MR_ADDR, socket.S_BSB_REG, 1, &socket.S_MR);
	W5500_SPI_Send(S_MSSR_ADDR, socket.S_BSB_REG, 1, socket.S_MSSR);
	W5500_SPI_Send(S_PORT_ADDR, socket.S_BSB_REG, 2, socket.S_PORT);
	W5500_SPI_Send(S_KPALVTR_ADDR, socket.S_BSB_REG, 1, &socket.S_KPALVTR);
}

void W5500_TcpipDestinationRegInit(uint8_t socketNumber, uint32_t destIpAddress, uint16_t destPort){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	//Set destination IP address
	copyToArray(&destIpAddress, socket.S_DIPR, 4);
	//Set destination port
	copyToArray(&destPort, socket.S_DPORT, 2);


	W5500_SPI_Send(S_DIPR_ADDR, socket.S_BSB_REG, 4, socket.S_DIPR);
	W5500_SPI_Send(S_DPORT_ADDR, socket.S_BSB_REG, 2, socket.S_DPORT);
};
