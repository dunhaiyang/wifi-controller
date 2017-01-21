#include "NRF905.h"


//--- 芯片配置字结构
//
typedef struct RFConfig
{
	uint8_t n;
	uint8_t buf[ 10 ];
} RFConfig;


//--- 芯片配置常量
//
RFConfig RxTxConf =
{
	10,
	RFConfig_Bit0, 	RFConfig_Bit1, 	RFConfig_Bit2, 	RFConfig_Bit3, 	RFConfig_Bit4,
	RFConfig_Bit5, 	RFConfig_Bit6, 	RFConfig_Bit7, 	RFConfig_Bit8, 	RFConfig_Bit9	
};


// 初始化无线模块
//
void NRF905_SetWireLess(uint8_t wirelessChannel)
{
	uint8_t i;
	
	PWR_UP = 0; PWR_UP = 0;

	NRF905_InitIO(); 														// Initialize IO port
	NRF905_fSetRF(wirelessChannel);
	NRF905_Config905();														// Config nRF905 module
	CSN = 0;																// Spi enable for write a spi command	
	Spi_Write( WTA );														// Write TX Address  command
	for( i = 0; i < 4; i ++ )												// Write 4 bytes address
	{ Spi_Write( RxTxConf.buf[ i + 5 ] ); }	
	CSN = 1;																// Spi disable
	NRF905_SetRxMode();														// Set nRF905 in Rx mode
}


void NRF905_InitIO(void)
{
	CSN=1;						// Spi 	disable						
	SCK=1;						// Spi clock line init high
//	nrf905_DR=1;				// Init DR for input
//	AM=1;						// Init AM for input
	
	// 设置nf905无线模块工作模式为standby模式(PWR_UP = 1, TRX_CE = 0, TX_EN = x)
	// RX模式(PWR_UP = 1, TRX_CE = 1, TX_EN = 0)
	// TX模式(PWR_UP = 1, TRX_CE = 1, TX_EN = 1)
	//
	PWR_UP=1;					// nRF905 power on
	TRX_CE=0;					// Set nRF905 in standby mode
	TX_EN=0;					// set radio in Rx mode	
}

 //设置无线通讯测试(通讯频道)
//
void NRF905_fSetRF(uint8_t wirelessChannel)
{
//	uint8_t cTmp;
//
//	cTmp = (WirelessChannel % 20);
//	cTmp = cTmp * 13;		//没频段间隔1.3MHZ
//	cTmp = cTmp + 2;
//	if( cTmp >= 256 ) { cTmp -= 256; RxTxConf.buf[ 1 ] += 1; }
//	RxTxConf.buf[ 0 ] = cTmp;		// freq=422.4 + 84/10 = 423 + (DRV_FZ * 13) / 10 MHz 

	uint8_t  i;
	uint16_t x;

	//--- 调节频率
	i = (wirelessChannel % 38);
	x = i * 13;										//每频段间隔1.3MHZ
	x += 2;											//频率偏差 0.2MHZ
	RxTxConf.buf[ 0 ] = x % 256;					// freq=422.4 + 84/10 = 423 + (DRV_FZ * 13) / 10 MHz 
	RxTxConf.buf[ 1 ] &= 0xFE;   					//CH_NO[8]=0
	if( x >= 256 ) { RxTxConf.buf[ 1 ] |= 0x01; } 	//CH_NO[8]=1

	RxTxConf.buf[ 5 ] = wirelessChannel;			// 无线信道
}


void NRF905_Config905(void)
{
	uint8_t i;					
	CSN=0;								// Spi enable for write a spi command
	Spi_Write(WC);						// Write config command
	for (i=0; i<RxTxConf.n; i++)		// Write configration words
	{
		Spi_Write(RxTxConf.buf[i]);
	}
	CSN = 1;							// Disable Spi
}

void Delay650us()						// @22.1184MHz
{
	uint8_t i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 14;
	j = 248;
	do
	{
		while (--j);
	} while (--i);
}


void NRF905_Delay(uint8_t n)
{
//	uint16_t i;
//	while(n--)
//        for(i=0; i<80; i++);
    while (n--)
        Delay650us();
}


bool NRF905_HaveDataToRead(void)
{
	nrf905_DR = 1; _nop_(); _nop_();
	
	if(nrf905_DR)                                           									// 无线数据非空，准备接收处理 
	{
		return 1;
	}
	return 0;
}


void __TxPacket(uint8_t *send_buf, uint8_t *send_add)
{
	uint8_t i;

	CSN=0;						// Spi enable for write a spi command
	Spi_Write(WTP);				// Write payload command
	for (i=0;i<32;i++)
	{
		Spi_Write(send_buf[i]);// Write 32 bytes Tx data
	}
	CSN=1;						// Spi disable
	NRF905_Delay(1);
	CSN=0;						// Spi enable for write a spi command
	Spi_Write(WTA);				// Write address command
	for (i=0; i<4; i++)			// Write 4 bytes address
	{
		Spi_Write(send_add[i]);
	}
	CSN=1;						// Spi disable
	TRX_CE=1;					// Set TRX_CE high,start Tx data transmission
	NRF905_Delay(1);			// while (DR!=1);
	TRX_CE=0;					// Set TRX_CE low
}



void NRF905_TxPacket(uint8_t *send_buf)
{
	uint8_t	tmpSendAddress[4];
	
	// 目的中继是0，直接发送给设备
    //
    if (send_buf[4] == 0)
    {
        tmpSendAddress[0] = send_buf[0];	tmpSendAddress[1] = send_buf[1];
		
		tmpSendAddress[2] = 0xCC;			tmpSendAddress[3] = 0xCC;
    }
    // 目的中继不为0，发送给中继器
    //
    else
    {
        tmpSendAddress[0] = send_buf[4];	tmpSendAddress[1] = 0xCC;
		
		tmpSendAddress[2] = 0xCC;			tmpSendAddress[3] = 0xCE;
    }
    NRF905_SetTxMode();                     		// 设置无线为发送模式
    
    __TxPacket(send_buf, tmpSendAddress);     		// 发送无线数据
    
    Delay1ms(3);                            		// 延时, 这个？？？？？
	
    NRF905_SetRxMode();                     		// 重新设置为接收模式
}



void NRF905_RxPacket(uint8_t *receive_buf)
{
	uint8_t i;	

	TRX_CE=0;					                // Set nRF905 in standby mode	
	CSN=0;						                // Spi enable for write a spi command
	Spi_Write(RRP);				                // Read payload command	
	for (i = 0; i < 32; i++)
	{
		receive_buf[i] = Spi_Read();			// Read data and save to buffer
	}
	CSN=1;						                // Disable spi
	while(nrf905_DR||AM);	
	TRX_CE=1;			
}



void NRF905_SetTxMode(void)				
{	
	TX_EN=1;
	TRX_CE=0;
	NRF905_Delay(1); 					// delay for mode change(>=650us)
}
				


void NRF905_SetRxMode(void)
{
	TX_EN=0;
	TRX_CE=1;
	NRF905_Delay(1); 					// delay for mode change(>=650us)				
}







