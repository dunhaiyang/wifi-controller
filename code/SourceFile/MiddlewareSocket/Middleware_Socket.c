#include "Middleware_Socket.h"





void MiddlewareSocket_NetworkError(void)
{
	SetStartScan(0);																			// ��ͣ��ѯ
	
	SetHeartbeatInterval(1);																	// �����������Ϊ1
}



// ����������������
//
void MiddlewareSocket_FastTask(void)
{
	static	uint8_t		MiddlewareSocket_Command[80];
	
	uint16_t 	MiddlewareSocket_CommandLen = 0;
	
	// ���û�����ݣ���ô�ʹӻ����ж�ȡ����
	//
#ifdef	USING_MODULE_WIFI
	MiddlewareSocket_CommandLen = App_Hal_Api.wifi->read(MiddlewareSocket_Command);
#endif
		
#ifdef	USING_MODULE_NETWORK
	MiddlewareSocket_CommandLen = App_Hal_Api.network->readUdp(MiddlewareSocket_Command);
#endif

	// ���ݲ�Ϊ�գ��ŵ����û��߲���Ҫ�ŵ���У��Ϸ�������ǰ��������������ִ��
	//
	if (MiddlewareSocket_CommandLen && 
	    (WiresslessChannel_Status == WirelessChannel_Free 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x65 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x69 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x6F 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x72 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x73))
	{
		if (PC_CheckCommand(MiddlewareSocket_Command, MiddlewareSocket_CommandLen))
		{
			App_Hal_Api.led->setTime(YELLOW_LED, 2);											// ���Ƶ�
			
			Network_DealControlData(MiddlewareSocket_Command);									// �������������
			
			HookFunction_ReceivePcData();														// PC��Ӧ��������ֹͣ��ѯ�豸��������յ�PC��������Ĭ�������������������������������Ӧ��������
		}
	}
	
}












