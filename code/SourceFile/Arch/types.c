#include "types.h"


Time_TypeDef SysTime = {16, 12, 9, 5, 18, 14, 0};


void InitLed(void)
{
	P3M0 &= ~0x3B; P3M1 &= ~0x3B;
}


void LedGreen(uint8_t action)
{
	if (action == 2)
		COM_GREEN = ~COM_GREEN;
	else
		COM_GREEN = action;
}


void LedBlue(uint8_t action)
{
	if (action == 2)
		WLS_BLUE = ~WLS_BLUE;
	else
		WLS_BLUE = action;
}


void LedYellow(uint8_t action)
{
	if (action == 2)
		PWR_YELLOW = ~PWR_YELLOW;
	else
		PWR_YELLOW = action;
}


void InitBeep(void)
{
	P3M0 &= ~0x20; P3M1 &= ~0x20;
}


void BeepAction(uint8_t action)
{
	PP = action;
}

void ClearWatchdog(void)
{
	WDT_CONTR = 0x3E;						// PS2, PS1, PS0: 1, 0, 0(1.25S), 1, 1, 0(2.5S), 1, 1, 1(5S)
}


void Reboot(void)
{
	IAP_CONTR |= 0x60;
}


void Delay1us(void)							//@22.1184MHz
{
	unsigned char xdata i;

	i = 3;
	
	while (--i);
}


void  Delay1ms(uint16_t ms)					//@22.1184MHz
{
	static uint8_t i;
	static uint8_t j;
	
  	while (ms--)
    {
        _nop_();
		_nop_();
		i = 22;
		j = 128;
		do
		{
			while (--j);
		} while (--i);
    }
}


