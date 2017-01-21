#include "Scheduler.h"


static	Scheduler *Scheduler_self;


// 定义延时时间
//
void Scheduler_Delay1ms(uint16_t millisecond)
{
	static uint32_t tmpStart;
	
	static uint32_t tmpNow;
	
	tmpStart = HAL_SYSTEMTIME();
	
	do
	{
		tmpNow = HAL_SYSTEMTIME();
		
	}while (HAL_DIFFERENT4_TIME(tmpNow, tmpStart) <= millisecond);
}


void Scheduler_RegisterTask(void *tasks, uint8_t taskEntries)
{
	uint8_t i;
	
	Scheduler_self->tasks = tasks;
	
	Scheduler_self->taskEntries = taskEntries;
	
	for (i = 0; i < Scheduler_self->taskEntries; i++)
	{
		Scheduler_self->tasks[i].__intervalTicks = 0;
		
		Scheduler_self->tasks[i].__maxLimitMilliseconds = 0;
	}
}


void Scheduler_Run(void)
{
	static uint8_t i;
	
	static uint16_t tickDt;
	
	static uint32_t maxLimitDt;
	
	for (i = 0; i < Scheduler_self->taskEntries; i++)
	{
		tickDt = HAL_DIFFERENT2_TIME(Scheduler_self->ticks, 
										  Scheduler_self->tasks[i].__intervalTicks);
		
		maxLimitDt = HAL_DIFFERENT4_TIME(Scheduler_self->milliseconds(), 
										 Scheduler_self->tasks[i].__maxLimitMilliseconds);
		
		if (tickDt >= Scheduler_self->tasks[i].intervalTicks ||
			maxLimitDt >= Scheduler_self->tasks[i].maxLimitMilliseconds)
		{
			if (Scheduler_self->tasks[i].function())
			{
				Scheduler_self->tasks[i].__intervalTicks = Scheduler_self->ticks;
			
				Scheduler_self->tasks[i].__maxLimitMilliseconds = Scheduler_self->milliseconds();
			}
		}
	}
}


void Scheduler_TicksIncrease(void)
{
	Scheduler_self->ticks++;
}


void Scheduler_Init(void *self)
{
	Scheduler_self = self;
	
	Scheduler_self->init = Scheduler_Init;
	
	Scheduler_self->run = Scheduler_Run;
	
	Scheduler_self->registerTask = Scheduler_RegisterTask;
	
	Scheduler_self->delayMilliseconds = Scheduler_Delay1ms;
	
	Scheduler_self->milliseconds = HAL_SYSTEMTIME;
	
	Scheduler_self->ticksIncrease = Scheduler_TicksIncrease;
	
	Scheduler_self->ticks = 0;
	
	Scheduler_self->taskEntries = 0;
}





