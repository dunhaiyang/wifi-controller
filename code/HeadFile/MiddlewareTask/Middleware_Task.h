#ifndef __MIDDLEWARE_TASK_H_
#define __MIDDLEWARE_TASK_H_


#include "Command_Wireless.h"

#include "Command_Network.h"


// ��ѯ����
//
bool PollDeviceTask(void);


// α�ն�����
//
bool ConsoleRunTask(void);


// ����������
//
bool PeriodTask(void);


extern	Task	task[3];
















#endif


