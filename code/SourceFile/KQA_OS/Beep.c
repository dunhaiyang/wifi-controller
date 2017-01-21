#include "Beep.h"


static Beep *Beep_self;


uint32_t Beep_BaseTime = 0;				// �������Ŀ�ʼʱ��


uint32_t Beep_Time = 0;					// ���������ã���λ�ɶ�ʱ��0����


void Beep_SetTime(uint32_t t)
{
	Beep_Time = t;
	
	Beep_BaseTime = HAL_SYSTEMTIME();
	
	Beep_self->action(BEEP_ON);
}


void Beep_Run(void)
{
	static uint32_t nowTime;
	
	nowTime = HAL_SYSTEMTIME();
	
	if (Beep_Time &&
		HAL_DIFFERENT4_TIME(nowTime, Beep_BaseTime) > Beep_Time)
	{
		Beep_Time = 0;
		
		Beep_self->action(BEEP_OFF);
	}
}


void Beep_Init(void *self)
{
	Beep_self = self;
	
	Beep_self->init = Beep_Init;
	
	Beep_self->run = Beep_Run;
	
	Beep_self->setTime = Beep_SetTime;
	
	Beep_self->action = HAL_BEEP_ACTION; 
}












