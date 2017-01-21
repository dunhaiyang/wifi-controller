#include "Uart2.h"
#include "Uart1.h"


#define		UART2_RXMAX			512

bool		Uart2_RxMode = 0;									// wifi有两种数据：0 -> 透传接收数据， 1 -> 指令接收数据

uint8_t 	Uart2_RxBuf[UART2_RXMAX];							// wifi数据缓存区

uint16_t 	Uart2_Count = 0;									// 接收数据长度

bool        UartPack_ReciveCmdOk = 0;							// 接收命令正确标志

bool		UartPack_0x10Received = 0;   						// 是否已经接收到了0x10

bool		UartPack_Started = 0;								// 通讯包是否已经开始


void Uart2_Init(void)
{
// 115200
//
	S2CON = 0x50;												// 8位数据,可变波特率
	
	AUXR |= 0x04;												// 定时器2时钟为Fosc,即1T
	 
	T2L = 0xD0;													// 设定定时初值
	
	T2H = 0xFF;													// 设定定时初值
	
	AUXR |= 0x10;												// 启动定时器2

// 230400
//
//	S2CON = 0x50;												// 8位数据,可变波特率
//	
//	AUXR |= 0x04;												// 定时器2时钟为Fosc,即1T
//	
//	T2L = 0xE8;													// 设定定时初值
//	
//	T2H = 0xFF;													// 设定定时初值
//	
//	AUXR |= 0x10;												// 启动定时器2

//
	IE2	= 0x01;													// 允许串口2中断,ES2=1
}


#define S2TI    0x02
#define S2RI    0x01


bool Uart2_Busy = 0;


void Uart2_Interrupt(void) interrupt 8
{
	static uint8_t recived_data = 0;
	
	// 读取
	//
    if(S2CON & S2RI)
    {
		S2CON &= ~S2RI;
		
		recived_data = S2BUF;
		
		// wifi指令接收数据
		//
		if (Uart2_RxMode)
		{
			if (Uart2_Count < UART2_RXMAX)
			{
				Uart2_RxBuf[Uart2_Count++] = recived_data;
			
//				Uart1_SendByte('#');
			}
		}
		// wifi透传接收数据
		//
		else
		{
			if (UartPack_ReciveCmdOk)
			{
				UartPack_Started = 0;
			
//				Uart1_SendByte('@');
				
				return;
			}
				
			// 如果是0x02, 并且前面没有转义字符0x10
			//
			if( (0x02 == recived_data) && (0 == UartPack_0x10Received) )	//接收到开始标志
			{
				UartPack_Started = 1;
				
				Uart2_Count = 0;
				
//				Uart1_SendByte('S');
			}
			// 如果是0x03, 并且前面没有转义字符0x10
			//
			else if ((0x03 == recived_data) && (0 == UartPack_0x10Received) && (UartPack_Started))		//接收到结束标志
			{
				// 成功接收一个完整的数据包
				//
				UartPack_Started = 0;
				
				UartPack_0x10Received = 0;
				
				UartPack_ReciveCmdOk = 1;
				
//				Uart1_SendByte('E');
			}
			// 如果是0x10, 并且前面没有转义字符0x10
			//
			else if ((0x10 == recived_data) && (0 == UartPack_0x10Received))
			{
				UartPack_0x10Received = 1;
			}
			// 其他情况
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
	// 写入
	//
	else if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;
        
        Uart2_Busy = 0;
    }
}


// 设置为透传模式
//
void Uart2_SetMode0(void)
{
	Uart2_RxMode = 0;
	
	Uart2_Count = 0;
	
	UartPack_ReciveCmdOk = 0;
	
	UartPack_0x10Received = 0;
	
	UartPack_Started = 0;
}


// 设置为指令模式
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
		
		Uart2_Count = 0; UartPack_ReciveCmdOk = 0;				// 透传数据接收完毕，那么重置状态
		
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




