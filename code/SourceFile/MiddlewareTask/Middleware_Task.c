#include "Middleware_Task.h"



// ��ѯ����
//
bool PollDeviceTask(void)
{
	if (IsStartScan() &&
		(WiresslessChannel_Status == WirelessChannel_Free))  									// ������ѯ�������ŵ����У���ô����ѯ
	{
		if (DevicePool_SendDataToDevice())
		{
			App_Hal_Api.led->setTime(GREEN_LED, 2);												// ���̵�
			
//			printf("111\r\n");
			
			return 1;
		}
	}
	return 0;
}


// α�ն�����
//
bool ConsoleRunTask(void)
{
	App_Hal_Api.console->run();
	
	return 1;
}


// ����������
//
bool PeriodTask(void)
{
//	App_Hal_Api.hardware->feedWatchdog();
		
	if (0 == --ControlerInfo.HeartbeatInterval)
	{
		RestoreHeartbeatInterval();																// ������ʱ����
		
		Heartbeat_SendDataToPC();																// ����������
		
//		App_Hal_Api.wireless->changeChannel(0x07);
		
		App_Hal_Api.led->setTime(YELLOW_LED, 2);												// ���̵�
	}
		
	return 1;
}


/*
	������ȱ� - ������ʽ����������fast_loop�У���Ӧ����������
	��һ����Ա������������
	�ڶ�����Ա���������������õ�Ƶ�ʣ���λ�ǣ�5ms��
	��������Ա��������������Ҫ������ӳ�ִ��ʱ�䣬��λ�ǣ�1ms��
*/
Task	task[3] = {
	
	// ��ѯ���� (5msһ�Σ����ִ���ӳٲ�Ҫ����5ms)
	//
	{PollDeviceTask,		6,		40},
	
	// α�ն����� (30msһ�Σ����ִ���ӳٲ�Ҫ����50ms)
	//
	{ConsoleRunTask,		6,		40},
	
	// ����������1000msһ�Σ����ִ���ӳٲ�Ҫ����1200ms��
	//
	{PeriodTask,			200,	1200},
};












