/*
 * app_udp.h
 *
 *  Created on: 17. 3. 2022
 *      Author: tomas
 */

#ifndef INC_APP_UDP_H_
#define INC_APP_UDP_H_

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//#include "lwip.h"
//#include "../Middlewares/Third_Party/LwIP/src/include/lwip/udp.h"

#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include "socket.h"
#include "dhcp.h"
#include "dns.h"


#include "app_eth_process.h"


#ifndef DATA_BUF_SIZE
	#define DATA_BUF_SIZE			4096
#endif

#define UDP_SOCKET 3

#define UDP_PORT 5005



#define ip_GET8(ip,byte_position) ((uint8_t)((ip >> ((3-byte_position) * 8)) & 0xff))
#define ip_MAKEU32(a,b,c,d) (((uint32_t)((a) & 0xff) << 24) | \
                               ((uint32_t)((b) & 0xff) << 16) | \
                               ((uint32_t)((c) & 0xff) << 8)  | \
                                (uint32_t)((d) & 0xff))



void ETH_StoreIP(uint32_t ip);
void ETH_StoreNETMASK(uint32_t netmask);
void ETH_StoreGATEWAY(uint32_t gateway);
uint32_t ETH_GetIP();
uint32_t ETH_GetNETMASK();
uint32_t ETH_GetGATEWAY();
void ETH_SendSetting();


void ETH_udp_Init();
void ETH_udp_StoreEndpoint();
void ETH_udp_Transmit(uint8_t *pData, uint16_t Size);
void ETH_udp_Receive();

#endif /* INC_APP_UDP_H_ */
