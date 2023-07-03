/*
 * w5500_driver.h
 *
 *  Created on: Jul 15, 2022
 *      Author: MateKocsis
 */

#ifndef W5500_DRIVER_INC_W5500_DRIVER_H_
#define W5500_DRIVER_INC_W5500_DRIVER_H_
/*-----------------------------------------------------------------------------------------------*/

/*Socket Commands--------------------------------------------------------------------------------*/

#define OPEN				(0x01)
#define LISTEN				(0x02)
#define CONNECT				(0x04)
#define DISCON				(0x08)
#define CLOSE				(0x10)
#define SEND				(0x20)
#define SEND_KEEP			(0x22)
#define RECV				(0x40)

/*Socket Status----------------------------------------------------------------------------------*/

#define SOCK_CLOSED			(0x00)
#define SOCK_INIT			(0x13)
#define SOCK_LISTEN			(0x14)
#define SOCK_ESTABLISHED	(0x17)
#define SOCK_CLOSE_WAIT		(0x1C)
#define SOCK_FIN_WAIT		(0x18)
#define SOCK_CLOSING		(0x1A)
#define SOCK_TIME_WAIT		(0x1B)

/*Functions--------------------------------------------------------------------------------------*/

/*
 * Send command (e.g. OPEN; CLOSE) for a chosen socket (0,1,...,7).
 * */
void W5500_SocketCommand(uint8_t socketNumber, uint8_t command);

/*
 * Transmit data to client.
 * */
void W5500_Send(uint8_t socketNumber, uint8_t* dataBuffer, uint16_t dataSize);

/*
 * Receive data from client.
 * */
uint16_t W5500_Receive(uint8_t socketNumber, uint8_t* recvBuffer);

/*
 * Close, reopen and reinitialize the chosen socket.
 * */
void W5500_SocketReopen(uint8_t socketNumber);

/*
 * Get the current state of a socket (e.g. SOCK_LISTEN; SOCK_ESTABLISHED).
 * */
void W5500_GetSocketStatus(uint8_t socketNumber, uint8_t* statusHandler);

/*
 * Initialize the WizNET for TCP/IP communication.
 * */
void W5500_TcpipCommonRegInit(uint32_t GatewayIpAddress, uint32_t SubnetMask, uint64_t SourceHardwareAddress,uint32_t SourceIpAddress);

/*
 * Initialize a socket for TCP/IP communication.
 * */
void W5500_TcpipSocketRegInit(uint8_t socketNumber, uint16_t sourcePort);


#endif /* W5500_DRIVER_INC_W5500_DRIVER_H_ */






























