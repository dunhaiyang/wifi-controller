#include "Middleware.h"


Middleware_Typedef MiddlewareInfo;


uint8_t  	__Middleware_Send_ReceiveBuffer[601];


uint16_t   	__Middleware_Send_ReceiveBufferLen;


uint8_t code  __Middleware_WordArray[] = "0123456789abcdef";


void __Middleware_FastAck(void)
{
//	uint8_t		sendBufferLen = 0;
//	
//	// websocket前缀
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x81;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x80;		// 需要掩码
//	
//	// 掩码
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	// 设备编号和设备序列号
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
//	// 指令执行结果
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
//	// 设置负载长度
//	//
//	__Middleware_Send_ReceiveBuffer[1] |= sendBufferLen - 6;		// 负载不包括掩码
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
//	// websocket前缀
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x81;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0xFE;
//	
//	// 长度
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = 0x00;
//	
//	// 增加掩码
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
//	// 设备编号和设备序列号
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
//	// 准备装载数据
//	//
//	memcpy(__Middleware_Send_ReceiveBuffer + sendBufferLen, "\",\"ds\":[", 8); sendBufferLen += 8;
//	
//	// 装载数据
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
//		MiddlewareData_Free(MiddlewareData_PollData); OneCardDataUpload_SerialQuality++;	// 统计的数量在删除区间指令中使用
//	}
//	// 去掉逗号
//	//
//	--sendBufferLen;
//	
//	// 加入剩余字符
//	//
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = ']';
//	__Middleware_Send_ReceiveBuffer[sendBufferLen++] = '}';
//	
//	// 长度
//	//
//	__Middleware_Send_ReceiveBuffer[2] = (sendBufferLen - 8) >> 8;
//	
//	__Middleware_Send_ReceiveBuffer[3] = (sendBufferLen - 8);
//	
//	// 正式发送数据
//	//
//	Ch395_Write(peerSockfd, __Middleware_Send_ReceiveBuffer, sendBufferLen);
}


void __SendUrgencyDataToPC(void)
{
	switch (Middleware_Get_SlowAckCmdNo)
	{
		case 10:			// 配置设备参数
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
		case 8:				// 配置设备参数
			DeviceParameter_SendFrameTextToPc(Middleware_Get_SlowAckSerialNo,
											  __Middleware_Send_ReceiveBuffer);
			printf("DeviceParameter_SendFrameTextToPc\r\n");
			break;
		
		case 11:			// 初始化，添加，删除，更新白名单
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
	Middleware_Clear_Shakehand();				// 清空握手标记
	
	Middleware_Clear_FastAck();					// 清空快速回包标记
	
	Middleware_ClearError_FastAck();			// 清空快速回包中错误标记
	
	MiddlewareData_Init();						// 初始化动态分配内存
}


// 停止轮询，设置握手为未完成，自动重连
//
void Middleware_DealAbort(void)
{
//	PC_DisconnectToPc();
//			
//	Middleware_Init();
//	
//	PC_ConnectToPc();
}


// 如果没有成功握手，那么就发送握手包
//
void Middleware_SendShakehand(void)
{
	// 组装握手包
	//
//	Websocket_SendShakehand(peerAddr.ip, peerAddr.port, 
//					__Middleware_Send_ReceiveBuffer, 
//					&__Middleware_Send_ReceiveBufferLen);
//	
//	// 发送握手包
//	//
//	Ch395_Write(peerSockfd, 
//			__Middleware_Send_ReceiveBuffer, 
//			__Middleware_Send_ReceiveBufferLen);
}


// 处理发送网络数据逻辑
//
void Middleware_SendDataToPC(void)
{
//	static uint8_t  pollDataUpload = 0;
//	
//	// 检查是否发送快速应答包（控制器接收到服务器的指令，告诉服务器该指令已经成功接收）
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
//	// OneCardDataUpload_PollDeviceStatus == 2表示读取脱机数据完毕
//	// ++pollDataUpload > 10 && OneCardDataUpload_PollDeviceStatus == 0表示可能有实时数据
//	//
//	if (OneCardDataUpload_PollDeviceStatus == 2 || 
//		(++pollDataUpload > 10 && OneCardDataUpload_PollDeviceStatus == 0))
//	{
//		pollDataUpload = 0;
//		
//		// 有轮询数据需要上报给服务器
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
//		// 没有轮询数据需要上报给服务器
//		//
//		else
//		{
//			OneCardDataUpload_PollDeviceStatus = 0;
//		}
//	}
//	
//	// 紧急指令执行的应答包
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
//	// 普通指令执行的应答包
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
//	// 检查是否需要发送心跳数据
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


// 处理接收网络数据逻辑
//
void Middleware_ReceiveDataFromPC(void)
{
	// 如果没有获取到服务器数据，那么就立即返回
	//
//	if ((__Middleware_Send_ReceiveBufferLen = Ch395_Read(peerSockfd, 
//													__Middleware_Send_ReceiveBuffer, 1000)) == 0)
//	{
//		return;
//	}
//	
//	printf("fuqiyang\r\n");
//	
//	// 如还没完成握手，那么处理握手包
//	//
//	if (!Middleware_Get_Shakehand())
//	{
//		if (Websocket_ReceiveShakehand(__Middleware_Send_ReceiveBuffer,
//									__Middleware_Send_ReceiveBufferLen))
//		{	
//			Middleware_Set_Shakehand();
//		}
//	}
//	// 已经完成握手， 那么处理数据包
//	//
//	else
//	{
//		uint8_t *tmpAnalyse;						// 这个变量指向字符串正在处理的位置， 不用每次都从头处理
//		
//		PWR_YELLOW = LED_ON;							// 亮黄灯， 下面灭黄灯
//		
//		// 去掉websocket的帧头， 遇到不合法的websocket数据， 返回0
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
//		// 在末尾添加一个伪零，以便进行字符串处理
//		//
//		__Middleware_Send_ReceiveBuffer[__Middleware_Send_ReceiveBufferLen] = 0;
//		
//		// 接收指令号
//		//
//		if (!Json_ReceiveFrameCharValue(&tmpAnalyse, "cn\":\"", 5, &Middleware_Get_FastAckCmdNo))
//		{
//			PWR_YELLOW = LED_OFF;
//			
//			return;
//		}
//		
//		// 接收指令流水号
//		//
//		if (!Json_ReceiveFrameUintValue(&tmpAnalyse, "csn\":\"", 6, &Middleware_Get_FastAckSerialNo))
//		{
//			PWR_YELLOW = LED_OFF;
//			
//			return;
//		}
//		
//		// 设置需要快速回包
//		//
//		Middleware_Set_FastAck();
//		
//		// 对各个指令分别处理
//		//
//		switch (Middleware_Get_FastAckCmdNo)
//		{
//			case 1:					// 控制器参数配置
//				if (!ControllerParameter_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				printf("controller parameter\r\n");
//				break;
//			
//			case 2:					// 控制器状态查询（暂时没有）
//				break;
//			
//			case 3:					// 控制器设备列表配置
//				if (!ControllerDeviceList_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				printf("device list\r\n");
//				break;
//			
//			case 4:					// 心跳包(不需要回复)
//				ControllerHeartbeat_DealFrameText(&tmpAnalyse);
//				Middleware_Clear_FastAck();
//				break;
//			
//			case 5:					// 中继器参数配置(暂时没有)
//				break;
//			
//			case 6:					// 中继器通讯测试(暂时没有)
//				break;
//			
//			case 7:					// 轮询数据上报应答
//				OneCardDataUpload_PollDeviceStatus = 4;
//				Middleware_Clear_FastAck();
//				printf("upload ack\r\n");
//				break;
//			
//			case 8:					// 设备参数配置
//				if (!DeviceParameter_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("device parameter\r\n");
//				break;
//			
//			case 10:				// 通用设备指令
//				if (!DeviceUniversalCommand_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("universal command\r\n");
//				break;
//			
//			case 11:				// 名单上传
//				if (!DeviceWhiteList_DealFrameText(&tmpAnalyse))
//				{
//					Middleware_SetError_FastAck();
//				}
//				Middleware_Set_SlowAckCmdNo(Middleware_Get_FastAckCmdNo);
//				Middleware_Set_SlowAckSerialNo(Middleware_Get_FastAckSerialNo);
//				printf("white list\r\n");
//				break;
//				
//			case 12:				// 数据重采
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



// 发送无线紧急数据
//
void Middleware_SendUrgencyDataToDevice(void)
{
	uint8_t *tmp = MiddlewareData_Fetch(MiddlewareData_SendDataUrgency);
	
	if (tmp)
	{
		// 发送轮询指令
		//
//		Wireless_SendDataToDevice(tmp);
		
//		printf("1deviceNo: %x, %x\r\n", (uint)tmp[0], (uint)tmp[1]);
//		
//		printf("1deviceType: %u\r\n", (uint)tmp[19]);
//		
//		printf("1cmdNo: %u\r\n", (uint)tmp[2]);

		// 根据中继来设置无线发送等待超时时间
		//
		Pca_Start(tmp, 0);
	}
}


// 发送无线普通数据
//
void Middleware_SendNormalDataToDevice(void)
{
	uint8_t *tmp = MiddlewareData_Fetch(MiddlewareData_SendDataNormal);
	
	if (tmp)
	{
		// 发送轮询指令
		//
//		Wireless_SendDataToDevice(tmp);
		
//		printf("2cmdNo: %u\r\n", (uint)tmp[2]);
		
		// 根据中继来设置无线发送等待超时时间
		//
		Pca_Start(tmp, 0);
	}
}




