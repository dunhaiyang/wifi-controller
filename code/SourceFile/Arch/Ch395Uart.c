#include "Ch395Uart.h"



/********************************************************************************
* Function Name  : mDelayuS
* Description    : ��ʱָ��΢��ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ
* Input          : us---��ʱʱ��ֵ
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS(UINT8 us)
{
    while(us --);                                                    /* MCS51@24MHz */
}

/*******************************************************************************
* Function Name  : mDelaymS
* Description    : ��ʱָ������ʱ��,���ݵ�Ƭ����Ƶ����,����ȷ
* Input          : ms---��ʱʱ��ֵ
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS(UINT8 ms)
{
    while(ms --) 
    {
        mDelayuS(250);
        mDelayuS(250);
        mDelayuS(250);
        mDelayuS(250);
    }
}

/*******************************************************************************
* Function Name  : CH395_PORT_INIT
* Description    : Ӳ����ʼ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT(void)
{
    CH395_SPI_SCS = 1;
    CH395_SPI_SCK = 1;                                               /*  SIP_CLKΪ�ߵ�ƽ��������ʹ��SPIģʽ3��Ҳ����ʹ��ģʽ0*/
}

/*******************************************************************************
* Function Name  : Spi395OutByte
* Description    : ��CH395����8λ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Spi395OutByte(UINT8 mdata)                                      /* SPI���8λ���� */
{                                                                    /* �����Ӳ��SPI����ֻ��Ҫ������д��SPI�����ݼĴ����� */
    UINT8   i;                                                       /* Ȼ��ȴ�������ɼ��� */

    for ( i = 0; i < 8; i ++ ) 
    {
        CH395_SPI_SCK = 0;                                           /* CLK���� */
        if( mdata & 0x80 )CH395_SPI_SDI = 1; 
        else CH395_SPI_SDI = 0;
        mdata <<= 1;                                                 /* ����λ�Ǹ�λ��ǰ */
        CH395_SPI_SCK = 1;                                           /* CH395��ʱ�������ز������� */
    }
}

/*******************************************************************************
* Function Name  : Spi395InByte
* Description    : ��CH395��8λ����
* Input          : None
* Output         : None
* Return         : 8λ����
*******************************************************************************/
UINT8 Spi395InByte(void)                                             /* SPI����8λ���� */
{                                                                    /* �����Ӳ��SPI�ӿ�,Ӧ�����Ȳ�ѯSPI״̬�Ĵ����Եȴ�SPI�ֽ�*/
    UINT8   i, d;                                                    /* �������,Ȼ���SPI���ݼĴ����������� */
    d = 0;

    for ( i = 0; i < 8; i ++ )  
    {
        CH395_SPI_SCK = 0;                                           /* CH395��ʱ���½������ */
        d <<= 1;  /* ����λ�Ǹ�λ��ǰ */
        if ( CH395_SPI_SDO) d ++;
        CH395_SPI_SCK = 1;
    }
    return( d );
}

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : ��CH395����8λ������
* Input          : 8λ������
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                       /* ��CH395д���� */
{
    xEndCH395Cmd();                                                  /* ��ֹCSԭ��Ϊ�ͣ��Ƚ�CD�ø� */
    xCH395CmdStart( );                                               /* ���ʼ������CS���� */
    Spi395OutByte(cmd);                                              /* Ӳ��SPI����8λ������ */
    mDelayuS(2);                                                     /* ��Ҫ��ʱ,��ʱ1.5uSȷ����д���ڲ�С��1.5uS */
}

/********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : ��CH395����8λ����
* Input          : 8λ����
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)                                  /* ��CH395д���� */
{   
    Spi395OutByte(mdata);                                                      
}

/********************************************************************************
* Function Name  : xReadCH395Data
* Description    : ��CH395��������
* Input          : None 
* Output         : None
* Return         : 8λ����
*******************************************************************************/
UINT8   xReadCH395Data( void )                                       /* ��CH395������ */
{
    UINT8 i;
    i = Spi395InByte( );
    return i;
}















//#define CH395_INT_WIRE             INT1                          /* �ٶ�CH395��INT#����,���δ������ôҲ����ͨ����ѯ�����ж�״̬��ʵ�� */

//#define UART_INIT_BAUDRATE         115200                        /* Ĭ��ͨѶ������9600bps,����ͨ��Ӳ�������趨ֱ��ѡ����ߵ�CH395��Ĭ��ͨѶ������ */
//#define UART_WORK_BAUDRATE         115200                        /* ��ʽͨѶ������57600bps */

//#define S2TI    0x02
//#define S2RI    0x01


///*******************************************************************************
//* Function Name  : CH395_PORT_INIT
//* Description    : ������Ϊ115200
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void CH395_InitUart2(void)
//{
//}

///*******************************************************************************
//* Function Name  : Set_MCU_BaudRate
//* Description    : ���õ�Ƭ��������
//*                  ����Ƭ���л�����ʽͨѶ������ 
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void SetMCUBaudRate(void)                                
//{
//////  TL2 = RCAP2L = 0 - 18432000/32/UART_WORK_BAUDRATE;               /* 18.432MHz���� */
////    TL2 = RCAP2L = 0 - 24000000/32/UART_WORK_BAUDRATE;               /* 24MHz���� */
////    RI = 0;
//}


///********************************************************************************
//* Function Name  : xWriteCH395Cmd
//* Description    : ��CH395д����
//* Input          : cmd 8λ��������
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void xWriteCH395Cmd(UINT8 cmd)                                      
//{
//	S2CON &= ~S2TI;
//    S2BUF = SER_SYNC_CODE1;                                           /* ���������ĵ�1������ͬ���� */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2TI;
//    S2BUF = SER_SYNC_CODE2;                                           /* ���������ĵ�2������ͬ���� */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2TI;
//    S2BUF = cmd;                                                      /* ������� */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2RI;
//}

///********************************************************************************
//* Function Name  : xWriteCH395Data
//* Description    : ��CH395д����
//* Input          : mdata 8λ����
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void  xWriteCH395Data(UINT8 mdata)
//{                                                                    	/* ��CH395д���� */
//    S2CON &= ~S2TI;
//    S2BUF = mdata;                                                    /* ������� */
//    while((S2CON & S2TI) == 0);
//}

///********************************************************************************
//* Function Name  : xReadCH395Data
//* Description    : ��CH395������
//* Input          : None
//* Output         : None
//* Return         : 8λ����
//*******************************************************************************/
//UINT8  xReadCH395Data(void)                                          /* ��CH395������ */
//{
//    UINT32 xdata i;
//    
//    for(i = 0; i < 500000; i ++) 
//    {  
//        /* ������ֹ��ʱ */
//        if(S2CON & S2RI) 
//        {  
//            /* ���ڽ��յ� */
//			S2CON &= ~S2RI;
//            return(S2BUF);                                            /* �������� */
//        }
//    }
//    return(0);                                                       /* ��Ӧ�÷�������� */
//}


