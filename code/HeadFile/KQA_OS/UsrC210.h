#ifndef __USRC210_H_
#define __USRC210_H_


#include "Uart2.h"


void UsrC210_Init(void);


void UsrC210_GetUart(void);										// 获取串口波特率


void UsrC210_Scan(void);										// 扫描wifi热点


void UsrC210_LinkAP(uint8_t *ssid, uint8_t *key);				// 连接wifi热点


void UsrC210_HotspotStatus(void);								// 查询连接wifi热点状态


void UsrC210_Dhcp(void);										// 查询本模块通过dhcp分配到的ip资源


void UsrC210_Ping(uint8_t *ip);									// ping 一个ip


void UsrC210_connectServer(uint8_t *ip, uint8_t *port);			// 连接服务器（UDP）


void UsrC210_ServerStatus(void);								// 查询连接服务器状态（只能用于tcp， 本模块暂时只支持udp，所以这个接口没用）


void UsrC210_disconnectServer(void);							// 断开服务器连接（只能用于tcp， 本模块暂时只支持udp，所以这个接口没用）


void UsrC210_QueryMac(void);									// 查询wifi模块mac地址


void UsrC210_Reboot(void);										// 重启wifi模块


#endif