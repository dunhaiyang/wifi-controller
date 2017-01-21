#include "Middleware_Boardcast.h"


#ifdef	USING_MODULE_NETWORK


// ����������������
//
void MiddlewareBoardcast_FastTask(void)
{
	static	uint8_t		MiddlewareBoardcast_Command[80];
	
	uint16_t 	MiddlewareBoardcast_CommandLen = 0;
	
	// ��ȡ����
	//
	MiddlewareBoardcast_CommandLen = App_Hal_Api.network->readBoardcast(MiddlewareBoardcast_Command);

	// ���ݲ�Ϊ�գ��ŵ����û��߲���Ҫ�ŵ���У��Ϸ�������ǰ��������������ִ��
	//
	if (MiddlewareBoardcast_CommandLen &&
		(MiddlewareBoardcast_Command[Enum_CommandNo] == 0x61 || MiddlewareBoardcast_Command[Enum_CommandNo] == 0x63))
	{
		if (PC_CheckCommand(MiddlewareBoardcast_Command, MiddlewareBoardcast_CommandLen))
		{
			App_Hal_Api.led->setTime(YELLOW_LED, 2);											// ���Ƶ�
			
			Network_DealControlData(MiddlewareBoardcast_Command);								// �������������
		}
	}
	
}



#endif








