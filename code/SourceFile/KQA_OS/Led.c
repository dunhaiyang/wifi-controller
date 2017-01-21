#include "Led.h"


static Led *Led_self;


void Led_SetTime(uint8_t whichLed, uint16_t t)
{
	static uint8_t	tmpWhichLed;						
	
	static uint16_t	tmpT;								
	
	static uint8_t	index;
	
	static uint8_t  whichLedFlag;
	
	tmpWhichLed = whichLed;								// 间接调用，需要保存局部变量
	
	tmpT = t;											// 间接调用，需要保存局部变量
	
	for (index = 0; index < LED_MAX; index++)
	{
		whichLedFlag = tmpWhichLed & (0x01 << index);
		
		if (whichLedFlag)
		{
			Led_self->ledStatus[index].baseTime = HAL_SYSTEMTIME();
		
			Led_self->ledStatus[index].ledTime = tmpT;
			
			Led_self->action(whichLedFlag, LED_ON);
		}
	}
}


void Led_Run(void)
{
	static uint8_t	index;
	
	static uint32_t nowTime;
	
	for (index = 0; index < LED_MAX; index++)
	{
		nowTime = HAL_SYSTEMTIME();
		
		if (Led_self->ledStatus[index].ledTime &&
			HAL_DIFFERENT4_TIME(nowTime, Led_self->ledStatus[index].baseTime) > Led_self->ledStatus[index].ledTime)
		{
			Led_self->ledStatus[index].ledTime = 0;
			
			Led_self->action(0x01 << index, LED_OFF);
		}
	}
}


void Led_Action(uint8_t whichLed, uint8_t whatAction)
{
	switch (whichLed)
	{
		case GREEN_LED:
			HAL_LED_GREEN(whatAction);
			break;
		
		case BLUE_LED:
			HAL_LED_BLUE(whatAction);
			break;
		
		case YELLOW_LED:
			HAL_LED_YELLOW(whatAction);
			break;
		
		case ALL_LED:
			HAL_LED_GREEN(whatAction);
			HAL_LED_BLUE(whatAction);
			HAL_LED_YELLOW(whatAction);
			break;
		
		default:
			break;
	}
}


void Led_Init(void *self)
{
	Led_self = self;
	
	Led_self->init = Led_Init;
	
	Led_self->run = Led_Run;
	
	Led_self->setTime = Led_SetTime;
	
	Led_self->action = Led_Action;
}







