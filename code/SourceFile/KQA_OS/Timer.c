#include "Timer.h"


static	xdata Timer *Timer_self;


void Timer_Init(void *self)
{
	Timer_self = self;
	
	
	
	printf("Timer_Init\r\n");
}







