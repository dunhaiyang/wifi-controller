#include "Uart2.h"



//uchar 	xdata			Uart2_RxBufCount = 0;
//uchar 	xdata 			Uart2_RxBuf[Uart2_RXLEN];

//bit           	        UartPack_ReciveCmdOk = NO;							// ����������ȷ��־
//bit			  			UartPack_0x10Received = NO;   						// �Ƿ��Ѿ����յ���0x10
//bit						UartPack_Started = NO;								// ͨѶ���Ƿ��Ѿ���ʼ


// ������Ϊ115200
//
void Uart2_Init(void)
{
	S2CON = 0x50;			// 8λ����,�ɱ䲨����
	
	AUXR |= 0x04;			// ��ʱ��2ʱ��ΪFosc,��1T
	 
	T2L = 0xD0;				// �趨��ʱ��ֵ
	
	T2H = 0xFF;				// �趨��ʱ��ֵ
	
	AUXR |= 0x10;			// ������ʱ��2
	
	IE2	= 0x01;				// ������2�ж�,ES2=1
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
//        // �����0x02, ����ǰ��û��ת���ַ�0x10
//        //
//        if( (0x02 == recived_data) && (NO == UartPack_0x10Received) )	//���յ���ʼ��־
//        {
//            UartPack_Started = YES;
//            
//            Uart2_RxBufCount = 0;
//        }
//        // �����0x03, ����ǰ��û��ת���ַ�0x10
//        //
//        else if ((0x03 == recived_data) && (NO == UartPack_0x10Received) && (UartPack_Started))		//���յ�������־
//        {
//            // �ɹ�����һ�����������ݰ�
//            //
//            UartPack_Started = NO;
//            
//            UartPack_0x10Received = NO;
//            
//            UartPack_ReciveCmdOk = YES;
//        }
//        // �����0x10, ����ǰ��û��ת���ַ�0x10
//        //
//        else if ((0x10 == recived_data) && (NO == UartPack_0x10Received))
//        {
//            UartPack_0x10Received = YES;
//        }
//        // �������
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


