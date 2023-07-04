# WizNET-W5500-Driver
This repository contains a compact, platform independent and  easy to integrate driver for WizNet W5500 IC and Ethernet Shield.
## Introduction
This driver is designed as an open-source project so feel free to suggest changes or provide feedback. The main goal was to create a driver which everyone can easily integrate and use. If you have a microcontroller which has SPI compatibility and you want to communicate through Ethernet, but it has no Ethernet port, the WizNET W5500 Ethernet shield could be a perfect solution for you and thanks to this driver the developement process won't take a bunch of time from you. 
## Use
### Platform independency
This is a platform independent driver which means you can use it with nearly all type of microcontrollers. To reach this functionality we've separated the SPI communication as an independent transfer layer therefore you can implement the communication without a deep understanding of the driver.
### How to integrate and use the driver
1. Copy the header and the source files into your project
2. Implement the SPI communication in the SPI_Communication.c file
3. Use the driver API to initialize the sockets -_W5500_TcpipSocketRegInit()_- and the general settings -_W5500_TcpipCommonRegInit_-
   >* This init functions provide you a standard settings for TCP communication<br>
   >* For change this settings you can use the _W5500_SetCommonRegister()_ and the _W5500_SetSocketRegister_ functions<br>
   >* For UDP protocol, you can use the TCP init functions and overwrite the necessary registers or you must implement an other init function for UDP protocol
4. Use the W5500_Driver API for Ethernet communication
### Advanced Driver Layer
This layer has their own API which provide you a complete access for the WizNET's registers. With this API you can modify the Ethernet protocol settings, SPI protocol settings, memory management settings and so on.
### SPI Low Level Layer
This layer generates the SPI frame for the send and receive methodes.
### Driver API
* Initialization
   - W5500_TcpipCommonRegInit() --> set the basic parameters of the WizNET (e.g. IP address or MAC address)
   - W5500_TcpipSocketRegInit() --> set the basic TCP parameters of a socket (e.g. port)
* Socket Handling
   - W5500_SocketCommand()
   - W5500_GetSocketStatus()
   - W5500_SocketReopen()
* Data Streaming
   - W5500_Send()
   - W5500_Receive()
## Communication Parameters
|Measurement|Value|Package size|
|:----:|:----:|:----:|
|RTT|2.876 ms|1 byte|
|RTT|3.008 ms|10 byte|
|RTT|5.116 ms|100 byte|
|RTT|23.884 ms|1000 byte|
|iRTT|0.6153 ms||
|Sending Latency|0.6720 ms|1 byte|
|Sending Latency|0.713 ms|10 byte|
|Sending Latency|1.131 ms|100 byte|
|Sending Latency|5.309 ms|1000 byte|
|Throughput|1800 msg/sec|1 byte|
|Throughput|1700 msg/sec|10 byte|
|Throughput|1000 msg/sec|100 byte|
|Throughput|200 msg/sec|1000 byte|
|Chance of Data Loss|<0,000025%|
## Usefull Links
WizNET W5500 product overview --> https://www.wiznet.io/product-item/w5500/<br>
WizNET W5500 datasheet --> https://docs.wiznet.io/Product/iEthernet/W5500/datasheet

