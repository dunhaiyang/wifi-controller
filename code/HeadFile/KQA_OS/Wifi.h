#ifndef __WIFI_H_
#define __WIFI_H_



#include "OS_HAL.h"


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;
	
	// 公共接口
	//
	// 设置wifi属性（这些属性会固化到wifi中， 下一次就不需要设置了）
	//
	ProcVoid_Void				getUart;					// wifi 获取串口波特率信息
	
	ProcVoidP_Void				linkAP;						// wifi 连接ap站点
	
	ProcVoid_Void				queryMac;					// wifi 查询MAC地址
	
	ProcVoid_Void				reboot;						// wifi 重启
	
	ProcVoid_Void				scan;						// wifi 扫描
	
	ProcVoid_Void				hotspotStatus;				// wifi 热点连接状态
	
	ProcVoid_Void				serverStatus;				// wifi 服务器连接状态
	
	ProcVoid_Void				dhcp;						// wifi 查看DHCP分配的ip，掩码等信息
	
	ProcUint8P_Void				ping;						// wifi ping
	
	ProcVoidP_Void				connectServer;				// wifi 连接远程服务器
	
	ProcVoid_Void				disconnectServer;			// wifi 断开连接远程服务器
	
	// 接收数据
	//
	ProcVoidPUint8_Void			write;						// wifi 发送数据
	
	ProcUint8P_Uint16			read;					// wifi 接收数据
	
}Wifi;


void Wifi_Init(void *self);



#endif

