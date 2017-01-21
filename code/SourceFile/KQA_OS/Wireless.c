#include "Wireless.h"



static Wireless *Wireless_self;


void Wireless_ChangeChannel(uint8_t channelNo)
{
	Wireless_self->channelNo = channelNo;
	
	HAL_WIRELESS_INIT(channelNo);
}


void Wireless_Init(void *self)
{
	Wireless_self = self;
	
	Wireless_self->init = Wireless_Init;
	
	Wireless_self->changeChannel = Wireless_ChangeChannel;
	
	Wireless_self->avilable = HAL_WIRELESS_AVAILABE;
	
	Wireless_self->write = HAL_WIRELESS_SEND;
	
	Wireless_self->read = HAL_WIRELESS_RECEIVE;
	
	Wireless_self->changeChannel(0x00);
}





