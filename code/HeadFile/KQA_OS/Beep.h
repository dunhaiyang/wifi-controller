#ifndef __BEEP_H_
#define __BEEP_H_


#include "OS_HAL.h"


enum
{
	BEEP_ON = 0,
	
	BEEP_OFF = 1,
};


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void			init;

	// �����ӿ�
	//
	ProcVoid_Void			run;								// BEEP����(��Ҫ�����Եص���)
	
	ProcUint32_Void			setTime;							// ���÷���������
	
	ProcUint8_Void			action;								// ���Ʒ���������Ϊ
	
}Beep;


void Beep_Init(void *self);






#endif


