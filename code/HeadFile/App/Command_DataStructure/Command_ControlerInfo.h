#ifndef __COMMAND_CONTROLERINFO_H_
#define __COMMAND_CONTROLERINFO_H_

#include "APP_HAL_API.h"


typedef struct
{
	uint8_t StartScan:1;						// ��ʼɨ���־�� ��ʼ��ֵ0
	
	uint8_t HeartbeatNotAckTimes:3;				// ����û��Ӧ���������ʼ��ֵΪ0��������ѯʱ���㣬��������ʱ�������ﵽһ�������ص���ѯ��������Ӧ��ʱ����
	
	uint8_t Reserver:4;							// ����δ��ʹ��
		
	uint8_t FirstBootup;						// �״ο�����־λ�� 0x31��ʾ�״ο����� 0x32��ʾ���״ο���
	
	uint8_t HeartbeatInterval;					// �����������λ��1S
	
	uint8_t HeartbeatInterval_Bak;				// ����������ݣ���λ��1S
	
	uint8_t Version[3];							// �������汾��(���磺0x16, 0x12, 0x15)
	
	uint8_t Name[10];							// ����������()
	
	uint8_t Info[10];							// �����������ֶ�()
	
	uint8_t Password[6];						// ������������
	
}ControlerInfo_Typedef;


#define SetStartScan(val)						ControlerInfo.StartScan = val

#define IsStartScan()							ControlerInfo.StartScan

#define SetHeartbeatNotAckTimes(val)			ControlerInfo.HeartbeatNotAckTimes = val

#define SetFirstBootUp(val)						ControlerInfo.FirstBootup = val

#define SetHeartbeatInterval(val)				ControlerInfo.HeartbeatInterval = val? val:5

#define SetHeartbeatIntervalBak(val)			ControlerInfo.HeartbeatInterval_Bak = val? val:5

#define	RestoreHeartbeatInterval()				ControlerInfo.HeartbeatInterval = ControlerInfo.HeartbeatInterval_Bak		// �ָ��������(��������ʱ��Ϊ�˿�������������������������Ȼ������������ʱ���ٻָ�ԭ����ֵ)


extern	ControlerInfo_Typedef					ControlerInfo;


void ControlerInfo_ReadName(void);


void ControlerInfo_WriteName(void);


void ControlerInfo_ReadNetworkParameter(void);


void ControlerInfo_WriteNetworkParameter(void);
	

void ControlerInfo_Init(void);



#endif
