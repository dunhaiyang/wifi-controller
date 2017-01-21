#include "Middleware_Wireless.h"




// ����������������
//
void MiddlewareWireless_FastTask(void)
{
	static uint8_t ReceiveWireless_Command[32];
	
	if(App_Hal_Api.wireless->avilable())                                           				// �Ƿ�����������
	{
		App_Hal_Api.wireless->read(ReceiveWireless_Command);									// ������������
		
		if (Wireless_CheckCommand(ReceiveWireless_Command))                        				// ����������ݺϷ���
		{
			Pca_Stop();																			// �ͷ������ŵ�
			
			App_Hal_Api.led->setTime(BLUE_LED, 2);												// ���̵�
			
			Wireless_DealControlData(ReceiveWireless_Command);									// ������������
		}
	}
}




