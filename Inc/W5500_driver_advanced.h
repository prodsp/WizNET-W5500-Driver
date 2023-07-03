/*
 * W5500_driver_advanced.h
 *
 *  Created on: Jun 22, 2023
 *      Author: MateKocsis
 */

#ifndef INC_W5500_DRIVER_ADVANCED_H_
#define INC_W5500_DRIVER_ADVANCED_H_

/*
 *Handle the Common Registers.
 * */
typedef struct{

	uint8_t MR;					/*Mode register*/

	uint8_t GAR[4];					/*Gateway IP Address Register*/

	uint8_t SUBR[4];				/*Subnet Mask Register*/

	uint8_t SHAR[6];				/*Source Hardware Address Register*/

	uint8_t SIPR[4];				/*Source IP Address Register*/

	uint8_t INTLEVEL[2];				/*Interrupt Low Level Timer Register*/

	uint8_t IR;					/*Interrupt Register*/

	uint8_t IMR;					/*Interrupt Mask Register*/

	uint8_t SIR;					/*Socket Interrupt Register*/

	uint8_t SIMR;					/*Socket Interrupt Mask Register*/

	uint8_t RTR[2];					/*Retry Time-value Register*/

	uint8_t RCR;					/*Retry Count Register*/

	uint8_t PTIMER;					/*PPP Link Control Protocol Request Timer Register*/

	uint8_t PMAGIC;					/*PPP Link Control Protocol Magic number Register*/

	uint8_t PHAR[6];				/*Destination Hardware Address Register in PPPoE mode*/

	uint8_t PSID[2];				/*Session ID Register in PPPoE mode*/

	uint8_t PMRU[2];				/*Maximum Receive Unit in PPPoE mode*/

	uint8_t PHYCFGR;				/*W5500 PHY Configuration Register*/


} CommonRegisterInit_HandleTypeDef;

/*
 * Handle a Socket's Registers.
 * */
typedef struct{

	uint8_t socketNumber;		/*{0,1,...,8}*/

	uint8_t S_BSB_REG;		/*Socket n Register*/

	uint8_t S_BSB_RX;		/*Socket n RX Buffer*/

	uint8_t S_BSB_TX;		/*Socket n TX Buffer*/

	uint8_t S_SR;			/*Socket Status Register*/

	uint8_t S_MR;			/*Socket Mode Register*/

	uint8_t S_CR;			/*Socket Command Register*/

	struct{
		union{
			uint8_t data;
			struct{
				uint8_t _CON:1;
				uint8_t _DISCON:1;
				uint8_t _RECV:1;
				uint8_t _TIMEOUT:1;
				uint8_t _SEND_OK:1;
				uint8_t : 3;
			};
		};
	}S_IR;				/*Socket Interrupt Register*/

	uint8_t S_PORT[2];		/*Socket Source Port Register*/

	uint8_t S_DHAR[6];		/*Socket Destination Hardware Address Register*/

	uint8_t S_DIPR[4];		/*Socket Destination IP Address Register*/

	uint8_t S_DPORT[2];		/*Socket Destination Port Register*/

	uint8_t S_MSSR[2];		/*Socket Maximum Segment Size Register*/

	uint8_t S_TOS;			/*Socket IP Type of Service Register*/

	uint8_t S_TTL;			/*Socket TTL Register*/

	uint8_t S_RXBUF_SIZE;		/*Socket RX Buffer Size Register*/

	uint8_t S_TXBUF_SIZE;		/*Socket TX Buffer Size Register*/

	uint8_t S_TX_WR[2];		/*Socket TX Write Pointer Register*/

	uint8_t S_TX_RD[2];		/*Socket TX Read Pointer Register*/

	uint8_t S_RX_RD[2];		/*Socket RX Read Data Pointer Register*/

	uint8_t S_RX_WR[2];		/*Socket RX Write Data Pointer Register*/

	uint8_t S_IMR;			/*Socket Interrupt Mask Register*/

	uint8_t S_FRAG[2];		/*Socket Fragment Register*/

	uint8_t S_KPALVTR;		/*Socket Keep Alive Time Register*/

} SocketRegisterInit_HandleTypeDef;

/*Offset Addresses of Common Registers---------------------------------------------------------------*/

#define MR_ADDR				(0x0000)		/*Mode register*/

#define GAR_ADDR			(0x0001)		/*Gateway IP Address Register*/

#define SUBR_ADDR			(0x0005)		/*Subnet Mask Register*/

#define SHAR_ADDR			(0x0009)		/*Source Hardware Address Register*/

#define SIPR_ADDR			(0x000F)		/*Source IP Address Register*/

#define INTLEVEL_ADDR			(0x0013)		/*Interrupt Low Level Timer Register*/

#define IR_ADDR				(0x0015)		/*Interrupt Register*/

#define IMR_ADDR			(0x0016)		/*Interrupt Mask Register*/

#define SIR_ADDR			(0x0017)		/*Socket Interrupt Register*/

#define SIMR_ADDR			(0x0018)		/*Socket Interrupt Mask Register*/

#define RTR_ADDR			(0x0019)		/*Retry Time-value Register*/

#define RCR_ADDR			(0x001B)		/*Retry Count Register*/

#define PTIMER_ADDR			(0x001C)		/*PPP Link Control Protocol Request Timer Register*/

#define PMAGIC_ADDR			(0x001D)		/*PPP Link Control Protocol Magic number Register*/

#define PHAR_ADDR			(0x001E)		/*Destination Hardware Address Register in PPPoE mode*/

#define PSID_ADDR			(0x0024)		/*Session ID Register in PPPoE mode*/

#define PMRU_ADDR			(0x0026)		/*Maximum Receive Unit in PPPoE mode*/

#define PHYCFGR_ADDR			(0x002E)		/*W5500 PHY Configuration Register*/

/*Offset Addresses of a Socket Registers------------------------------------------------------------*/

#define S_MR_ADDR			(0x0000)		/*Socket Mode Register*/

#define S_CR_ADDR			(0x0001)		/*Socket Command Register*/

#define S_IR_ADDR			(0x0002)		/*Socket Interrupt Register*/

#define S_SR_ADDR			(0x0003)		/*Socket Status Register*/

#define S_PORT_ADDR			(0x0004)		/*Socket Source Port Register*/

#define S_DHAR_ADDR			(0x0006)		/*Socket Destination Hardware Address Register*/

#define S_DIPR_ADDR			(0x000C)		/*Socket Destination IP Address Register*/

#define S_DPORT_ADDR			(0x0010)		/*Socket Destination Port Register*/

#define S_MSSR_ADDR			(0x0012)		/*Socket Maximum Segment Size Register*/

#define S_TOS_ADDR			(0x0015)		/*Socket IP Type of Service Register*/

#define S_TTL_ADDR			(0x0016)		/*Socket TTL Register*/

#define S_RXBUF_SIZE_ADDR		(0x001E)		/*Socket RX Buffer Size Register*/

#define S_TXBUF_SIZE_ADDR		(0x001F)		/*Socket TX Buffer Size Register*/

#define S_TX_WR_ADDR			(0x0024)		/*Socket TX Write Pointer Register*/

#define S_TX_RD_ADDR			(0x0022)		/*Socket TX Read Pointer Register*/

#define S_RX_RSR_ADDR			(0x0026)		/*Socket Received Size Register*/

#define S_RX_RD_ADDR			(0x0028)		/*Socket RX Read Data Pointer Register*/

#define S_RX_WR_ADDR			(0x002A)		/*Socket RX Write Data Pointer Register*/

#define S_IMR_ADDR			(0x002C)		/*Socket Interrupt Mask Register*/

#define S_FRAG_ADDR			(0x002D)		/*Socket Fragment Register*/

#define S_KPALVTR_ADDR			(0x002F)		/*Socket Keep Alive Time Register*/

/*Block Select Bits (BSB)------------------------------------------------------------------------*/

#define COMM_REG			(0b00000)		/*Common Register*/

#define SOCK0_REG			(0x01)			/*Socket 0 Register*/
#define SOCK0_TX			(0b00010)		/*Socket 0 TX Buffer*/
#define SOCK0_RX			(0b00011)		/*Socket 0 RX Buffer*/

#define SOCK1_REG			(0b00101)		/*Socket 1 Register*/
#define SOCK1_TX			(0b00110)		/*Socket 1 TX Buffer*/
#define SOCK1_RX			(0b00111)		/*Socket 1 RX Buffer*/

#define SOCK2_REG			(0b01001)		/*Socket 2 Register*/
#define SOCK2_TX			(0b01010)		/*Socket 2 TX Buffer*/
#define SOCK2_RX			(0b01011)		/*Socket 2 RX Buffer*/

#define SOCK3_REG			(0b01101)		/*Socket 3 Register*/
#define SOCK3_TX			(0b01110)		/*Socket 3 TX Buffer*/
#define SOCK3_RX			(0b01111)		/*Socket 3 RX Buffer*/

#define SOCK4_REG			(0b10001)		/*Socket 4 Register*/
#define SOCK4_TX			(0b10010)		/*Socket 4 TX Buffer*/
#define SOCK4_RX			(0b10011)		/*Socket 4 RX Buffer*/

#define SOCK5_REG			(0b10101)		/*Socket 5 Register*/
#define SOCK5_TX			(0b10110)		/*Socket 5 TX Buffer*/
#define SOCK5_RX			(0b10111)		/*Socket 5 RX Buffer*/

#define SOCK6_REG			(0b11001)		/*Socket 6 Register*/
#define SOCK6_TX			(0b11010)		/*Socket 6 TX Buffer*/
#define SOCK6_RX			(0b11011)		/*Socket 6 RX Buffer*/

#define SOCK7_REG			(0b11101)		/*Socket 7 Register*/
#define SOCK7_TX			(0b11110)		/*Socket 7 TX Buffer*/
#define SOCK7_RX			(0b11111)		/*Socket 7 RX Buffer*/

/*Register Names---------------------------------------------------------------------------------*/

enum registerNames{
	MR = 0,
	GAR = 1,
	SUBR = 2,
	SHAR = 3,
	SIPR = 4,
	INTLEVEL = 5,
	IR = 6,
	IMR = 7,
	SIR = 8,
	SIMR = 9,
	RTR = 10,
	RCR = 11,
	PTIMER = 12,
	PMAGIC = 13,
	PHAR = 14,
	PSID = 15,
	PMRU = 16,
	PHYCFGR = 17,
	S_MR = 18,
	S_CR = 19,
	S_IR = 20,
	S_SR = 21,
	S_PORT = 22,
	S_DHAR = 23,
	S_DIPR = 24,
	S_DPORT = 25,
	S_MSSR = 26,
	S_TOS = 27,
	S_TTL = 28,
	S_RXBUF_SIZE = 29,
	S_TXBUF_SIZE = 30,
	S_TX_WR = 31,
	S_RX_RD = 32,
	S_IMR = 33,
	S_FRAG = 34,
	S_KPALVTR = 35
};
/*Functions--------------------------------------------------------------------------------------*/

/*
 * Initialize the Block Select Bits (BSB).
 * */
void W5500_SocketNumberInit(SocketRegisterInit_HandleTypeDef* sockregInit, uint8_t socketNumber);

/*
 * Create an uint16_t from a uint8_t [2].
 * */
uint16_t intFromArray(uint8_t* array);

/*
 * Set a specific Common Register directly.
 * */
void W5500_SetCommonRegister(int registerName, uint64_t value);

/*
 * Set a specific Socket Register directly.
 * */
void W5500_SetSocketRegister(uint8_t socketNumber, int registerName, uint64_t value);

/*
 * Copy any type of number to an array of specified length.
 * */
void copyToArray(uint8_t *copyFrom, uint8_t *copyTo, uint16_t length);

#endif /* INC_W5500_DRIVER_ADVANCED_H_ */
