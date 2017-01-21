#ifndef __TYPES_H_
#define __TYPES_H_

#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "Pin.h"

typedef char			int8_t;

typedef unsigned char 	uint8_t;

typedef int				int16_t;

typedef unsigned int 	uint16_t;

typedef long			int32_t;

typedef unsigned long 	uint32_t;

typedef bit				bool;


typedef struct
{
    uint8_t year;
    
    uint8_t month;
    
    uint8_t day;
    
    uint8_t week;
    
    uint8_t hour;
    
    uint8_t minute;
    
    uint8_t second;
    
}Time_TypeDef;


extern  Time_TypeDef SysTime;


#define BCD(n)  ((n / 10 << 4) + (n % 10))                      // 整数转化成BCD码

#define DCB(n)  (((n & 0xF0) >> 4) * 10 + (n & 0x0F))           // BCD码转化成整数


#define     Uart1_Debug



#define IoPort_Init()		do{								\
									AUXR = 0x54;			\ 
									P0M0 = 0; P0M1 = 0;		\					
									P1M0 = 0; P1M1 = 0;		\
									P2M0 = 0; P2M1 = 0;		\
									P3M0 = 0; P3M1 = 0;		\
									P4M0 = 0; P4M1 = 0;		\
									P5M0 = 0; P5M1 = 0;		\
									P6M0 = 0; P6M1 = 0;		\
							}while(0)


void InitLed(void);


void LedGreen(uint8_t action);


void LedBlue(uint8_t action);


void LedYellow(uint8_t action);


void InitBeep(void);


void BeepAction(uint8_t action);


void ClearWatchdog(void);
							
							
void Reboot(void);


void Delay1us(void);


void Delay1ms(uint16_t delay_n);


#endif