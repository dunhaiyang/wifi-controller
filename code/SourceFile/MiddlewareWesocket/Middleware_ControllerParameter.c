#include "Middleware_ControllerParameter.h"


bool ControllerParameter_DealFrameText(uint8_t **Data)
{
	uint8_t tmpWirelessChannel;
	
	uint8_t tmpHeartbeatInterval;
	
	if (!Json_ReceiveFrameCharValue(Data, "nwc\":\"", 6, &tmpWirelessChannel))
	{
		return 0;
	}
	
	if (!Json_ReceiveFrameCharValue(Data, "nhi\":\"", 6, &tmpHeartbeatInterval))
	{
		return 0;
	}
	
	// �޸������ŵ�
	//
	PWR_UP = 0; PWR_UP = 0;
	
//	WirelessChannel = tmpWirelessChannel;
	
//	NRF905_SetWireLess(); os_send_signal(THREAD_BEEP);
	
	// �޸��������
	//
//	ControlerInfo_Set_HeartbeatIntervalReload(tmpHeartbeatInterval);
	
	//�������ݲɼ�����
	//
	
	// �����ɼ���ʼʱ��
	//
	
	// �����ɼ�ʱ����
	//
	
	return 1;
}




