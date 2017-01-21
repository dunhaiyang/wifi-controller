#ifndef __OS_HAL_H_
#define __OS_HAL_H_


// =======================  ����ģ��ͷ�ļ� ========================
//

#include "Timer0.h"													// �ṩʱ�ӵδ�


#include "Pca.h"													// �ṩ��ʱ���ܣ���ͨѶ��ʱ��ʱ��


#include "Uart1.h"													// �ṩxshellα�ն�ͨѶ�ӿ�


#include "Eeprom.h"													// �ṩEEPROM�ӿ�


#include "NRF905.h"													// �ṩzigbeeͨѶ�ӿ�


#include "UsrC210.h"												// �ṩwifiͨѶ�ӿ�


#include "Ch395Cmd.h"												// �ṩnetworkͨѶ�ӿ�



// =======================  �ײ�������ܳ��� ========================
//

#define HAL_HARDWARE_INIT()						do {				\
													IoPort_Init(); 	\
													Pca_Init(); 	\
												}while(0)						// Ӳ����ʼ��

												
#define HAL_SYSTEMTIME_INIT						Timer0_Init						// ��ʱ��0��ʼ��


#define HAL_SYSTEMTIME							Timer0_SystemTicks				// ��ȡ��ʱ��0ά����ϵͳ�δ�


#define HAL_REBOOT								Reboot							// ����оƬ


#define HAL_WATCHDOG							ClearWatchdog					// ���Ź�


#define HAL_DELAY1MS							Delay1ms						// �ӳ�1����


#define HAL_LED_GREEN							LedGreen						// �̵ƽӿ�


#define HAL_LED_BLUE							LedBlue							// ���ƽӿ�


#define HAL_LED_YELLOW							LedYellow						// �Ƶƽӿ�


#define HAL_BEEP_ACTION							BeepAction						// ����������


#define HAL_CONSOLE_INIT						Uart1_Init						// ����1��ʼ��


#define HAL_CONSOLE_AVAILABLE					Uart1_Available					// ����1�����ݿɶ�


#define HAL_CONSOLE_SENDBYTE					Uart1_SendByte					// ����1����һ���ֽ�


#define HAL_CONSOLE_SENDSTRING					Uart1_SendString				// ����1�����ַ�������


#define HAL_PARAMETER_READBYTE					Byte_Read						// EEPROM��ȡ


#define HAL_PARAMETER_WRITEBYTE					Byte_Program					// EEPROM����


#define HAL_PARAMETER_ERASE						Sector_Erase					// EEPROM����


#define HAL_WIRELESS_INIT						NRF905_SetWireLess				// NRF905���߳�ʼ��


#define HAL_WIRELESS_AVAILABE					NRF905_HaveDataToRead			// NRF905���������ݿɶ�


#define HAL_WIRELESS_SEND						NRF905_TxPacket					// NRF905�������ݣ�һ��32�ֽڣ�


#define HAL_WIRELESS_RECEIVE					NRF905_RxPacket					// NRF905�������ݣ�һ��32�ֽڣ�


#define HAL_WIFI_INIT							UsrC210_Init					// USR-C210wifi��ʼ��


#define HAL_WIFI_GETUART						UsrC210_GetUart					// ��ȡ���ڲ�����


#define HAL_WIFI_LINKAP							UsrC210_LinkAP					// USR-C210wifi����վ��


#define HAL_WIFI_QUERYMAC						UsrC210_QueryMac				// USR-C210wifi��ѯMAC��ַ


#define HAL_WIFI_REBOOT							UsrC210_Reboot					// USR-C210wifi���� 


#define HAL_WIFI_SCAN							UsrC210_Scan					// USR-C210wifiɨ�� 


#define HAL_WIFI_HOTSPOTSTATUS					UsrC210_HotspotStatus			// USR-C210wifi�鿴�ȵ�����״̬


#define HAL_WIFI_SERVERSTATUS					UsrC210_ServerStatus			// USR-C210wifi�鿴���ӷ�����״̬


#define HAL_WIFI_DHCP							UsrC210_Dhcp					// USR-C210wifi�鿴DHCP����


#define HAL_WIFI_PING							UsrC210_Ping					// USR-C210wifi ping


#define HAL_WIFI_CONNECTSERVER					UsrC210_connectServer			// USR-C210wifi���ӷ����� 


#define HAL_WIFI_DISCONNECTSERVER 				UsrC210_disconnectServer		// USR-C210wifi�Ͽ����ӷ����� 


#define HAL_WIFI_SEND							Uart2_SendNString				// USR-C210wifi��������


#define HAL_WIFI_RECEIVE						Uart2_Mode0_ReceiveString		// USR-C210wifi��������


#define HAL_NETWORK_CH395REBOOT					CH395CMDReset					// CH395����������CH395��Ȼ������IP��ַ�����ص�ַ�������ַ��


#define HAL_NETWORK_CH395SETIPADDR				CH395CMDSetIPAddr				// CH395����IP��ַ


#define HAL_NETWORK_CH395SETGATEWAY				CH395CMDSetGWIPAddr				// CH395�������ص�ַ


#define HAL_NETWORK_CH395SETMASKADDR			CH395CMDSetMASKAddr				// CH395���������ַ


#define HAL_NETWORK_CH395GETMACADDR				CH395CMDGetMACAddr				// CH395��ȡMAC��ַ


#define HAL_NETWORK_CH395INIT					CH395CMDInitCH395				// CH395��ʼ��CH395������IP��ַ�����ص�ַ�������ַ��Ȼ���ʼ����


#define HAL_NETWORK_CH395SETSOCKETTYPE			CH395SetSocketProtType			// CH395����socket������
	

#define HAL_NETWORK_CH395SETSOCKETSOURCEPORT	CH395SetSocketSourPort			// CH395����socketԴ�˿�


#define HAL_NETWORK_CH395SETSOCKETDESIP			CH395SetSocketDesIP				// CH395����Զ��IP��ַ


#define HAL_NETWORK_CH395SETSOCKETDESPORT		CH395SetSocketDesPort			// CH395����Զ�̶˿�


#define HAL_NETWORK_CH395SOCKETOPEN				CH395OpenSocket					// CH395������


#define HAL_NETWORK_CH395SENDDATA				CH395SendData					// CH395��������


#define HAL_NETWORK_CH395CLEARRECEIVEBUFFER		CH395ClearRecvBuf				// CH295��ս��ջ�����


#define HAL_NETWORK_CH395GETGLOBALINT_ALL		CH395CMDGetGlobIntStatus_ALL	// CH395��ȡSOCKETȫ���ж�


#define HAL_NETWORK_CH395GETSOCKETINT			CH395GetSocketInt				// CH395��ȡSOCKET�ж�



// =======================  �����ӿ��������� ========================
//
typedef struct
{
	uint8_t *para1;
	
	uint8_t *para2;
	
}Uint8P_Uint8P;


// --------------  ����Ϊ (void)
//
typedef void (*ProcVoid_Void)(void);


typedef bool (*ProcVoid_Bool)(void);


typedef uint32_t (*ProcVoid_Uint32)(void);


// --------------  ����Ϊ (void*)
//
typedef void (*ProcVoidP_Void)(void *);


// --------------  ����Ϊ (void*, uint8_t)
//
typedef void (*ProcVoidPUint8_Void)(void *, uint8_t);


// --------------  ����Ϊ (uint8_t)
//
typedef void (*ProcUint8_Void)(uint8_t);


// --------------  ����Ϊ (uint8_t, uint8_t)
//
typedef void (*ProcUint8Uint8_Void)(uint8_t, uint8_t);


// --------------  ����Ϊ (uint8_t, uint16_t)
//
typedef void (*ProcUint8Uint16_Void)(uint8_t, uint16_t);


// --------------  ����Ϊ (uint8_t *)
//
typedef void (*ProcUint8P_Void)(uint8_t *);


typedef uint16_t (*ProcUint8P_Uint16)(uint8_t *);


// --------------  ����Ϊ (uint8_t *, uint16_t)
//
typedef void (*ProcUint8PUint16_Void)(uint8_t *, uint16_t);


// --------------  ����Ϊ (uint16_t)
//
typedef void (*ProcUint16_Void)(uint16_t);


typedef uint8_t (*ProcUint16_Uint8)(uint16_t);


// --------------  ����Ϊ (uint16_t, uint8_t)
//
typedef void (*ProcUint16Uint8_Void)(uint16_t, uint8_t);


// --------------  ����Ϊ (uint32_t)
//
typedef void (*ProcUint32_Void)(uint32_t);



// �Ƚ����������Ĳ�ֵ
//
#define HAL_DIFFERENT2_TIME(now, past)	((now >= past)? (now - past):(~past + now + 1))		// ˫�ֽڵıȽ�


#define HAL_DIFFERENT4_TIME(now, past)	((now >= past)? (now - past):(~past + now + 1))		// ���ֽڵıȽ�


// ����ģ��ĺ�
//
#define STATIC_DRIVER_INIT(DriverType, DriverName)	static DriverType DriverName = {DriverType##_Init}



#endif



