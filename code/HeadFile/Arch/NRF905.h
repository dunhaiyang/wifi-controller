#ifndef __NRF905_H_
#define __NRF905_H_

#include "SPI.h"


#define WC				0x00			// Write configuration register command
#define RC				0x10 			// Read  configuration register command
#define WTP				0x20 			// Write TX Payload  command
#define RTP				0x21			// Read  TX Payload  command
#define WTA				0x22			// Write TX Address  command
#define RTA				0x23			// Read  TX Address  command
#define RRP				0x24			// Read  RX Payload  command

// <RF-Configuration-Register ������Ϣ>
//
#define CH_NO			0x4C//76		//freq=422.4+104/10=432.8MHz
//#define CH_NO			0x68//76		//freq=422.4+104/10=432.8MHz
//#define CH_NO			0x01//76		//freq=422.4+104/10=432.8MHz
#define HFREQ_PLL		0x0				//433Mhz / 868/915Mhz
#define PA_PWR			0x3				//����������
#define RX_RED_PWR		0x0				//���չ���
#define AUTO_RETRAN		0x0				//�Զ����·���
#define RX_AWF			0x4				//Rx ���ؽ��յ�ַ���
#define TX_AWF			0x4				//Tx ���ط��͵�ַ���
#define RX_PW			0x20			//Rx ���ؽ�����Ч���ݿ��
#define TX_PW			0x20			//Tx ���ط�����Ч���ݿ��
#define UP_CLK_FREQ		0x0				//���ʱ��Ƶ��
#define UP_CLK_EN		0x0				//���ʱ��ʹ��
#define XOF				0x3				//12MHz	//��������Ƶ��,���������ⲿ����ı��Ƶ������
#define CRC_EN			0x1				//CRCУ������
#define CRC_MODE		0x0				//CRCģʽ   0b0-8λCRCУ��λ;  0b1-16λCRCУ��λ ��Ĭ�ϣ�

#define RX_ADDR_Bit3	0xcf			//������ַ ����ֽ�
#define RX_ADDR_Bit2	0xcc
#define RX_ADDR_Bit1	0xcc
#define RX_ADDR_Bit0	0xcc			//������ַ ����ֽ�

// <��������Ϣ��ϳ�ÿ���ֽڵ�������Ϣ�������������޸�>
//
#define RFConfig_Bit0	(CH_NO & 0xff)
#define RFConfig_Bit1	(AUTO_RETRAN<<5 | RX_RED_PWR<<4 | PA_PWR<<2 | HFREQ_PLL<<1 | CH_NO>>8)
#define RFConfig_Bit2	(TX_AWF<<4 | RX_AWF)
#define RFConfig_Bit3	RX_PW
#define RFConfig_Bit4	TX_PW
#define RFConfig_Bit5	RX_ADDR_Bit0
#define RFConfig_Bit6	RX_ADDR_Bit1
#define RFConfig_Bit7	RX_ADDR_Bit2
#define RFConfig_Bit8	RX_ADDR_Bit3
#define RFConfig_Bit9	(CRC_MODE<<7 | CRC_EN<<6 | XOF<<3 | UP_CLK_EN<<2 | UP_CLK_FREQ)



#define	COM_LENGTH 		32

#define DRVCONFIGADDR	0

#define DRV_SNR_L   	0
#define DRV_SNR_H   	1
#define CMD_NAME	   	2
#define CMD_SNR	   		3
#define AIM_RELAY  		4
#define RELAY_1  		5
#define RELAY_2  		6
#define RELAY_3  		7
#define COM_DATA_S  	8
#define COM_DATA_E  	29
#define COM_CHECKSUM_L  30
#define COM_CHECKSUM_H  31


// ��ʼ������ģ��
//
void NRF905_SetWireLess(uint8_t wirelessChannel);


// ��ʼ��IO��
//
void NRF905_InitIO(void);


// ��ʼ���Ĵ����ṹ������
//
void NRF905_fSetRF(uint8_t wirelessChannel);


// ��������ģ��ļĴ���
//
void NRF905_Config905(void);


void NRF905_Delay(uint8_t n);


bool NRF905_HaveDataToRead(void);


void NRF905_TxPacket(uint8_t *send_buf);


void NRF905_RxPacket(uint8_t *receive_buf);


void NRF905_SetTxMode(void);
				

void NRF905_SetRxMode(void);







#endif