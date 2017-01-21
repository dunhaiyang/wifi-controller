#include "APP_HAL_API.h"


// ����ģ�����ע���ʼ������
//
STATIC_DRIVER_INIT(Hardware, hardware);											// Ӳ��ģ�鶨��


STATIC_DRIVER_INIT(Led, led);													// ��ģ�鶨��


STATIC_DRIVER_INIT(Beep, beep);													// ������ģ�鶨��


STATIC_DRIVER_INIT(Console, console);											// α�ն�ģ�鶨��


STATIC_DRIVER_INIT(Parameter, parameter);										// ����ģ�鶨��


STATIC_DRIVER_INIT(Wireless, wireless);											// ����ģ�鶨��


#ifdef	USING_MODULE_WIFI
STATIC_DRIVER_INIT(Wifi, wifi);													// WIFIģ�鶨��
#endif


#ifdef	USING_MODULE_NETWORK
STATIC_DRIVER_INIT(Network, network);											// ����ģ�鶨��
#endif


STATIC_DRIVER_INIT(Scheduler, scheduler);										// ������ģ�鶨��


// ��ʼ��ģ�鲢��ע���ģ������������Ա����
//
void App_Hal_Init(void)
{
	// ============================  Ӳ��ģ��  ===============================
	//
	App_Hal_Api.hardware->init(App_Hal_Api.hardware);						
	
	
	// ============================  ��ģ��  =================================
	//
	App_Hal_Api.led->init(App_Hal_Api.led);									
	
	
	// ===========================  ������ģ��  ==============================
	//
	App_Hal_Api.beep->init(App_Hal_Api.beep);
	
	
	// ===========================  α�ն�ģ��  ==============================
	//
	App_Hal_Api.console->init(App_Hal_Api.console);
	
	
	// ===========================  ����ģ��  ==============================
	//
	App_Hal_Api.parameter->init(App_Hal_Api.parameter);
	
	
	// ============================  ����ģ��  ===============================
	//
	App_Hal_Api.wireless->init(App_Hal_Api.wireless);
	
	
	// ============================  WIFIģ��  ================================
	//
#ifdef	USING_MODULE_WIFI

	App_Hal_Api.wifi->init(App_Hal_Api.wifi);

#endif
	
	
	// ============================  ����ģ��  ================================
	//
#ifdef	USING_MODULE_NETWORK

	App_Hal_Api.network->init(App_Hal_Api.network);
	
#endif

	
	// ===========================  ������ģ��  ===============================
	//
	App_Hal_Api.scheduler->init(App_Hal_Api.scheduler);
}


// IPA15���󣨳�ʼ����
//
APP_HAL_API		App_Hal_Api = {		App_Hal_Init, 
	
									&hardware, 
	
									&led, 
	
									&beep, 
	
									&console, 
		
									&parameter, 
	
									&wireless, 

#ifdef	USING_MODULE_WIFI
									&wifi, 
#endif
	
#ifdef	USING_MODULE_NETWORK
									&network, 
#endif
	
									&scheduler
};






