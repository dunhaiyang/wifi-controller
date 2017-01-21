#include "Timer0.h"


uint32_t	__SystemTicks = 0;


// 1ms interrupt
//
void Timer0_Init(void)
{
	AUXR &= 0x7F;		// 定时器时钟12T模式
	
	TMOD &= 0xF0;		// 设置定时器模式
	
	TL0 = 0xCD;			// 设置定时初值
	
	TH0 = 0xF8;			// 设置定时初值
	
	TF0 = 0;			// 清除TF0标志
	
	TR0 = 1;			// 定时器0开始计时
	
//	PT0 = 1;			// 提高时钟优先级
	
	ET0 = 1;			// 允许定时器0中断
}


void Timer0_Interrupt(void) interrupt 1
{
	__SystemTicks++;
}


uint32_t Timer0_SystemTicks(void)
{
	return __SystemTicks;
}













