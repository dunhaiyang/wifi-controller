#ifndef __Wireless_H_
#define __Wireless_H_


#include "OS_HAL.h"


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void			init;
	
	// �����ӿ�
	//
	uint8_t					channelNo;						// ��ȡ�����ŵ���
	
	// �����ӿ�
	
	ProcUint8_Void			changeChannel;					// �ı������ŵ�
	
	ProcVoid_Bool			avilable;						// �����ݿɶ�
	
	ProcUint8P_Void			write;							// ��������
	
	ProcUint8P_Void			read;							// ��������
	
}Wireless;


void Wireless_Init(void *self);




#endif

