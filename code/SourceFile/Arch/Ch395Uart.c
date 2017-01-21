#include "Ch395Uart.h"



/********************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS(UINT8 us)
{
    while(us --);                                                    /* MCS51@24MHz */
}

/*******************************************************************************
* Function Name  : mDelaymS
* Description    : 延时指定毫秒时间,根据单片机主频调整,不精确
* Input          : ms---延时时间值
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
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT(void)
{
    CH395_SPI_SCS = 1;
    CH395_SPI_SCK = 1;                                               /*  SIP_CLK为高电平，本程序使用SPI模式3，也可以使用模式0*/
}

/*******************************************************************************
* Function Name  : Spi395OutByte
* Description    : 向CH395发送8位数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Spi395OutByte(UINT8 mdata)                                      /* SPI输出8位数据 */
{                                                                    /* 如果是硬件SPI，在只需要将数据写入SPI的数据寄存器中 */
    UINT8   i;                                                       /* 然后等待发送完成即可 */

    for ( i = 0; i < 8; i ++ ) 
    {
        CH395_SPI_SCK = 0;                                           /* CLK拉低 */
        if( mdata & 0x80 )CH395_SPI_SDI = 1; 
        else CH395_SPI_SDI = 0;
        mdata <<= 1;                                                 /* 数据位是高位在前 */
        CH395_SPI_SCK = 1;                                           /* CH395在时钟上升沿采样输入 */
    }
}

/*******************************************************************************
* Function Name  : Spi395InByte
* Description    : 从CH395读8位数据
* Input          : None
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8 Spi395InByte(void)                                             /* SPI输入8位数据 */
{                                                                    /* 如果是硬件SPI接口,应该是先查询SPI状态寄存器以等待SPI字节*/
    UINT8   i, d;                                                    /* 传输完成,然后从SPI数据寄存器读出数据 */
    d = 0;

    for ( i = 0; i < 8; i ++ )  
    {
        CH395_SPI_SCK = 0;                                           /* CH395在时钟下降沿输出 */
        d <<= 1;  /* 数据位是高位在前 */
        if ( CH395_SPI_SDO) d ++;
        CH395_SPI_SCK = 1;
    }
    return( d );
}

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395发送8位命令码
* Input          : 8位命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                       /* 向CH395写命令 */
{
    xEndCH395Cmd();                                                  /* 防止CS原来为低，先将CD置高 */
    xCH395CmdStart( );                                               /* 命令开始，必须CS拉低 */
    Spi395OutByte(cmd);                                              /* 硬件SPI发送8位命令码 */
    mDelayuS(2);                                                     /* 必要延时,延时1.5uS确保读写周期不小于1.5uS */
}

/********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395发送8位数据
* Input          : 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)                                  /* 向CH395写数据 */
{   
    Spi395OutByte(mdata);                                                      
}

/********************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读读数据
* Input          : None 
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8   xReadCH395Data( void )                                       /* 从CH395读数据 */
{
    UINT8 i;
    i = Spi395InByte( );
    return i;
}















//#define CH395_INT_WIRE             INT1                          /* 假定CH395的INT#引脚,如果未连接那么也可以通过查询串口中断状态码实现 */

//#define UART_INIT_BAUDRATE         115200                        /* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH395的默认通讯波特率 */
//#define UART_WORK_BAUDRATE         115200                        /* 正式通讯波特率57600bps */

//#define S2TI    0x02
//#define S2RI    0x01


///*******************************************************************************
//* Function Name  : CH395_PORT_INIT
//* Description    : 波特率为115200
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void CH395_InitUart2(void)
//{
//}

///*******************************************************************************
//* Function Name  : Set_MCU_BaudRate
//* Description    : 设置单片机波特率
//*                  将单片机切换到正式通讯波特率 
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void SetMCUBaudRate(void)                                
//{
//////  TL2 = RCAP2L = 0 - 18432000/32/UART_WORK_BAUDRATE;               /* 18.432MHz晶振 */
////    TL2 = RCAP2L = 0 - 24000000/32/UART_WORK_BAUDRATE;               /* 24MHz晶振 */
////    RI = 0;
//}


///********************************************************************************
//* Function Name  : xWriteCH395Cmd
//* Description    : 向CH395写命令
//* Input          : cmd 8位的命令码
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void xWriteCH395Cmd(UINT8 cmd)                                      
//{
//	S2CON &= ~S2TI;
//    S2BUF = SER_SYNC_CODE1;                                           /* 启动操作的第1个串口同步码 */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2TI;
//    S2BUF = SER_SYNC_CODE2;                                           /* 启动操作的第2个串口同步码 */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2TI;
//    S2BUF = cmd;                                                      /* 串口输出 */
//    while((S2CON & S2TI) == 0) ;
//	
//	S2CON &= ~S2RI;
//}

///********************************************************************************
//* Function Name  : xWriteCH395Data
//* Description    : 向CH395写数据
//* Input          : mdata 8位数据
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void  xWriteCH395Data(UINT8 mdata)
//{                                                                    	/* 向CH395写数据 */
//    S2CON &= ~S2TI;
//    S2BUF = mdata;                                                    /* 串口输出 */
//    while((S2CON & S2TI) == 0);
//}

///********************************************************************************
//* Function Name  : xReadCH395Data
//* Description    : 从CH395读数据
//* Input          : None
//* Output         : None
//* Return         : 8位数据
//*******************************************************************************/
//UINT8  xReadCH395Data(void)                                          /* 从CH395读数据 */
//{
//    UINT32 xdata i;
//    
//    for(i = 0; i < 500000; i ++) 
//    {  
//        /* 计数防止超时 */
//        if(S2CON & S2RI) 
//        {  
//            /* 串口接收到 */
//			S2CON &= ~S2RI;
//            return(S2BUF);                                            /* 串口输入 */
//        }
//    }
//    return(0);                                                       /* 不应该发生的情况 */
//}


