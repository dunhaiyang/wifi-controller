#ifndef __PIN_H_
#define __PIN_H_


#include "STC15F2K60S2.h"


// --- 灯的引脚定义
//
sbit    	PWR_YELLOW		= P4^5;		// 黄灯
sbit    	WLS_BLUE		= P3^6;     // 蓝灯
sbit    	COM_GREEN		= P3^7;		// 绿灯


// --- 蜂鸣器的引脚定义
//
sbit    	PP				= P4^7;     // 低电平响，高电平不响



// --- NRF905引脚定义
//
sbit		TX_EN			= P4^3;
sbit		PWR_UP			= P4^4;
sbit		CD				= P2^0;
sbit		SCK				= P2^1;
sbit		MISO			= P2^2;
sbit		MOSI			= P2^3;
sbit		CSN				= P2^4;
sbit		nrf905_DR		= P2^5;
sbit		AM				= P2^6;
sbit		TRX_CE			= P2^7;


// --- CH395模块（SPI驱动）
//
sbit		CH395_INT_WIRE	= P3^2;

sbit		CH395_SPI_SCS	= P1^2;
sbit		CH395_SPI_SDI	= P1^3;
sbit		CH395_SPI_SDO	= P1^4;
sbit		CH395_SPI_SCK	= P1^5;



#endif


