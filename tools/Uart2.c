#include "Uart2.h"



//uchar 	xdata			Uart2_RxBufCount = 0;
//uchar 	xdata 			Uart2_RxBuf[Uart2_RXLEN];

//bit           	        UartPack_ReciveCmdOk = NO;							// 接收命令正确标志
//bit			  			UartPack_0x10Received = NO;   						// 是否已经接收到了0x10
//bit						UartPack_Started = NO;								// 通讯包是否已经开始


// 波特率为115200
//
void Uart2_Init(void)
{
	S2CON = 0x50;			// 8位数据,可变波特率
	
	AUXR |= 0x04;			// 定时器2时钟为Fosc,即1T
	 
	T2L = 0xD0;				// 设定定时初值
	
	T2H = 0xFF;				// 设定定时初值
	
	AUXR |= 0x10;			// 启动定时器2
	
	IE2	= 0x01;				// 允许串口2中断,ES2=1
}


//#define S2TI    0x02
//#define S2RI    0x01

//bit Uart2_Busy = 0;


//void Uart2_Interrupt(void) interrupt 8
//{
//    static uchar idata recived_data = 0;
//    
//    if(S2CON & S2RI)
//    {
//		S2CON &= ~S2RI;
//        
//        recived_data = S2BUF;
//        
//        if (UartPack_ReciveCmdOk)
//        {
//            UartPack_Started = NO;
//            
//            return;
//        }
//        	
//        // 如果是0x02, 并且前面没有转义字符0x10
//        //
//        if( (0x02 == recived_data) && (NO == UartPack_0x10Received) )	//接收到开始标志
//        {
//            UartPack_Started = YES;
//            
//            Uart2_RxBufCount = 0;
//        }
//        // 如果是0x03, 并且前面没有转义字符0x10
//        //
//        else if ((0x03 == recived_data) && (NO == UartPack_0x10Received) && (UartPack_Started))		//接收到结束标志
//        {
//            // 成功接收一个完整的数据包
//            //
//            UartPack_Started = NO;
//            
//            UartPack_0x10Received = NO;
//            
//            UartPack_ReciveCmdOk = YES;
//        }
//        // 如果是0x10, 并且前面没有转义字符0x10
//        //
//        else if ((0x10 == recived_data) && (NO == UartPack_0x10Received))
//        {
//            UartPack_0x10Received = YES;
//        }
//        // 其他情况
//        //
//        else if(UartPack_Started)
//        {
//            UartPack_0x10Received = NO;

//            if (Uart2_RxBufCount < Uart2_RXLEN)
//            {
//                Uart2_RxBuf[Uart2_RxBufCount++] = recived_data;
//            }
//        }
//        else
//        {
//             UartPack_0x10Received = NO; 
//        }
//    }
//    else if (S2CON & S2TI)
//    {
//        S2CON &= ~S2TI;
//        
//        Uart2_Busy = 0;
//    }
//}


//void Uart2_SendByte(uchar send_data)
//{
//    while (Uart2_Busy)
//    {
//        ;
//    }
//    
//    Uart2_Busy = 1;
//    
//    S2BUF = send_data;
//}


//void Uart2_SendString(uchar *string)
//{
//	while (*string)
//	{
//		Uart2_SendByte(*string);
//		
//		string++;
//	}
//}


