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
	uint16_t	receiveOk:1;					// �����Ѿ�����������
	
	uint16_t 	receiveBufferCount:15;			// ���ջ������ݴ�С
	
	uint8_t		__receiveBuffer[120];			// �ڲ����ջ�������û��ȥ��֡�ṹ�����ݣ�

	uint8_t		receiveBuffer[60];				// �ⲿ���ջ�������ȥ��֡�ṹ�����ݣ�
	
	uint8_t		__sendBuffer[120];				// �ڲ����ͻ�����������֡�ṹ�����ݣ�
	
	uint8_t		sendBuffer[80];					// �ⲿ���ͻ�������û�м���֡�ṹ�����ݣ�
	
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
	uint16_t	receiveOk:1;					// �����Ѿ�����������
	
	uint16_t 	receiveBufferCount:15;			// ���ջ������ݴ�С
	
	uint8_t		__receiveBuffer[120];			// �ڲ����ջ�������û��ȥ��֡�ṹ�����ݣ�

	uint8_t		receiveBuffer[80];				// �ⲿ���ջ�������ȥ��֡�ṹ�����ݣ�
	
	uint8_t		__sendBuffer[255];				// �ڲ����ͻ�����������֡�ṹ�����ݣ�
	
	uint8_t		sendBuffer[200];				// �ⲿ���ͻ�������û�м���֡�ṹ�����ݣ�
	
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
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;	

	ProcVoid_Void				error;
	
	
	// ˽�����ݣ����ڵ��ԣ�
	//
	uint16_t  					globalStatus;					// ȫ��״̬�����ɴIP��ͻ�� PHY�ı䣬socke״̬�ı䣩
	
	uint8_t   					socket0Status;					// socket0״̬��UDPʹ�õ�socket��
	
	uint8_t   					socket1Status;					// socket1״̬���㲥��ʹ�õ�socket��
		
	
	// �����ӿ�
	//
	ProcVoid_Void				run;							// ����������Ҫ������ʵʱ����
	
	ProcVoid_Void				reboot;							// ������̫����
	
	ProcVoid_Void				allParameters;					// ��ѯ�������в���
	
	ProcVoidP_Void				registerErrorFunction;			// ע�����ص�����������Ͽ����������Ͽ��ȵȣ�
	
	
	// UDP
	//
	ProcVoid_Void				connectUdp;						// ����UDPsocket����
	
	ProcUint8PUint16_Void		writeUdp;						// ����UDP����
	
	ProcUint8P_Uint16			readUdp;						// ����UDP���߹㲥����
	
	
	// Boardcast
	//
	ProcVoid_Void				connectBoardcast;				// ���ù㲥socket����
	
	ProcUint8PUint16_Void		writeBoardcast;					// ���͹㲥����
	
	ProcUint8P_Uint16			readBoardcast;					// ���չ㲥����
	
}Network;



void Network_Init(void *self);




#endif

