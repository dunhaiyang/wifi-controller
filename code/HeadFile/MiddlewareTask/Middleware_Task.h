#ifndef __MIDDLEWARE_TASK_H_
#define __MIDDLEWARE_TASK_H_


#include "Command_Wireless.h"

#include "Command_Network.h"


// 轮询任务
//
bool PollDeviceTask(void);


// 伪终端任务
//
bool ConsoleRunTask(void);


// 周期性任务
//
bool PeriodTask(void);


extern	Task	task[3];
















#endif


