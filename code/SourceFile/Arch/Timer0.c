#include "Timer0.h"


uint32_t	__SystemTicks = 0;


// 1ms interrupt
//
void Timer0_Init(void)
{
	AUXR &= 0x7F;		// ��ʱ��ʱ��12Tģʽ
	
	TMOD &= 0xF0;		// ���ö�ʱ��ģʽ
	
	TL0 = 0xCD;			// ���ö�ʱ��ֵ
	
	TH0 = 0xF8;			// ���ö�ʱ��ֵ
	
	TF0 = 0;			// ���TF0��־
	
	TR0 = 1;			// ��ʱ��0��ʼ��ʱ
	
//	PT0 = 1;			// ���ʱ�����ȼ�
	
	ET0 = 1;			// ����ʱ��0�ж�
}


void Timer0_Interrupt(void) interrupt 1
{
	__SystemTicks++;
}


uint32_t Timer0_SystemTicks(void)
{
	return __SystemTicks;
}













