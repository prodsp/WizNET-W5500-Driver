/*
 * W5500_example_Counter.h
 *
 *  Created on: Aug 2, 2022
 *      Author: MateKocsis
 *
 *  This example shows a long-term operation of the program.
 *  There is a timer implemented in this example. If the client send any data to the server,
 *  the server will transmit the actual value of the timer.
 *
 */

#ifndef INC_W5500_EXAMPLE_COUNTER_H_
#define INC_W5500_EXAMPLE_COUNTER_H_

/*
 * There is a counter implemented in this example.
 * The counter's value increases by 1 every second.
 * With the example_Counter_client.py you can query the value of the counter.
 * */
void W5500_Example_Counter_Run(SPI_HandleTypeDef* hspi1);


#endif /* INC_W5500_EXAMPLE_COUNTER_H_ */
