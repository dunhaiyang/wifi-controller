#ifndef __USRC210_H_
#define __USRC210_H_


#include "Uart2.h"


void UsrC210_Init(void);


void UsrC210_GetUart(void);										// ��ȡ���ڲ�����


void UsrC210_Scan(void);										// ɨ��wifi�ȵ�


void UsrC210_LinkAP(uint8_t *ssid, uint8_t *key);				// ����wifi�ȵ�


void UsrC210_HotspotStatus(void);								// ��ѯ����wifi�ȵ�״̬


void UsrC210_Dhcp(void);										// ��ѯ��ģ��ͨ��dhcp���䵽��ip��Դ


void UsrC210_Ping(uint8_t *ip);									// ping һ��ip


void UsrC210_connectServer(uint8_t *ip, uint8_t *port);			// ���ӷ�������UDP��


void UsrC210_ServerStatus(void);								// ��ѯ���ӷ�����״̬��ֻ������tcp�� ��ģ����ʱֻ֧��udp����������ӿ�û�ã�


void UsrC210_disconnectServer(void);							// �Ͽ����������ӣ�ֻ������tcp�� ��ģ����ʱֻ֧��udp����������ӿ�û�ã�


void UsrC210_QueryMac(void);									// ��ѯwifiģ��mac��ַ


void UsrC210_Reboot(void);										// ����wifiģ��


#endif