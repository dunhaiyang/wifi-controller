#include "Parameter.h"


static Parameter *Parameter_self;



void Parameter_Init(void *self)
{
	Parameter_self = self;
	
	Parameter_self->init = Parameter_Init;
	
	Parameter_self->read = HAL_PARAMETER_READBYTE;
	
	Parameter_self->write = HAL_PARAMETER_WRITEBYTE;	
	
	Parameter_self->erase = HAL_PARAMETER_ERASE;
}







