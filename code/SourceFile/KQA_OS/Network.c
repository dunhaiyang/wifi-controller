#include "Network.h"


static	Network *Network_self;


//NetworkParameter Network_Parameter = {
//	
//	{192, 168, 1, 120},										// ���ص�ַ
//	
//	{192, 168, 1, 1},										// Ĭ������
//	
//	{255, 255, 255, 0},										// ����
//	
//	{0, 0, 0, 0, 0, 0},										// MAC��ַ(������ᱻ��ȡ������ʵ��mac��ַ��ȡ��)
//	
//};


//NetworkSocket Network_Socket0 = {
//	
//	4001,													// ���ض˿�
//		
//	4001,													// Զ�̶˿�
//	
//	{192, 168, 1, 105},										// Զ��ip
//	
//};


NetworkParameter Network_Parameter = {
	
	{192, 168, 1, 150},										// ���ص�ַ
	
	{192, 168, 1, 1},										// Ĭ������
	
	{255, 255, 255, 0},										// ����
	
	{0, 0, 0, 0, 0, 0},										// MAC��ַ(������ᱻ��ȡ������ʵ��mac��ַ��ȡ��)
	
};


NetworkSocket Network_Socket0 = {
	
	4001,													// ���ض˿�
		
	4001,													// Զ�̶˿�
	
	{192, 168, 1, 102},										// Զ��ip
	
};


NetworkBoardcastData		Network_BoardcastData = {
	
	0,														// ��ʼ��û�н��յ�����
	
};


NetworkSocketData			Network_SocketData = {
	
	0,														// ��ʼ��û�н��յ�����
};



void __SubBoardcastRead(void)
{
	uint8_t		i;
	
	uint8_t		tmp_ReceiveCount = 0;
	
	uint8_t		have0x02 = 0;
	
	uint8_t		have0x10 = 0;
	
	if (!BoardcastData_ReceiveOk)
	{
		// ======================== ��ȡ���ݳ��� =========================
		//
		BoardcastData_ReceiveBufferCount = CH395GetRecvLength(1);
		
		
		// ======================== ��ȡ�ͽ������� =========================
		//
		if (BoardcastData_ReceiveBufferCount > 0)
		{	
			CH395GetRecvData(1, BoardcastData_ReceiveBufferCount, __BoardcastData_ReceiveBuffer);
			
			// ȥ��������ֽ�(Э���֡ͷ0x02, ת���ַ�0x10, ֡β0x03)
			//
			for (i = 0; i < BoardcastData_ReceiveBufferCount; i++)
			{
				// �����û���յ�0x02��ͷ�ֽ�
				//
				if (!have0x02)
				{
					if (__BoardcastData_ReceiveBuffer[i] == 0x02)
					{
						have0x02 = 1;
					}
					continue;
				}
				
				// �����û���յ�0x10��ת���ַ�
				//
				if (!have0x10)
				{
					if (__BoardcastData_ReceiveBuffer[i] == 0x10)
					{
						have0x10 = 1;
						
						continue;
					}
					
					// ������յ�0x03��β�ֽ�
					//
					if (__BoardcastData_ReceiveBuffer[i] == 0x03)
					{
						if (!(BoardcastData_ReceiveBuffer[0] == 0x61 || BoardcastData_ReceiveBuffer[0] == 0x63))
						{
							return;
						}
						if (BoardcastData_ReceiveBuffer[0] == 0x63 && memcmp(BoardcastData_ReceiveBuffer + 3, NETPARA_MAC, 6) != 0)
						{
							return;
						}
						BoardcastData_ReceiveOk = 1;
						
						BoardcastData_ReceiveBufferCount = tmp_ReceiveCount;
						
						return;
					}
				}
				else
				{
					have0x10 = 0;
				}
				BoardcastData_ReceiveBuffer[tmp_ReceiveCount++] = __BoardcastData_ReceiveBuffer[i];
			}
		}
	}
}


void __SubSocketRead(void)
{
	uint8_t		i;
	
	uint8_t		tmp_ReceiveCount = 0;
	
	uint8_t		have0x02 = 0;
	
	uint8_t		have0x10 = 0;
	
	if (!SocketData_ReceiveOk)
	{
		// ======================== ����ȡ���ݳ��� =========================
		//
		SocketData_ReceiveBufferCount = CH395GetRecvLength(0);
		
		
		// ======================== ��ȡ�ͽ������� =========================
		//
		if (SocketData_ReceiveBufferCount > 0)
		{	
			CH395GetRecvData(0, SocketData_ReceiveBufferCount, __SocketData_ReceiveBuffer);
			
			// ȥ��������ֽ�(Э���֡ͷ0x02, ת���ַ�0x10, ֡β0x03)
			//
			for (i = 0; i < SocketData_ReceiveBufferCount; i++)
			{
				// �����û���յ�0x02��ͷ�ֽ�
				//
				if (!have0x02)
				{
					if (__SocketData_ReceiveBuffer[i] == 0x02)
					{
						have0x02 = 1;
					}
					continue;
				}
				
				// �����û���յ�0x10��ת���ַ�
				//
				if (!have0x10)
				{
					if (__SocketData_ReceiveBuffer[i] == 0x10)
					{
						have0x10 = 1;
						
						continue;
					}
					
					// ������յ�0x03��β�ֽ�
					//
					if (__SocketData_ReceiveBuffer[i] == 0x03)
					{
						SocketData_ReceiveOk = 1;
						
						SocketData_ReceiveBufferCount = tmp_ReceiveCount;
						
						return;
					}
				}
				else
				{
					have0x10 = 0;
				}
				SocketData_ReceiveBuffer[tmp_ReceiveCount++] = __SocketData_ReceiveBuffer[i];
			}
		}
	}
}


void Network_ConnectUdp(void)
{
	// ����socket0ΪUDP����
	//
	HAL_NETWORK_CH395SETSOCKETTYPE(0, PROTO_TYPE_UDP);
	
	// ����socket0��Դ�˿�
	//
	HAL_NETWORK_CH395SETSOCKETSOURCEPORT(0, SOCKET0_LOCALPORT);
	
	// ����Զ��IP
	//
	HAL_NETWORK_CH395SETSOCKETDESIP(0, SOCKET0_REMOTEIP);
	
	// ����Զ��PORT
	//
	HAL_NETWORK_CH395SETSOCKETDESPORT(0, SOCKET0_REMOTEPORT);
	
	// ��socket
	//
	HAL_NETWORK_CH395SOCKETOPEN(0);
}


void Network_SendUdp(uint8_t *buffer, uint16_t bufferLen)
{
	static	int8_t	ret;
	
	// �����û�����
	//
	HAL_NETWORK_CH395SENDDATA(0, buffer, bufferLen);
	
	// �ȴ����ͻ�����Ϊ��, ���߷��ͳ�ʱ
	//
	do
	{
		ret = HAL_NETWORK_CH395GETSOCKETINT(0);
		
	}while ((ret & SINT_STAT_SENBUF_FREE) != 0 || (ret & SINT_STAT_TIM_OUT));
}


uint16_t Network_ReceiveUdp(uint8_t *buffer)
{
	uint16_t tmpCount = SocketData_ReceiveBufferCount;
	
	memcpy(buffer, SocketData_ReceiveBuffer, SocketData_ReceiveBufferCount);
	
	SocketData_ReceiveBufferCount = 0; SocketData_ReceiveOk = 0;
	
	return tmpCount;
}


void Network_ConnectBoardcast(void)
{
	static uint8_t boardcastIP[4] = {255, 255, 255, 255};
	
	// ����socket0������ΪUDP
	//
	HAL_NETWORK_CH395SETSOCKETTYPE(1, PROTO_TYPE_UDP);
	
	// ����socket0��Դ�˿�
	//
	HAL_NETWORK_CH395SETSOCKETSOURCEPORT(1, 10087);
	
	// ����Զ��IP
	//
	HAL_NETWORK_CH395SETSOCKETDESIP(1, boardcastIP);
	
	// ����Զ��PORT
	//
	HAL_NETWORK_CH395SETSOCKETDESPORT(1, 10086);
	
	// ��socket
	//
	HAL_NETWORK_CH395SOCKETOPEN(1);
}


void Network_SendBoardcast(uint8_t *buffer, uint16_t bufferLen)
{
	static	int8_t	ret;
	
	// �����û�����
	//
	HAL_NETWORK_CH395SENDDATA(1, buffer, bufferLen);
	
	// �ȴ����ͻ�����Ϊ��, ���߷��ͳ�ʱ
	//
	do
	{
		ret = HAL_NETWORK_CH395GETSOCKETINT(1);
		
	}while ((ret & SINT_STAT_SENBUF_FREE) != 0 || (ret & SINT_STAT_TIM_OUT));
}


uint16_t Network_ReceiveBoardcast(uint8_t *buffer)
{
	uint16_t tmpCount = BoardcastData_ReceiveBufferCount;
	
	memcpy(buffer, BoardcastData_ReceiveBuffer, BoardcastData_ReceiveBufferCount);
	
	BoardcastData_ReceiveBufferCount = 0; BoardcastData_ReceiveOk = 0;
	
	return tmpCount;
}


void Network_RegisterErrorFunction(void *func)
{
	Network_self->error = func;
}


void Network_PeriodTask(void)
{
	if (CH395_INT_WIRE == 0)														// �жϽ�Ϊ�ͣ�˵�������鷢��
	{
		Network_self->globalStatus = HAL_NETWORK_CH395GETGLOBALINT_ALL();
		
		if (Network_self->globalStatus & 0x20)										// socket1 �ж�(socket1 ����㲥��)
		{
			Network_self->socket1Status = HAL_NETWORK_CH395GETSOCKETINT(1);
			
			if (Network_self->socket1Status & 0x04)									// socket1 �����ݿɶ�
			{
				__SubBoardcastRead();
			}
		}
		
		if(Network_self->globalStatus & 0x10)									// socket0 �ж�(socket0 �������ݰ�)
		{
			Network_self->socket0Status = HAL_NETWORK_CH395GETSOCKETINT(0);
			
			if (Network_self->socket0Status & 0x04)									// socket0 �����ݿɶ�
			{
				__SubSocketRead();
			}
		}
		
		if(!(Network_self->globalStatus & 0x10 || Network_self->globalStatus & 0x20))
		{
			if (Network_self->error)
			{
				Network_self->error();
			}
		}
	}
}


void Network_AllParameters(void)
{
	printf("eth0\t\tLink encap:Ethernet  HWaddr %x:%x:%x:%x:%x:%x\r\n", (uint16_t)(NETPARA_MAC[0]), 
																		(uint16_t)(NETPARA_MAC[1]), 
																		(uint16_t)(NETPARA_MAC[2]), 
																		(uint16_t)(NETPARA_MAC[3]),
																		(uint16_t)(NETPARA_MAC[4]), 
																		(uint16_t)(NETPARA_MAC[5]));
	
	printf("\t\tLocal IP: %u.%u.%u.%u  Port: %u\r\n",	(uint16_t)(NETPARA_IP[0]), 
														(uint16_t)(NETPARA_IP[1]), 
														(uint16_t)(NETPARA_IP[2]), 
														(uint16_t)(NETPARA_IP[3]),
														(uint16_t)(SOCKET0_LOCALPORT));
											  
	printf("\t\tRemote IP: %u.%u.%u.%u  RemotePort: %u\r\n", 	(uint16_t)(SOCKET0_REMOTEIP[0]), 
																(uint16_t)(SOCKET0_REMOTEIP[1]), 
																(uint16_t)(SOCKET0_REMOTEIP[2]), 
																(uint16_t)(SOCKET0_REMOTEIP[3]),
																(uint16_t)(SOCKET0_REMOTEPORT));
	
	printf("\t\tGateway: %u.%u.%u.%u  Mask: %u.%u.%u.%u\r\n",	 (uint16_t)(NETPARA_GATEWAY[0]), 
																(uint16_t)(NETPARA_GATEWAY[1]), 
																(uint16_t)(NETPARA_GATEWAY[2]), 
																(uint16_t)(NETPARA_GATEWAY[3]),
																(uint16_t)(NETPARA_MASK[0]), 
																(uint16_t)(NETPARA_MASK[1]), 
																(uint16_t)(NETPARA_MASK[2]), 
																(uint16_t)(NETPARA_MASK[3]));
}


void Network_Reboot(void)
{
	// ��ʼ��CH395
	//
	HAL_NETWORK_CH395REBOOT();										// ��λCH395
	
	HAL_DELAY1MS(100);												// CH395��Ӳ����λͨ����Ҫ50ms
	
	HAL_NETWORK_CH395SETIPADDR(NETPARA_IP);							// ���ñ���IP
	
	HAL_NETWORK_CH395SETGATEWAY(NETPARA_GATEWAY);					// ���ñ��ص�����
	
	HAL_NETWORK_CH395SETMASKADDR(NETPARA_MASK);						// ���ñ��ص�����
	
	HAL_NETWORK_CH395GETMACADDR(NETPARA_MAC);						// ��ȡ����mac��ַ
	
	HAL_NETWORK_CH395INIT();										// ��ʼ��CH395
	
	Network_self->connectUdp();
	
	Network_self->connectBoardcast();
}



void Network_Init(void *self)
{
	Network_self = self;
	
	Network_self->init = Network_Init;
	
	Network_self->error = 0;
	
	//
	Network_self->allParameters = Network_AllParameters;
	
	Network_self->reboot = Network_Reboot;
	
	//
	Network_self->registerErrorFunction = Network_RegisterErrorFunction;
	
	Network_self->run = Network_PeriodTask;
	
	// UDP
	//
	Network_self->connectUdp = Network_ConnectUdp;
	
	Network_self->writeUdp = Network_SendUdp;
	
	Network_self->readUdp = Network_ReceiveUdp;
	
	// �㲥
	//
	Network_self->connectBoardcast = Network_ConnectBoardcast;
	
	Network_self->writeBoardcast = Network_SendBoardcast;
	
	Network_self->readBoardcast = Network_ReceiveBoardcast;
}


