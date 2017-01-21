#include "Uart2.h"
#include "Uart1.h"


#define		UART2_RXMAX			512

bool		Uart2_RxMode = 0;									// wifi���������ݣ�0 -> ͸���������ݣ� 1 -> ָ���������

uint8_t 	Uart2_RxBuf[UART2_RXMAX];							// wifi���ݻ�����

uint16_t 	Uart2_Count = 0;									// �������ݳ���

bool        UartPack_ReciveCmdOk = 0;							// ����������ȷ��־

bool		UartPack_0x10Received = 0;   						// �Ƿ��Ѿ����յ���0x10

bool		UartPack_Started = 0;								// ͨѶ���Ƿ��Ѿ���ʼ


void Uart2_Init(void)
{
// 115200
//
	S2CON = 0x50;												// 8λ����,�ɱ䲨����
	
	AUXR |= 0x04;												// ��ʱ��2ʱ��ΪFosc,��1T
	 
	T2L = 0xD0;													// �趨��ʱ��ֵ
	
	T2H = 0xFF;													// �趨��ʱ��ֵ
	
	AUXR |= 0x10;												// ������ʱ��2

// 230400
//
//	S2CON = 0x50;												// 8λ����,�ɱ䲨����
//	
//	AUXR |= 0x04;												// ��ʱ��2ʱ��ΪFosc,��1T
//	
//	T2L = 0xE8;													// �趨��ʱ��ֵ
//	
//	T2H = 0xFF;													// �趨��ʱ��ֵ
//	
//	AUXR |= 0x10;												// ������ʱ��2

//
	IE2	= 0x01;													// ������2�ж�,ES2=1
}


#define S2TI    0x02
#define S2RI    0x01


bool Uart2_Busy = 0;


void Uart2_Interrupt(void) interrupt 8
{
	static uint8_t recived_data = 0;
	
	// ��ȡ
	//
    if(S2CON & S2RI)
    {
		S2CON &= ~S2RI;
		
		recived_data = S2BUF;
		
		// wifiָ���������
		//
		if (Uart2_RxMode)
		{
			if (Uart2_Count < UART2_RXMAX)
			{
				Uart2_RxBuf[Uart2_Count++] = recived_data;
			
//				Uart1_SendByte('#');
			}
		}
		// wifi͸����������
		//
		else
		{
			if (UartPack_ReciveCmdOk)
			{
				UartPack_Started = 0;
			
//				Uart1_SendByte('@');
				
				return;
			}
				
			// �����0x02, ����ǰ��û��ת���ַ�0x10
			//
			if( (0x02 == recived_data) && (0 == UartPack_0x10Received) )	//���յ���ʼ��־
			{
				UartPack_Started = 1;
				
				Uart2_Count = 0;
				
//				Uart1_SendByte('S');
			}
			// �����0x03, ����ǰ��û��ת���ַ�0x10
			//
			else if ((0x03 == recived_data) && (0 == UartPack_0x10Received) && (UartPack_Started))		//���յ�������־
			{
				// �ɹ�����һ�����������ݰ�
				//
				UartPack_Started = 0;
				
				UartPack_0x10Received = 0;
				
				UartPack_ReciveCmdOk = 1;
				
//				Uart1_SendByte('E');
			}
			// �����0x10, ����ǰ��û��ת���ַ�0x10
			//
			else if ((0x10 == recived_data) && (0 == UartPack_0x10Received))
			{
				UartPack_0x10Received = 1;
			}
			// �������
			//
			else if(UartPack_Started)
			{
				UartPack_0x10Received = 0;

				if (Uart2_Count < UART2_RXMAX)
				{
					Uart2_RxBuf[Uart2_Count++] = recived_data;
				}
			}
			else
			{
				UartPack_0x10Received = 0; 
				
//				Uart1_SendByte('o');
			}
		}
    }
	// д��
	//
	else if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;
        
        Uart2_Busy = 0;
    }
}


// ����Ϊ͸��ģʽ
//
void Uart2_SetMode0(void)
{
	Uart2_RxMode = 0;
	
	Uart2_Count = 0;
	
	UartPack_ReciveCmdOk = 0;
	
	UartPack_0x10Received = 0;
	
	UartPack_Started = 0;
}


// ����Ϊָ��ģʽ
//
void Uart2_SetMode1(void)
{
	Uart2_RxMode = 1;
	
	Uart2_Count = 0;
}


uint16_t Uart2_Mode0_ReceiveString(uint8_t *buffer)
{
	static uint16_t tmpCount = 0;
	
	if (UartPack_ReciveCmdOk)
	{
		memcpy(buffer, Uart2_RxBuf, Uart2_Count);
		
		tmpCount = Uart2_Count;
		
		Uart2_Count = 0; UartPack_ReciveCmdOk = 0;				// ͸�����ݽ�����ϣ���ô����״̬
		
		return tmpCount;
	}
	else
	{
		return 0;
	}
}


uint16_t Uart2_Mode1_ReceiveString(uint8_t **buffer)
{
	*buffer = Uart2_RxBuf;
	
	return Uart2_Count;
}


void Uart2_SendByte(uint8_t byte)
{
    while (Uart2_Busy)
		;
    
    Uart2_Busy = 1;
    
    S2BUF = byte;
}


void Uart2_SendString(uint8_t *string)
{
	while (*string)
	{
		Uart2_SendByte(*string++);
	}
}


void Uart2_SendNString(uint8_t *string, uint8_t count)
{
	uint8_t index;
	
	for (index = 0; index < count; index++)
	{
		Uart2_SendByte(string[index]);
	}
}




