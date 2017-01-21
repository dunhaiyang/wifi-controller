#ifndef __APP_HAL_API_H_
#define __APP_HAL_API_H_


#include "APP_HAL.h"


// IAP15��������оƬ���ܺ����蹦�ܵĳ����
//
typedef struct
{
	// ���нӿ�
	//
	ProcVoid_Void		init;					// ��ʼ������������һ��ʼ��Ҫ���ã����ڳ�ʼ������ϵͳ�ײ㣩
	
	// ���г�Ա����
	//
	Hardware			*hardware;				// Ӳ��ģ��
	
	Led					*led;					// ��ģ��
	
	Beep				*beep;					// ������ģ��
	
	Console				*console;				// α�ն�ģ��
	
	Parameter			*parameter;				// ����ģ��
	
	Wireless			*wireless;				// ����ģ��(NF905)

#ifdef	USING_MODULE_WIFI
	Wifi				*wifi;					// WIFIģ��(TI��˾)
#endif

#ifdef	USING_MODULE_NETWORK
	Network				*network;				// ����ģ��(�Բ�CH395)
#endif
	
	Scheduler			*scheduler; 			// ������ģ��
	
}APP_HAL_API;


extern	APP_HAL_API		App_Hal_Api;


#endif


