#include "Hardware.h"


static Hardware *Hardware_self;


void Hardware_Init(void *self)
{
	Hardware_self = self;
	
	Hardware_self->init = Hardware_Init;	
	
	Hardware_self->reboot = HAL_REBOOT;
	
	Hardware_self->feedWatchdog = HAL_WATCHDOG;
	
	// Ӳ����ʼ��
	//
	HAL_HARDWARE_INIT();
	
	// ϵͳʱ�ӵδ��ʼ��
	//
	HAL_SYSTEMTIME_INIT();
}





