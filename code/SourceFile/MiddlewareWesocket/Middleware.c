#include "Middleware.h"


Middleware_Typedef MiddlewareInfo;


uint8_t  	__Middleware_Send_ReceiveBuffer[601];


uint16_t   	__Middleware_Send_ReceiveBufferLen;


uint8_t code  __Middleware_WordArray[] = "0123456789abcdef";


void __Middleware_FastAck(void)
{
//	uint8_t		sendBufferLen = 0;
//	
//	// websocketǰ׺
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x81;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x80;		// ��Ҫ����
//	
//	// ����
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	// �豸��ź��豸���к�
//	//
//	memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "{\"cn\":\"", 7); sendBufferLen += 7;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckCmdNo / 100 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckCmdNo /10 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckCmdNo % 10 + '0';
//	
//	memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "\",\"csn\":\"", 9); sendBufferLen += 9;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckSerialNo / 10000 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckSerialNo /1000 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckSerialNo /100 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckSerialNo /10 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = Middleware_Get_FastAckSerialNo % 10 + '0';
//	
//	// ָ��ִ�н��
//	//
//	if (Middleware_GetError_FastAck())
//	{
//		memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "\",\"result\":false}", 17); sendBufferLen += 17;
//		
//		Middleware_ClearError_FastAck();
//	}
//	else
//	{
//		memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "\",\"result\":true}", 16); sendBufferLen += 16;
//	}
//	
//	// ���ø��س���
//	//
//	__Middleware_Send_ReceiveBuffer[1] |= sendBufferLen - 6;		// ���ز���������
//	
//	Ch395_Write(peerSockfd, __Middleware_Send_ReceiveBuffer, sendBufferLen);
}


void __Middleware_SendPollDataToPC(void)
{
//	uint16_t	sendBufferLen = 0;
//	
//	uint8_t		*tmpData = 0;
//	
//	uint8_t		i;
//	
//	// websocketǰ׺
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x81;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0xFE;
//	
//	// ����
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	// ��������
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	
//	// �豸��ź��豸���к�
//	//
//	memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "{\"cn\":\"007\",\"csn\":\"", 19); sendBufferLen += 19;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = DeviceInfo_DeviceDataSerialNo /10000 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = DeviceInfo_DeviceDataSerialNo /1000 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = DeviceInfo_DeviceDataSerialNo /100 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = DeviceInfo_DeviceDataSerialNo /10 % 10 + '0';
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = DeviceInfo_DeviceDataSerialNo % 10 + '0';
//	
//	DeviceInfo_DeviceDataSerialNo++;
//	
//	// ׼��װ������
//	//
//	memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "\",\"ds\":[", 8); sendBufferLen += 8;
//	
//	// װ������
//	//
//	while (tmpData = MiddlewareData_Fetch(MiddlewareData_PollData))
//	{
//		memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "{\"dc\":\"", 7); sendBufferLen += 7;
//		
//		for (i = 0; i < 32; ++i)
//		{
//			__Middleware_Send_ReceiveBuffer[sendBufferLen++] = __Middleware_WordArray[tmpData[i] >> 4];
//			
//			__Middleware_Send_ReceiveBuffer[sendBufferLen++] = __Middleware_WordArray[tmpData[i] & 0x0F];
//		}
//		__Middleware_Send_ReceiveBuffer[sendBufferLen++] = '\"';
//		__Middleware_Send_ReceiveBuffer[sendBufferLen++] = '}';
//		__Middleware_Send_ReceiveBuffer[sendBufferLen++] = ',';
//		
//		MiddlewareData_Free(MiddlewareData_PollData); OneCardDataUpload_SerialQuality++;	// ͳ�Ƶ�������ɾ������ָ����ʹ��
//	}
//	// ȥ������
//	//
//	--sendBufferLen;
//	
//	// ����ʣ���ַ�
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = ']';
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = '}';
//	
//	// ����
//	//
//	__Middleware_Send_ReceiveBuffer[2] = (sendBufferLen - 8) >> 8;
//	
//	__Middleware_Send_ReceiveBuffer[3] = (sendBufferLen - 8);
//	
//	// ��ʽ��������
//	//
//	Ch395_Write(peerSockfd, __Middleware_Send_ReceiveBuffer, sendBufferLen);
}


void __SendUrgencyDataToPC(void)
{
	switch (Middleware_Get_SlowAckCmdNo)
	{
		case 10:			// �����豸����
			DeviceUniversalCommand_SendFrameTextToPc(Middleware_Get_SlowAckSerialNo,
													__Middleware_Send_ReceiveBuffer);
			printf("DeviceUniversalCommand_SendFrameTextToPc\r\n");
			break;
		
		default:
			break;
	}
}


void __SendNormalDataToPC(void)
{
	switch (Middleware_Get_SlowAckCmdNo)
	{
		case 8:				// �����豸����
			DeviceParameter_SendFrameTextToPc(Middleware_Get_SlowAckSerialNo,
											  __Middleware_Send_ReceiveBuffer);
			printf("DeviceParameter_SendFrameTextToPc\r\n");
			break;
		
		case 11:			// ��ʼ������ӣ�ɾ�������°�����
			DeviceWhiteList_SendFrameTextToPc(Middleware_Get_SlowAckSerialNo,
											  __Middleware_Send_ReceiveBuffer);
			printf("DeviceWhiteList_SendFrameTextToPc\r\n");
			break;
		
		default:
			break;
	}
}


void Middleware_Init(void)
{
	Middleware_Clear_Shakehand();				// ������ֱ��
	
	Middleware_Clear_FastAck();					// ��տ��ٻذ����
	
	Middleware_ClearError_FastAck();			// ��տ��ٻذ��д�����
	
	MiddlewareData_Init();						// ��ʼ����̬�����ڴ�
}


// ֹͣ��ѯ����������Ϊδ��ɣ��Զ�����
//
void Middleware_DealAbort(void)
{
//	PC_DisconnectToPc();
//			
//	Middleware_Init();
//	
//	PC_ConnectToPc();
}


// ���û�гɹ����֣���ô�ͷ������ְ�
//
void Middleware_SendShakehand(void)
{
	// ��װ���ְ�
	//
//	Websocket_SendShakehand(peerAddr.ip, peerAddr.port, 
//					__Middleware_Send_ReceiveBuffer, 
//					&__Middleware_Send_ReceiveBufferLen);
//	
//	// �������ְ�
//	//
//	Ch395_Write(peerSockfd, 
//			__Middleware_Send_ReceiveBuffer, 
//			__Middleware_Send_ReceiveBufferLen);
}


// ���������������߼�
//
void Middleware_SendDataToPC(void)
{
//	static uint8_t  pollDataUpload = 0;
//	
//	// ����Ƿ��Ϳ���Ӧ��������������յ���������ָ����߷�������ָ���Ѿ��ɹ����գ�
//	//
//	if (Middleware_Get_FastAck())
//	{
//		PWR_YELLOW = LED_ON;
//		
//		Middleware_Clear_FastAck();
//		
//		__Middleware_FastAck();
//		
//		PWR_YELLOW = LED_OFF;
//	}
//	
//	// OneCardDataUpload_PollDeviceStatus == 2��ʾ��ȡ�ѻ��������
//	// ++pollDataUpload > 10 && OneCardDataUpload_PollDeviceStatus == 0��ʾ������ʵʱ����
//	//
//	if (OneCardDataUpload_PollDeviceStatus == 2 || 
//		(++pollDataUpload > 10 && OneCardDataUpload_PollDeviceStatus == 0))
//	{
//		pollDataUpload = 0;
//		
//		// ����ѯ������Ҫ�ϱ���������
//		//
//		if (!MiddlewareData_IsEmpty(MiddlewareData_PollData))
//		{
//			PWR_YELLOW = LED_ON;
//			
//			__Middleware_SendPollDataToPC();
//			
//			OneCardDataUpload_PollDeviceStatus = 3;
//			
//			OneCardDataUpload_RecoverCount = OneCardDataUpload_RecoverCount_Init;
//			
//			printf("upload\r\n");
//			
//			PWR_YELLOW = LED_OFF;
//		}
//		// û����ѯ������Ҫ�ϱ���������
//		//
//		else
//		{
//			OneCardDataUpload_PollDeviceStatus = 0;
//		}
//	}
//	
//	// ����ָ��ִ�е�Ӧ���
//	//
//	if (MiddlewareData_IsEmpty(MiddlewareData_SendDataUrgency) &&
//		!MiddlewareData_IsEmpty(MiddlewareData_ReceiveDataUrgency))
//	{
//		PWR_YELLOW = LED_ON;
//		
//		__SendUrgencyDataToPC();
//		
//		PWR_YELLOW = LED_OFF;
//	}
//	// ��ָͨ��ִ�е�Ӧ���
//	//
//	else if (MiddlewareData_IsEmpty(MiddlewareData_SendDataNormal) &&
//			 !MiddlewareData_IsEmpty(MiddlewareData_ReceiveDataNormal))
//	{
//		PWR_YELLOW = LED_ON;
//		
//		__SendNormalDataToPC();
//		
//		PWR_YELLOW = LED_OFF;
//	}
//	// ����Ƿ���Ҫ������������
//	//
//	else if (ControlerInfo_Get_HeartbeatSignal())
//	{
//		PWR_YELLOW = LED_ON;
//		
//		ControlerInfo_Clear_HeartbeatSignal();
//		
//		ControllerHeartbeat_SendFrameTextToPc(__Middleware_Send_ReceiveBuffer);
//		
//		PWR_YELLOW = LED_OFF;
//	}
}


// ����������������߼�
//
void Middleware_ReceiveDataFromPC(void)
{
	// ���û�л�ȡ�����������ݣ���ô����������
	//
//	if ((__Middleware_Send_ReceiveBufferLen = Ch395_Read(peerSockfd, 
//													__Middleware_Send_ReceiveBuffer, 1000)) == 0)
//	{
//		return;
//	}
//	
//	printf("fuqiyang\r\n");
//	
//	// �绹û������֣���ô�������ְ�
//	//
//	if (!Middleware_Get_Shakehand())
//	{
//		if (Websocket_ReceiveShakehand(__Middleware_Send_ReceiveBuffer,
//									__Middleware_Send_ReceiveBufferLen))
//		{	
//			Middleware_Set_Shakehand();
//		}
//	}
//	// �Ѿ�������֣� ��ô�������ݰ�
//	//
//	else
//	{
//		uint8_t *tmpAnalyse;						// �������ָ���ַ������ڴ����λ�ã� ����ÿ�ζ���ͷ����
//		
//		PWR_YELLOW = LED_ON;							// ���Ƶƣ� ������Ƶ�
//		
//		// ȥ��websocket��֡ͷ�� �������Ϸ���websocket���ݣ� ����0
//		//
//		if (Websocket_ReceiveFrameText(__Middleware_Send_ReceiveBuffer, 
//								__Middleware_Send_ReceiveBufferLen,
//								&tmpAnalyse) == 0)
//		{
//			PWR_YELLOW = LED_OFF;
//			
//			return;
//		}
//		
//		// ��ĩβ���һ��α�㣬�Ա�����ַ�������
//		//
//		__Middleware_Send_ReceiveBuffer[__Middleware_Send_ReceiveBufferLen] = 0;
//		
//		// ����ָ���
//		//
//		if (!Json_ReceiveFrameCharValue(&tmpAnalyse, "cn\":\"", 5, &Middleware_Get_FastAckCmdNo))
//		{
//			PWR_YELLOW = LED_OFF;
//			
//			return;
//		}
//		
//		// ����ָ����ˮ��
//		//
//		if (!Json_ReceiveFrameUintValue(&tmpAnalyse, "csn\":\"", 6, &Middleware_Get_FastAckSerialNo))
//		{
//			PWR_YELLOW = LED_OFF;
//			
//			return;
//		}
//		
//		// ������Ҫ���ٻذ�
//		//
//		Middleware_Set_FastAck();
//		
//		// �Ը���ָ��ֱ���
//		//
//		switch (Middleware_Get_FastAckCmdNo)
//		{
//			case 1:					// ��������������
//				if (!ControllerParameter_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				printf("controller parameter\r\n");
//				break;
//			
//			case 2:					// ������״̬��ѯ����ʱû�У�
//				break;
//			
//			case 3:					// �������豸�б�����
//				if (!ControllerDeviceList_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				printf("device list\r\n");
//				break;
//			
//			case 4:					// ������(����Ҫ�ظ�)
//				ControllerHeartbeat_DealFrameText(&tmpAnalyse);
//				Middleware_Clear_FastAck();
//				break;
//			
//			case 5:					// �м�����������(��ʱû��)
//				break;
//			
//			case 6:					// �м���ͨѶ����(��ʱû��)
//				break;
//			
//			case 7:					// ��ѯ�����ϱ�Ӧ��
//				OneCardDataUpload_PollDeviceStatus = 4;
//				Middleware_Clear_FastAck();
//				printf("upload ack\r\n");
//				break;
//			
//			case 8:					// �豸��������
//				if (!DeviceParameter_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("device parameter\r\n");
//				break;
//			
//			case 10:				// ͨ���豸ָ��
//				if (!DeviceUniversalCommand_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("universal command\r\n");
//				break;
//			
//			case 11:				// �����ϴ�
//				if (!DeviceWhiteList_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("white list\r\n");
//				break;
//				
//			case 12:				// �����ز�
//				if (!DeviceDataRecollect_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("data recollect\r\n");
//				break;
//			
//			default:
//				Middleware_SetError_FastAck();
//				break;
//		}
//		PWR_YELLOW = LED_OFF;
//	}
}



// �������߽�������
//
void Middleware_SendUrgencyDataToDevice(void)
{
	uint8_t *tmp = MiddlewareData_Fetch(MiddlewareData_SendDataUrgency);
	
	if (tmp)
	{
		// ������ѯָ��
		//
//		Wireless_SendDataToDevice(tmp);
		
//		printf("1deviceNo: %x, %x\r\n", (uint)tmp[0], (uint)tmp[1]);
//		
//		printf("1deviceType: %u\r\n", (uint)tmp[19]);
//		
//		printf("1cmdNo: %u\r\n", (uint)tmp[2]);

		// �����м����������߷��͵ȴ���ʱʱ��
		//
		Pca_Start(tmp, 0);
	}
}


// ����������ͨ����
//
void Middleware_SendNormalDataToDevice(void)
{
	uint8_t *tmp = MiddlewareData_Fetch(MiddlewareData_SendDataNormal);
	
	if (tmp)
	{
		// ������ѯָ��
		//
//		Wireless_SendDataToDevice(tmp);
		
//		printf("2cmdNo: %u\r\n", (uint)tmp[2]);
		
		// �����м����������߷��͵ȴ���ʱʱ��
		//
		Pca_Start(tmp, 0);
	}
}




