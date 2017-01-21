#include "SPI.h"

//
//
uint8_t 	bdata 		DATA_BUF; 		// 数据忙标志
sbit	flag			= DATA_BUF^7; 	// 数据忙标志
sbit	flag1			= DATA_BUF^0;


 
void Spi_Write(uint8_t  byte)
{
	uint8_t i;	
    
	DATA_BUF=byte;				// Put function's parameter into a bdata variable		
	for (i=0;i<8;i++)			// Setup byte circulation bits
	{	
		
		if (flag)				// Put DATA_BUF.7 on data line
			MOSI=1;
		else
			MOSI=0;
		SCK=1;					// Set clock line high
		DATA_BUF=DATA_BUF<<1;	// Shift DATA_BUF
		SCK=0;					// Set clock line low 
	}
}



uint8_t Spi_Read(void)
{
	uint8_t i;
	
	for (i=0;i<8;i++)			// Setup byte circulation bits
	{	
		DATA_BUF=DATA_BUF<<1;	// Right shift DATA_BUF
		SCK=1;					// Set clock line high
		if (MISO)
			flag1=1;			// Read data
		else
			flag1=0;
							
		
		SCK=0;					// Set clock line low
	}
	return DATA_BUF;			// Return function parameter
}