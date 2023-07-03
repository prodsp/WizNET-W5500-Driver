/*
 * W5500_spi_lowLevel.h
 *
 *  Created on: Jul 14, 2022
 *      Author: MateKocsis
 */

#ifndef INC_W5500_SPI_LOWLEVEL_H_
#define INC_W5500_SPI_LOWLEVEL_H_

/*
 * W5500_SPI_Init() initializes which pin has been chosen for the chip select operation.
 * */
void W5500_SPI_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x, SPI_HandleTypeDef* hspi1);

/*
 * W5500_SPI_Send() transmits data to a specified memory area in the W5500 form a chosen array.
 * */
void W5500_SPI_Send(uint16_t offset_addres, uint8_t BSB,
		uint16_t send_dataLength, uint8_t* pData);

/*
 * W5500_SPI_Recieve() receives data from a specified memory area from the W5500 to a chosen array.
 * */
void W5500_SPI_Recieve(uint16_t offset_addres, uint8_t BSB,
		uint16_t recv_dataLength, uint8_t* pDestination);

#endif /* INC_W5500_SPI_LOWLEVEL_H_ */
