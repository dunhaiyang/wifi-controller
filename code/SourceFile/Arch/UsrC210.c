#include "UsrC210.h"


// ------------------------------------------------私有接口-----------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
//


// 进入指令模式（200ms指令不能发送其他指令，然后发送“+++”，等待'a'，然后发送'a'进入临时指令模式）
//
bool UsrC210_EnterCommandMode(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Delay1ms(200);
	
	Uart2_SendString("+++"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	Uart2_SendString("a"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 获取串口参数
//
bool UsrC210_ATUART(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+UART\r"); Uart2_SetMode1();
	
	Delay1ms(2000);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 扫描网络
//
bool UsrC210_ATWSCAN(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+WSCAN\r"); Uart2_SetMode1();
	
	Delay1ms(2000);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 设置工作模式，AP， STATION
//
bool UsrC210_ATWMODE(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+WMODE=STA\r"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 作为STA连接AP
//
bool UsrC210_ATWSTA(uint8_t *ssid, uint8_t *key)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
//	Uart2_SendString("AT+WSTA=kkk,12345678\r");
	Uart2_SendString("AT+WSTA=");
	Uart2_SendString(ssid);
	Uart2_SendByte(',');
	Uart2_SendString(key);
	Uart2_SendByte('\r'); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 查询DHCP获取到的IP，网关，掩码等
//
bool UsrC210_ATWANN(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+WANN\r"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 查询wifi连接状态
//
bool UsrC210_ATWSLK(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+WSLK\r"); Uart2_SetMode1();
	
	Delay1ms(500);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// ping
//
bool UsrC210_ATPING(uint8_t *ip)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+PING=");
	Uart2_SendString(ip);
	Uart2_SendByte('\r'); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 连接远程服务器
//
bool UsrC210_ATSOCKA(uint8_t *ip, uint8_t *port)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
//	Uart2_SendString("AT+SOCKA=TCPC,120.25.124.122,4002\r");
//	Uart2_SendString("AT+SOCKA=TCPC,");
	Uart2_SendString("AT+SOCKA=UDPS,");
	Uart2_SendString(ip);
	Uart2_SendByte(',');
	Uart2_SendString(port);
	Uart2_SendByte('\r'); Uart2_SetMode1();
	
	Delay1ms(500);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 查询服务器tcp连接状态
//
bool UsrC210_ATSOCKLKA(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+SOCKLKA\r"); Uart2_SetMode1();
	
	Delay1ms(500);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}



// 断开服务器连接
//
bool UsrC210_ATSOCKDISA(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+SOCKDISA=off\r\n"); Uart2_SetMode1();
	
	Delay1ms(500);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 查询mac地址
//
bool UsrC210_ATMAC(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+MAC\r"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}


// 重启模块，生效
//
bool UsrC210_ATZ(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+Z\r"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	return 1;
}



// 退出指令模式
//
bool UsrC210_ExitCommandMode(void)
{
	uint8_t *tmpBuffer;
	
	uint16_t  tmpBufferLen;
	
	Uart2_SendString("AT+ENTM\r"); Uart2_SetMode1();
	
	Delay1ms(300);
	
	tmpBufferLen = Uart2_Mode1_ReceiveString(&tmpBuffer);
	
	tmpBuffer[tmpBufferLen] = 0;
	
	printf("buffer[%u]: %s\r\n", tmpBufferLen, tmpBuffer);
	
	Uart2_SetMode0();
	
	return 1;
}


// ------------------------------------------------公共接口-----------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
//


void UsrC210_Init(void)
{
	Uart2_Init();
	
//	WIFI_NRELOAD = 1;											// 默认上拉
	
//	Delay1ms(5000);
//	
//	UsrC210_EnterCommandMode();
//	
//	UsrC210_ATWMODE(1);
//	
//	UsrC210_ATWSTA();
//	
//	UsrC210_ATMAC();
//	
//	UsrC210_ATWANN();
//	
//	UsrC210_ATWSLK();
//	
//	UsrC210_ATSOCKA();
//	
//	UsrC210_ATSOCKLKA();
//	
//	UsrC210_ExitCommandMode();
}



// 获取串口波特率
//
void UsrC210_GetUart(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWMODE();
	
	UsrC210_ATUART();
	
	UsrC210_ExitCommandMode();
}


// 扫描wifi热点
//
void UsrC210_Scan(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWSCAN();
	
	UsrC210_ExitCommandMode();
}



// 连接wifi热点
//
void UsrC210_LinkAP(uint8_t *ssid, uint8_t *key)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWMODE();
	
	UsrC210_ATWSTA(ssid, key);
	
	UsrC210_ExitCommandMode();
}


// 查询wifi热点连接状态
//
void UsrC210_HotspotStatus(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWSLK();
	
	UsrC210_ExitCommandMode();
}


// 查询dhcp分配的ip等
//
void UsrC210_Dhcp(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWANN();
	
	UsrC210_ExitCommandMode();
}


// ping 一个ip
//
void UsrC210_Ping(uint8_t *ip)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATPING(ip);
	
	UsrC210_ExitCommandMode();
}


// 连接服务器
//
void UsrC210_connectServer(uint8_t *ip, uint8_t *port)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKA(ip, port);
	
	UsrC210_ExitCommandMode();
}


// 查询服务器的连接状态
//
void UsrC210_ServerStatus(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKLKA();
	
	UsrC210_ExitCommandMode();
}


// 断开服务器的连接
//
void UsrC210_disconnectServer(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKDISA();
	
	UsrC210_ExitCommandMode();
}


// 查询mac地址
//
void UsrC210_QueryMac(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATMAC();
	
	UsrC210_ExitCommandMode();
}


// 重启wifi模块
//
void UsrC210_Reboot(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATZ();
	
	UsrC210_ExitCommandMode();
}







