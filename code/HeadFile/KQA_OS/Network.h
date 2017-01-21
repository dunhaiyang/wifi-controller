#ifndef __NETWORK_H_
#define __NETWORK_H_


#include "OS_HAL.h"


typedef struct
{
	uint8_t	 	ip[4];
	
	uint8_t  	gateway[4];
	
	uint8_t  	mask[4];
	
	uint8_t  	mac[6];
	
}NetworkParameter;


extern	NetworkParameter						Network_Parameter;


#define NETPARA_IP								Network_Parameter.ip


#define NETPARA_GATEWAY							Network_Parameter.gateway


#define NETPARA_MASK							Network_Parameter.mask


#define NETPARA_MAC								Network_Parameter.mac


typedef struct
{
	uint16_t 	localPort;
	
	uint16_t 	remotePort;
	
	uint8_t	 	remoteIp[4];
	
}NetworkSocket;


extern	NetworkSocket							Network_Socket0;


#define SOCKET0_LOCALPORT						Network_Socket0.localPort


#define SOCKET0_REMOTEPORT						Network_Socket0.remotePort


#define SOCKET0_REMOTEIP						Network_Socket0.remoteIp


typedef struct
{
	uint16_t	receiveOk:1;					// 接收已经解析到数据
	
	uint16_t 	receiveBufferCount:15;			// 接收缓存数据大小
	
	uint8_t		__receiveBuffer[120];			// 内部接收缓存区（没有去掉帧结构的数据）

	uint8_t		receiveBuffer[60];				// 外部接收缓存区（去掉帧结构的数据）
	
	uint8_t		__sendBuffer[120];				// 内部发送缓存区（加上帧结构的数据）
	
	uint8_t		sendBuffer[80];					// 外部发送缓存区（没有加上帧结构的数据）
	
}NetworkBoardcastData;


extern  NetworkBoardcastData					Network_BoardcastData;


#define	BoardcastData_ReceiveOk					Network_BoardcastData.receiveOk


#define	BoardcastData_ReceiveBufferCount		Network_BoardcastData.receiveBufferCount


#define	__BoardcastData_ReceiveBuffer			Network_BoardcastData.__receiveBuffer


#define	BoardcastData_ReceiveBuffer				Network_BoardcastData.receiveBuffer


#define	__BoardcastData_SendBuffer				Network_SocketData.__sendBuffer


#define	BoardcastData_SendBuffer				Network_SocketData.sendBuffer



typedef struct
{
	uint16_t	receiveOk:1;					// 接收已经解析到数据
	
	uint16_t 	receiveBufferCount:15;			// 接收缓存数据大小
	
	uint8_t		__receiveBuffer[120];			// 内部接收缓存区（没有去掉帧结构的数据）

	uint8_t		receiveBuffer[80];				// 外部接收缓存区（去掉帧结构的数据）
	
	uint8_t		__sendBuffer[255];				// 内部发送缓存区（加上帧结构的数据）
	
	uint8_t		sendBuffer[200];				// 外部发送缓存区（没有加上帧结构的数据）
	
}NetworkSocketData;


extern	NetworkSocketData						Network_SocketData;


#define	SocketData_ReceiveOk					Network_SocketData.receiveOk


#define	SocketData_ReceiveBufferCount			Network_SocketData.receiveBufferCount


#define	__SocketData_ReceiveBuffer				Network_SocketData.__receiveBuffer


#define	SocketData_ReceiveBuffer				Network_SocketData.receiveBuffer


#define	__SocketData_SendBuffer					Network_SocketData.__sendBuffer


#define	SocketData_SendBuffer					Network_SocketData.sendBuffer


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;	

	ProcVoid_Void				error;
	
	
	// 私有数据（用于调试）
	//
	uint16_t  					globalStatus;					// 全局状态（不可达，IP冲突， PHY改变，socke状态改变）
	
	uint8_t   					socket0Status;					// socket0状态（UDP使用的socket）
	
	uint8_t   					socket1Status;					// socket1状态（广播包使用的socket）
		
	
	// 公共接口
	//
	ProcVoid_Void				run;							// 网络任务，需要周期性实时调用
	
	ProcVoid_Void				reboot;							// 重启以太网卡
	
	ProcVoid_Void				allParameters;					// 查询网络所有参数
	
	ProcVoidP_Void				registerErrorFunction;			// 注册错误回调函数（网络断开，服务器断开等等）
	
	
	// UDP
	//
	ProcVoid_Void				connectUdp;						// 启用UDPsocket服务
	
	ProcUint8PUint16_Void		writeUdp;						// 发送UDP数据
	
	ProcUint8P_Uint16			readUdp;						// 接收UDP或者广播数据
	
	
	// Boardcast
	//
	ProcVoid_Void				connectBoardcast;				// 启用广播socket服务
	
	ProcUint8PUint16_Void		writeBoardcast;					// 发送广播数据
	
	ProcUint8P_Uint16			readBoardcast;					// 接收广播数据
	
}Network;



void Network_Init(void *self);




#endif

