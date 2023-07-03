/*
 * W5500_driver_advanced.c
 *
 *  Created on: Jun 22, 2023
 *      Author: MateKocsis
 */

#include "main.h"
#include "w5500_driver.h"
#include <stdio.h>
#include <string.h>
#include <W5500_spi_lowLevel.h>
#include <W5500_driver_advanced.h>

void W5500_SocketNumberInit(SocketRegisterInit_HandleTypeDef* socket, uint8_t socketNumber){

	socket->socketNumber = socketNumber;

	switch(socketNumber){
			case 0:
				socket->S_BSB_REG = SOCK0_REG;
				socket->S_BSB_RX = SOCK0_RX;
				socket->S_BSB_TX = SOCK0_TX;
				break;
			case 1:
				socket->S_BSB_REG = SOCK1_REG;
				socket->S_BSB_RX = SOCK1_RX;
				socket->S_BSB_TX = SOCK1_TX;
				break;
			case 2:
				socket->S_BSB_REG = SOCK2_REG;
				socket->S_BSB_RX = SOCK2_RX;
				socket->S_BSB_TX = SOCK2_TX;
				break;
			case 3:
				socket->S_BSB_REG = SOCK3_REG;
				socket->S_BSB_RX = SOCK3_RX;
				socket->S_BSB_TX = SOCK3_TX;
				break;
			case 4:
				socket->S_BSB_REG = SOCK4_REG;
				socket->S_BSB_RX = SOCK4_RX;
				socket->S_BSB_TX = SOCK4_TX;
				break;
			case 5:
				socket->S_BSB_REG = SOCK5_REG;
				socket->S_BSB_RX = SOCK5_RX;
				socket->S_BSB_TX = SOCK5_TX;
				break;
			case 6:
				socket->S_BSB_REG = SOCK6_REG;
				socket->S_BSB_RX = SOCK6_RX;
				socket->S_BSB_TX = SOCK6_TX;
				break;
			case 7:
				socket->S_BSB_REG = SOCK7_REG;
				socket->S_BSB_RX = SOCK7_RX;
				socket->S_BSB_TX = SOCK7_TX;
				break;
		}
};

uint16_t intFromArray(uint8_t* array){
	return (array[0]<<8) | array[1];
}

void W5500_SetCommonRegister(int registerName, uint64_t value){
	CommonRegisterInit_HandleTypeDef comreg;

	switch (registerName){
		case MR:
			copyToArray(&value, &comreg.MR, 1);
			W5500_SPI_Send(MR_ADDR, COMM_REG, 1, &comreg.MR);
			break;
		case GAR:
			copyToArray(&value, comreg.GAR, 4);
			W5500_SPI_Send(GAR_ADDR, COMM_REG, 4, comreg.GAR);
			break;
		case SUBR:
			copyToArray(&value, comreg.SUBR, 4);
			W5500_SPI_Send(SUBR_ADDR, COMM_REG, 4, comreg.SUBR);
			break;
		case SHAR:
			copyToArray(&value, comreg.SHAR, 6);
			W5500_SPI_Send(SHAR_ADDR, COMM_REG, 6, comreg.SHAR);
			break;
		case SIPR:
			copyToArray(&value, comreg.SIPR, 4);
			W5500_SPI_Send(SIPR_ADDR, COMM_REG, 4, comreg.SIPR);
			break;
		case INTLEVEL:
			copyToArray(&value, comreg.INTLEVEL, 2);
			W5500_SPI_Send(INTLEVEL_ADDR, COMM_REG, 2, comreg.INTLEVEL);
			break;
		case IR:
			copyToArray(&value, &comreg.IR, 1);
			W5500_SPI_Send(IR_ADDR, COMM_REG, 1, &comreg.IR);
			break;
		case IMR:
			copyToArray(&value, &comreg.IMR, 1);
			W5500_SPI_Send(IMR_ADDR, COMM_REG, 1, &comreg.IMR);
			break;
		case SIR:
			copyToArray(&value, &comreg.SIR, 1);
			W5500_SPI_Send(SIR_ADDR, COMM_REG, 1, &comreg.SIR);
			break;
		case SIMR:
			copyToArray(&value, &comreg.SIMR, 1);
			W5500_SPI_Send(SIMR_ADDR, COMM_REG, 1, &comreg.SIMR);
			break;
		case RTR:
			copyToArray(&value, comreg.RTR, 2);
			W5500_SPI_Send(RTR_ADDR, COMM_REG, 2, comreg.RTR);
			break;
		case RCR:
			copyToArray(&value, &comreg.RCR, 1);
			W5500_SPI_Send(RCR_ADDR, COMM_REG, 1, &comreg.RCR);
			break;
		case PTIMER:
			copyToArray(&value, &comreg.PTIMER, 1);
			W5500_SPI_Send(PTIMER_ADDR, COMM_REG, 1, &comreg.PTIMER);
			break;
		case PMAGIC:
			copyToArray(&value, &comreg.PMAGIC, 1);
			W5500_SPI_Send(PMAGIC_ADDR, COMM_REG, 1, &comreg.PMAGIC);
			break;
		case PHAR:
			copyToArray(&value, comreg.PHAR, 6);
			W5500_SPI_Send(PHAR_ADDR, COMM_REG, 6, comreg.PHAR);
			break;
		case PSID:
			copyToArray(&value, comreg.PSID, 2);
			W5500_SPI_Send(PSID_ADDR, COMM_REG, 2, comreg.PSID);
			break;
		case PMRU:
			copyToArray(&value, comreg.PMRU, 2);
			W5500_SPI_Send(PMRU_ADDR, COMM_REG, 2, comreg.PMRU);
			break;
		case PHYCFGR:
			copyToArray(&value, &comreg.PHYCFGR, 1);
			W5500_SPI_Send(PHYCFGR_ADDR, COMM_REG, 1, &comreg.PHYCFGR);
			break;
	}

}

void W5500_SetSocketRegister(uint8_t socketNumber, int registerName, uint64_t value){

	SocketRegisterInit_HandleTypeDef socket;
	W5500_SocketNumberInit(&socket, socketNumber);

	switch (registerName){

		case S_MR:
			copyToArray(&value, &socket.S_MR, 1);
			W5500_SPI_Send(S_MR_ADDR, socket.S_BSB_REG, 1, &socket.S_MR);
			break;
		case S_CR:
			copyToArray(&value, &socket.S_CR, 1);
			W5500_SPI_Send(S_CR_ADDR, socket.S_BSB_REG, 1, &socket.S_CR);
			break;
		case S_IR:
			copyToArray(&value, &socket.S_IR, 1);
			W5500_SPI_Send(S_IR_ADDR, socket.S_BSB_REG, 1, &socket.S_IR);
			break;
		case S_SR:
			copyToArray(&value, &socket.S_SR, 1);
			W5500_SPI_Send(S_SR_ADDR, socket.S_BSB_REG, 1, &socket.S_SR);
			break;
		case S_PORT:
			copyToArray(&value, socket.S_PORT, 2);
			W5500_SPI_Send(S_PORT_ADDR, socket.S_BSB_REG, 2, socket.S_PORT);
			break;
		case S_DHAR:
			copyToArray(&value, socket.S_DHAR, 6);
			W5500_SPI_Send(S_DHAR_ADDR, socket.S_BSB_REG, 6, socket.S_DHAR);
			break;
		case S_DIPR:
			copyToArray(&value, socket.S_DIPR, 4);
			W5500_SPI_Send(S_DIPR_ADDR, socket.S_BSB_REG, 4, socket.S_DIPR);
			break;
		case S_DPORT:
			copyToArray(&value, socket.S_DPORT, 2);
			W5500_SPI_Send(S_DPORT_ADDR, socket.S_BSB_REG, 2, socket.S_DPORT);
			break;
		case S_MSSR:
			copyToArray(&value, socket.S_MSSR, 2);
			W5500_SPI_Send(S_MSSR_ADDR, socket.S_BSB_REG, 2, socket.S_MSSR);
			break;
		case S_TOS:
			copyToArray(&value, &socket.S_TOS, 1);
			W5500_SPI_Send(S_TOS_ADDR, socket.S_BSB_REG, 1, &socket.S_TOS);
			break;
		case S_TTL:
			copyToArray(&value, &socket.S_TTL, 1);
			W5500_SPI_Send(S_TTL_ADDR, socket.S_BSB_REG, 1, &socket.S_TTL);
			break;
		case S_RXBUF_SIZE:
			copyToArray(&value, &socket.S_RXBUF_SIZE, 1);
			W5500_SPI_Send(S_RXBUF_SIZE_ADDR, socket.S_BSB_REG, 1, &socket.S_RXBUF_SIZE);
			break;
		case S_TXBUF_SIZE:
			copyToArray(&value, &socket.S_TXBUF_SIZE, 1);
			W5500_SPI_Send(S_TXBUF_SIZE_ADDR, socket.S_BSB_REG, 1, &socket.S_TXBUF_SIZE);
			break;
		case S_TX_WR:
			copyToArray(&value, socket.S_TX_WR, 2);
			W5500_SPI_Send(S_TX_WR_ADDR, socket.S_BSB_REG, 2, socket.S_TX_WR);
			break;
		case S_RX_RD:
			copyToArray(&value, socket.S_RX_RD, 2);
			W5500_SPI_Send(S_RX_RD_ADDR, socket.S_BSB_REG, 2, socket.S_RX_RD);
			break;
		case S_IMR:
			copyToArray(&value, &socket.S_IMR, 1);
			W5500_SPI_Send(S_IMR_ADDR, socket.S_BSB_REG, 1, &socket.S_IMR);
			break;
		case S_FRAG:
			copyToArray(&value, socket.S_FRAG, 2);
			W5500_SPI_Send(S_FRAG_ADDR, socket.S_BSB_REG, 2, socket.S_FRAG);
			break;
		case S_KPALVTR:
			copyToArray(&value, &socket.S_KPALVTR, 1);
			W5500_SPI_Send(S_KPALVTR_ADDR, socket.S_BSB_REG, 1, &socket.S_KPALVTR);
			break;
	}

};

void copyToArray(uint8_t *copyFrom, uint8_t *copyTo, uint16_t length){

	copyFrom = copyFrom+(length-1);
	for(int i = 0; i<length; i++){
		copyTo[i] = *copyFrom;
		copyFrom--;
	}
}




















