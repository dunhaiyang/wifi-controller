#include "UsrC210.h"


// ------------------------------------------------˽�нӿ�-----------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
//


// ����ָ��ģʽ��200msָ��ܷ�������ָ�Ȼ���͡�+++�����ȴ�'a'��Ȼ����'a'������ʱָ��ģʽ��
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


// ��ȡ���ڲ���
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


// ɨ������
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


// ���ù���ģʽ��AP�� STATION
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


// ��ΪSTA����AP
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


// ��ѯDHCP��ȡ����IP�����أ������
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


// ��ѯwifi����״̬
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


// ����Զ�̷�����
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


// ��ѯ������tcp����״̬
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



// �Ͽ�����������
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


// ��ѯmac��ַ
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


// ����ģ�飬��Ч
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



// �˳�ָ��ģʽ
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


// ------------------------------------------------�����ӿ�-----------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
//


void UsrC210_Init(void)
{
	Uart2_Init();
	
//	WIFI_NRELOAD = 1;											// Ĭ������
	
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



// ��ȡ���ڲ�����
//
void UsrC210_GetUart(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWMODE();
	
	UsrC210_ATUART();
	
	UsrC210_ExitCommandMode();
}


// ɨ��wifi�ȵ�
//
void UsrC210_Scan(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWSCAN();
	
	UsrC210_ExitCommandMode();
}



// ����wifi�ȵ�
//
void UsrC210_LinkAP(uint8_t *ssid, uint8_t *key)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWMODE();
	
	UsrC210_ATWSTA(ssid, key);
	
	UsrC210_ExitCommandMode();
}


// ��ѯwifi�ȵ�����״̬
//
void UsrC210_HotspotStatus(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWSLK();
	
	UsrC210_ExitCommandMode();
}


// ��ѯdhcp�����ip��
//
void UsrC210_Dhcp(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATWANN();
	
	UsrC210_ExitCommandMode();
}


// ping һ��ip
//
void UsrC210_Ping(uint8_t *ip)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATPING(ip);
	
	UsrC210_ExitCommandMode();
}


// ���ӷ�����
//
void UsrC210_connectServer(uint8_t *ip, uint8_t *port)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKA(ip, port);
	
	UsrC210_ExitCommandMode();
}


// ��ѯ������������״̬
//
void UsrC210_ServerStatus(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKLKA();
	
	UsrC210_ExitCommandMode();
}


// �Ͽ�������������
//
void UsrC210_disconnectServer(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATSOCKDISA();
	
	UsrC210_ExitCommandMode();
}


// ��ѯmac��ַ
//
void UsrC210_QueryMac(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATMAC();
	
	UsrC210_ExitCommandMode();
}


// ����wifiģ��
//
void UsrC210_Reboot(void)
{
	UsrC210_EnterCommandMode();
	
	UsrC210_ATZ();
	
	UsrC210_ExitCommandMode();
}







