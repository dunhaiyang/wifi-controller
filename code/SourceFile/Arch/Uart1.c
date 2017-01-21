#include "Uart1.h"


#ifdef  Uart1_Debug


#define UART1_RECEIVE_MAX	10


uint8_t Uart1_ReceiveBuffer[UART1_RECEIVE_MAX];


uint8_t Uart1_ReceiveLen = 0;							// ���ݴ����λ��


uint8_t Uart1_FetchLen = 0;								// ���ݻ�ȡ��λ��


//------------ ������ -------------
//
void Uart1_Init( void )
{
// 115200
//
    SCON = 0x50;		// 8λ����,�ɱ䲨����
	
	AUXR |= 0x40;		// ��ʱ��1ʱ��ΪFosc,��1T
	
	AUXR &= 0xFE;		// ����1ѡ��ʱ��1Ϊ�����ʷ�����
	
	TMOD &= 0x0F;		// �趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	
	TL1 = 0xD0;			// �趨��ʱ��ֵ
	
	TH1 = 0xFF;			// �趨��ʱ��ֵ
	
	ET1 = 0;			// ��ֹ��ʱ��1�ж�
	
	TR1 = 1;			// ������ʱ��1
	
	PS = 1;				// �����ȼ�
    
    ES = 1;
	
	EA = 1;
}


bool Uart1_Busy = 0;


void Uart1_Interrupt( void ) interrupt 4
{
	if(TI)
	{ 
        TI = 0;
        
        Uart1_Busy = 0;
	}
    else if(RI)
	{
        RI = 0;
		
		// ����Խ��
		//
		if (Uart1_ReceiveLen >= UART1_RECEIVE_MAX)
		{
			Uart1_ReceiveLen = 0;
		}
		
		// �洢����
		//
		Uart1_ReceiveBuffer[Uart1_ReceiveLen++] = SBUF;
	}
}


bool Uart1_Available(void)
{
	return (Uart1_FetchLen != Uart1_ReceiveLen);
}



uint8_t	Uart1_ReceiveByte(void)
{
	// ����Խ��
	//
	if (Uart1_FetchLen >= UART1_RECEIVE_MAX)
	{
		Uart1_FetchLen = 0;
	}
	
	// ��ȡ����
	//
	return Uart1_ReceiveBuffer[Uart1_FetchLen++];
}


void Uart1_SendByte(uint8_t send_data)
{	
    while (Uart1_Busy)
		;
    
    Uart1_Busy = 1;
    
    SBUF = send_data;
}


void Uart1_SendNString(uint8_t *send_string, uint8_t len)
{
	uint8_t i = 0;

	for (i = 0; i < len; ++i)
	{
		Uart1_SendByte(send_string[i]);
	}
}

void Uart1_SendString(uint8_t *send_string)
{
	while (*send_string != 0)
	{
		Uart1_SendByte(*send_string);
		
		send_string++;
	}
}


// Ϊ��֧��printf���ض���
//
int8_t putchar(int8_t c)
{
	Uart1_SendByte(c);
	
	return c;
}


#endif

