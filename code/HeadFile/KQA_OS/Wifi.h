#ifndef __WIFI_H_
#define __WIFI_H_



#include "OS_HAL.h"


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;
	
	// �����ӿ�
	//
	// ����wifi���ԣ���Щ���Ի�̻���wifi�У� ��һ�ξͲ���Ҫ�����ˣ�
	//
	ProcVoid_Void				getUart;					// wifi ��ȡ���ڲ�������Ϣ
	
	ProcVoidP_Void				linkAP;						// wifi ����apվ��
	
	ProcVoid_Void				queryMac;					// wifi ��ѯMAC��ַ
	
	ProcVoid_Void				reboot;						// wifi ����
	
	ProcVoid_Void				scan;						// wifi ɨ��
	
	ProcVoid_Void				hotspotStatus;				// wifi �ȵ�����״̬
	
	ProcVoid_Void				serverStatus;				// wifi ����������״̬
	
	ProcVoid_Void				dhcp;						// wifi �鿴DHCP�����ip���������Ϣ
	
	ProcUint8P_Void				ping;						// wifi ping
	
	ProcVoidP_Void				connectServer;				// wifi ����Զ�̷�����
	
	ProcVoid_Void				disconnectServer;			// wifi �Ͽ�����Զ�̷�����
	
	// ��������
	//
	ProcVoidPUint8_Void			write;						// wifi ��������
	
	ProcUint8P_Uint16			read;					// wifi ��������
	
}Wifi;


void Wifi_Init(void *self);



#endif

