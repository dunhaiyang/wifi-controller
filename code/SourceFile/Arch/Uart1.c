#include "Uart1.h"


#ifdef  Uart1_Debug


#define UART1_RECEIVE_MAX	10


uint8_t Uart1_ReceiveBuffer[UART1_RECEIVE_MAX];


uint8_t Uart1_ReceiveLen = 0;							// 数据存入的位置


uint8_t Uart1_FetchLen = 0;								// 数据获取的位置


//------------ 主串口 -------------
//
void Uart1_Init( void )
{
// 115200
//
    SCON = 0x50;		// 8位数据,可变波特率
	
	AUXR |= 0x40;		// 定时器1时钟为Fosc,即1T
	
	AUXR &= 0xFE;		// 串口1选择定时器1为波特率发生器
	
	TMOD &= 0x0F;		// 设定定时器1为16位自动重装方式
	
	TL1 = 0xD0;			// 设定定时初值
	
	TH1 = 0xFF;			// 设定定时初值
	
	ET1 = 0;			// 禁止定时器1中断
	
	TR1 = 1;			// 启动定时器1
	
	PS = 1;				// 高优先级
    
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
		
		// 避免越界
		//
		if (Uart1_ReceiveLen >= UART1_RECEIVE_MAX)
		{
			Uart1_ReceiveLen = 0;
		}
		
		// 存储数据
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
	// 避免越界
	//
	if (Uart1_FetchLen >= UART1_RECEIVE_MAX)
	{
		Uart1_FetchLen = 0;
	}
	
	// 获取数据
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


// 为了支持printf的重定向
//
int8_t putchar(int8_t c)
{
	Uart1_SendByte(c);
	
	return c;
}


#endif

