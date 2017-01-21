#ifndef __PIN_H_
#define __PIN_H_


#include "STC15F2K60S2.h"


// --- �Ƶ����Ŷ���
//
sbit    	PWR_YELLOW		= P4^5;		// �Ƶ�
sbit    	WLS_BLUE		= P3^6;     // ����
sbit    	COM_GREEN		= P3^7;		// �̵�


// --- �����������Ŷ���
//
sbit    	PP				= P4^7;     // �͵�ƽ�죬�ߵ�ƽ����



// --- NRF905���Ŷ���
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


// --- CH395ģ�飨SPI������
//
sbit		CH395_INT_WIRE	= P3^2;

sbit		CH395_SPI_SCS	= P1^2;
sbit		CH395_SPI_SDI	= P1^3;
sbit		CH395_SPI_SDO	= P1^4;
sbit		CH395_SPI_SCK	= P1^5;



#endif


