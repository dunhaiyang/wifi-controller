#ifndef __COMMAND_ONECARDOPERATION_H
#define __COMMAND_ONECARDOPERATION_H



#include "Pc.h"
#include "Command_Temporary.h"



//extern uint8_t OneCardOperation_NeedResend;


void OneCardOperation_DealData(uint8_t *Data);


void OneCardOperation_SendDataToPC(uint8_t *Data);


//void OneCardOperation_NoReceiveDataFromDevice(void);






#endif

