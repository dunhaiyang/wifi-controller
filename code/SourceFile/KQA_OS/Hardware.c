#include "Hardware.h"


static Hardware *Hardware_self;


void Hardware_Init(void *self)
{
	Hardware_self = self;
	
	Hardware_self->init = Hardware_Init;	
	
	Hardware_self->reboot = HAL_REBOOT;
	
	Hardware_self->feedWatchdog = HAL_WATCHDOG;
	
	// 硬件初始化
	//
	HAL_HARDWARE_INIT();
	
	// 系统时钟滴答初始化
	//
	HAL_SYSTEMTIME_INIT();
}





