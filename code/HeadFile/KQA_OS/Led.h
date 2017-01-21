#ifndef __LED_H_
#define __LED_H_


#include "OS_HAL.h"


enum
{
	GREEN_LED = 0x01,
	
	BLUE_LED = 0x02,
	
	YELLOW_LED = 0x04,
	
	ALL_LED = GREEN_LED | BLUE_LED | YELLOW_LED,
	
	LED_ON = 0,
	
	LED_OFF = 1,
	
	LED_SWITCH = 2,
};


typedef struct
{
	uint32_t					baseTime;						// �������Ŀ�ʼʱ��

	uint32_t					ledTime;						// ���������ã���λ�ɶ�ʱ��0����
	
}LedStatus;


#define 	LED_MAX				3


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;
	
	// �����ӿ�
	//
	ProcVoid_Void				run;							// LED����(��Ҫ�����Եص���)
	
	ProcUint8Uint16_Void		setTime;						// ������һ���������
	
	ProcUint8Uint8_Void			action;							// ���ƵƵ���Ϊ
	
	// ˽�нӿ�
	//
	LedStatus					ledStatus[LED_MAX];				// ��״̬
	
}Led;


void Led_Init(void *self);



#endif

