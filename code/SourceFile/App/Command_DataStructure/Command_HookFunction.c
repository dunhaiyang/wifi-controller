#include "Command_HookFunction.h"


// =====================  �߳���صĹ��Ӻ���  ============================
//
// ����PC���ݵĹ��Ӻ���
//
void HookFunction_ReceivePcData(void)
{
	// ���������Ӧ�������ԭ���ǿ���PC�����շ������Ƚ��أ������ش���������
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
}


// =====================  ������ָ����صĹ��Ӻ���  ============================
//
// ������صĹ��Ӻ���
//
void HookFunction_HeartbeatReq(void)
{
	// ʵ��N��û������Ӧ����ô�Ͷ϶��������͵���ͨѶ�Ѷϣ���ô��ֹͣ��ѯ
	//
	if (ControlerInfo.HeartbeatNotAckTimes > 3)
	{
		SetStartScan(0);						// ֹͣ��ѯ
	}
		
	// �����������Ӧ�����
	else
	{
		ControlerInfo.HeartbeatNotAckTimes++;
	}
}

void HookFunction_HeartbeatAck(void)
{
	// ������Ӧ���������
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
	
	// �ָ�ԭʼ�������
	//
	RestoreHeartbeatInterval();
	
	// �״ο�����־���
	//
	ControlerInfo.FirstBootup = 0x32;
}


// ����ģʽ�Ĺ��Ӻ���
//
void HookFunction_ControlerWorkMode(void)
{
	// ������Ӧ���������
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
}


// ====================  �м���ָ����صĹ��Ӻ���  =============================
// 



// ====================  �豸ָ����صĹ��Ӻ���  ===============================
//








