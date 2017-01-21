#ifndef __HARDWARE_H_
#define __HARDWARE_H_




#include "OS_HAL.h"


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void		init;
	
	// �����ӿ�
	//
	ProcVoid_Void		reboot;								/// ����
	
	ProcVoid_Void		feedWatchdog;						/// ι��
	
}Hardware;


void Hardware_Init(void *self);



#endif

