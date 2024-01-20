/*
 * app_udp.c
 *
 *  Created on: 17. 3. 2022
 *      Author: tomas
 */


#include "app_udp.h"
#include "app_params.h"

uint8_t  last_message_ip[4];
uint8_t  endpoint_ip[4];
uint32_t	endpoint_port;

wiz_NetInfo myNetInfo =
{
    .mac  = { 0x21, 0x96, 0x9D, 0x03, 0x60, 0xE1 },
	.ip = {192, 168, 0, 22},
	.sn = {255, 255, 255, 0},
	.gw = {192, 168, 0, 1},
	.dns = {192, 168, 0, 1},
    .dhcp = NETINFO_STATIC
};

//ip_addr_t last_message_ip;
//ip_addr_t my_ip;
//ip_addr_t endpoint_ip;
//struct udp_pcb * udp_pcb;


void ETH_StoreMac_1(uint32_t mac)
{
	MainParams.MAC_aadress_1_3MSB = mac;
}

void ETH_StoreMac_2(uint32_t mac)
{
	MainParams.MAC_aadress_2_3LSB = mac;
}

/* @brief store device ip address to sram
 *
 * @param ip -> ip address
 *
 */
void ETH_StoreIP(uint32_t ip)
{
	MainParams.IP_ADDRESS = ip;
}

/* @brief store device netmask address to sram
 *
 * @param netmask -> netmask address
 *
 */
void ETH_StoreNETMASK(uint32_t netmask)
{
	MainParams.NETMASK_ADDRESS = netmask;
}

/* @brief store device gateway address to sram
 *
 * @param gateway -> gateway address
 *
 */
void ETH_StoreGATEWAY(uint32_t gateway)
{
	MainParams.GATEWAY_ADDRESS = gateway;
}

void ETH_Store_UdpRecPort(uint32_t port)
{
	MainParams.UdpRecvPort = port;
}

/* @brief get ip address from sram
 *
 *
 */
uint32_t ETH_GetIP()
{
	uint32_t temp = ip_MAKEU32(myNetInfo.ip[0], myNetInfo.ip[1], myNetInfo.ip[2], myNetInfo.ip[3]);
	return temp;
}

/* @brief get netmask from sram
 *
 *
 */
uint32_t ETH_GetNETMASK()
{
	uint32_t temp = ip_MAKEU32(myNetInfo.sn[0], myNetInfo.sn[1], myNetInfo.sn[2], myNetInfo.sn[3]);
	return temp;

}

/* @brief get gateway address from sram
 *
 *
 */
uint32_t ETH_GetGATEWAY()
{
	uint32_t temp = ip_MAKEU32(myNetInfo.gw[0], myNetInfo.gw[1], myNetInfo.gw[2], myNetInfo.gw[3]);
	return temp;
}








void W5500_Select(void)
{
    HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
}

void W5500_Unselect(void)
{
    HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}

void W5500_ReadBuff(uint8_t* buff, uint16_t len)
{
    HAL_SPI_Receive(&hspi3, buff, len, HAL_MAX_DELAY);
}

void W5500_WriteBuff(uint8_t* buff, uint16_t len)
{
    HAL_SPI_Transmit(&hspi3, buff, len, HAL_MAX_DELAY);
}

uint8_t W5500_ReadByte(void)
{
    uint8_t byte;
    W5500_ReadBuff(&byte, sizeof(byte));
    return byte;
}

void W5500_WriteByte(uint8_t byte)
{
    W5500_WriteBuff(&byte, sizeof(byte));
}


/* @brief send setting of ethernet
 *
 *
 */
void ETH_SendSetting()
{

	SendCommunication_u32(cmd_ip_get_mac_1, MainParams.MAC_aadress_1_3MSB);
	SendCommunication_u32(cmd_ip_get_mac_2, MainParams.MAC_aadress_2_3LSB);

	SendCommunication_u32(cmd_ip_get_myip, MainParams.IP_ADDRESS);
	SendCommunication_u32(cmd_ip_get_mymask, MainParams.NETMASK_ADDRESS);
	SendCommunication_u32(cmd_ip_get_mygatew, MainParams.GATEWAY_ADDRESS);

	SendCommunication(cmd_ip_get_UdpRecvPort, MainParams.UdpRecvPort);

	//SendCommunication_u32(cmd_ip_get_myip, ETH_GetIP());
	//SendCommunication_u32(cmd_ip_get_mymask, ETH_GetNETMASK());
	//SendCommunication_u32(cmd_ip_get_mygatew, ETH_GetGATEWAY());
}




void ETH_load_ip()
{
	uint32_t x;


	x = MainParams.MAC_aadress_1_3MSB;
	myNetInfo.mac[0] = mac_GET8(x,0);
	myNetInfo.mac[1] = mac_GET8(x,1);
	myNetInfo.mac[2] = mac_GET8(x,2);

	x = MainParams.MAC_aadress_2_3LSB;
	myNetInfo.mac[3] = mac_GET8(x,0);
	myNetInfo.mac[4] = mac_GET8(x,1);
	myNetInfo.mac[5] = mac_GET8(x,2);


	x = MainParams.IP_ADDRESS;
	myNetInfo.ip[0] = ip_GET8(x,0);
	myNetInfo.ip[1] = ip_GET8(x,1);
	myNetInfo.ip[2] = ip_GET8(x,2);
	myNetInfo.ip[3] = ip_GET8(x,3);

	x = MainParams.NETMASK_ADDRESS;
	myNetInfo.sn[0] = ip_GET8(x,0);
	myNetInfo.sn[1] = ip_GET8(x,1);
	myNetInfo.sn[2] = ip_GET8(x,2);
	myNetInfo.sn[3] = ip_GET8(x,3);

	x = MainParams.GATEWAY_ADDRESS;
	myNetInfo.gw[0] = ip_GET8(x,0);
	myNetInfo.gw[1] = ip_GET8(x,1);
	myNetInfo.gw[2] = ip_GET8(x,2);
	myNetInfo.gw[3] = ip_GET8(x,3);

	myNetInfo.dns[0] = ip_GET8(x,0);
	myNetInfo.dns[1] = ip_GET8(x,1);
	myNetInfo.dns[2] = ip_GET8(x,2);
	myNetInfo.dns[3] = ip_GET8(x,3);

}

/* @brief UDP communication init
 *
 *
 */
void ETH_udp_Init()
{
	//ip_addr_get_ip4_u32(&(my_ip.addr));
	//IP4_ADDR(&my_ip,192,168,1,22);
	//IP4_ADDR(&endpoint_ip,192,168,1,100);
	//---------udp_pcb = udp_new();
	//udp_bind(udp_pcb, &my_ip, UDP_PORT);
	//---------udp_bind(udp_pcb, IP46_ADDR_ANY(), UDP_PORT);
	//---------udp_connect(udp_pcb, IP46_ADDR_ANY(), UDP_PORT);
	//udp_connect(udp_pcb, &endpoint_ip, UDP_PORT);

	//---------udp_recv(udp_pcb, UDP_Receiver_handler, NULL);

    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
    reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);

    uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
    wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);


    ETH_load_ip();

    wizchip_setnetinfo(&myNetInfo);

    int udp_socket = socket(UDP_SOCKET, Sn_MR_UDP, UDP_PORT, SF_IO_NONBLOCK);

    if(udp_socket != UDP_SOCKET)
    {
    	//error
    	return;
    }

}


/* @brief store UDP endpoint
 *
 *
 */
void ETH_udp_StoreEndpoint(uint32_t port)
{
	//---------endpoint_ip = last_message_ip;
	//---------udp_connect(udp_pcb, &endpoint_ip, UDP_PORT);

		//memcpy(endpoint_ip,last_message_ip,sizeof(last_message_ip));

	endpoint_ip[0] = last_message_ip[0];
	endpoint_ip[1] = last_message_ip[1];
	endpoint_ip[2] = last_message_ip[2];
	endpoint_ip[3] = last_message_ip[3];

	endpoint_port = port;

}


/* @brief send data by UDP
 *
 * @param *pData -> pointer on data to send
 * @param Size -> Size od data
 *
 */
void ETH_udp_Transmit(uint8_t *pData, uint16_t Size)
{
	//---------struct pbuf * pb;

	//---------pb = pbuf_alloc(PBUF_TRANSPORT, Size, PBUF_REF);
	//---------pb->payload = pData;
	//---------pb->len = pb->tot_len = Size;
	//---------udp_send(udp_pcb, pb);
	//---------pbuf_free(pb);

	//int result = sendto(UDP_SOCKET, pData, Size, address, UDP_PORT);

	int  ret;
	//uint16_t sentsize;

    //while(!(sentsize >= Size))
    //{

    	ret = sendto(UDP_SOCKET, pData, Size, endpoint_ip, endpoint_port);
    	//ret = sendto(UDP_SOCKET, pData+sentsize, Size-sentsize, endpoint_ip, UDP_PORT);

    	//char buff[256];
    	//int size = sprintf(buff, "ret=%d\r\n",ret);
        //HAL_UART_Transmit(&huart2, (uint8_t*)buff, size,HAL_MAX_DELAY);


    	if(ret < 0)
    	{
    		//return;
    	}

    	//sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
    //}


}


void ETH_udp_Receive()
{

	int32_t  ret;
	uint8_t buf[DATA_BUF_SIZE];
	uint16_t size;
	uint16_t destport;

	size = getSn_RX_RSR(UDP_SOCKET);

    if(size > 0)
    {

    	if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;

    	ret = recvfrom(UDP_SOCKET, buf, size, last_message_ip, (uint16_t*)&destport);


    	if(ret <= 0)
    	{
    		return;
    	}

    	size = (uint16_t) ret;


    	ETH_WriteBuffer(buf, size);

    }


}

