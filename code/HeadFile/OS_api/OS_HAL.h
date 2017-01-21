#ifndef __OS_HAL_H_
#define __OS_HAL_H_


// =======================  包含模块头文件 ========================
//

#include "Timer0.h"													// 提供时钟滴答


#include "Pca.h"													// 提供计时功能（如通讯超时计时）


#include "Uart1.h"													// 提供xshell伪终端通讯接口


#include "Eeprom.h"													// 提供EEPROM接口


#include "NRF905.h"													// 提供zigbee通讯接口


#include "UsrC210.h"												// 提供wifi通讯接口


#include "Ch395Cmd.h"												// 提供network通讯接口



// =======================  底层基本功能抽象 ========================
//

#define HAL_HARDWARE_INIT()						do {				\
													IoPort_Init(); 	\
													Pca_Init(); 	\
												}while(0)						// 硬件初始化

												
#define HAL_SYSTEMTIME_INIT						Timer0_Init						// 定时器0初始化


#define HAL_SYSTEMTIME							Timer0_SystemTicks				// 获取定时器0维护的系统滴答


#define HAL_REBOOT								Reboot							// 重启芯片


#define HAL_WATCHDOG							ClearWatchdog					// 看门狗


#define HAL_DELAY1MS							Delay1ms						// 延迟1毫秒


#define HAL_LED_GREEN							LedGreen						// 绿灯接口


#define HAL_LED_BLUE							LedBlue							// 蓝灯接口


#define HAL_LED_YELLOW							LedYellow						// 黄灯接口


#define HAL_BEEP_ACTION							BeepAction						// 蜂鸣器动作


#define HAL_CONSOLE_INIT						Uart1_Init						// 串口1初始化


#define HAL_CONSOLE_AVAILABLE					Uart1_Available					// 串口1有数据可读


#define HAL_CONSOLE_SENDBYTE					Uart1_SendByte					// 串口1发送一个字节


#define HAL_CONSOLE_SENDSTRING					Uart1_SendString				// 串口1发送字符串函数


#define HAL_PARAMETER_READBYTE					Byte_Read						// EEPROM读取


#define HAL_PARAMETER_WRITEBYTE					Byte_Program					// EEPROM保存


#define HAL_PARAMETER_ERASE						Sector_Erase					// EEPROM擦除


#define HAL_WIRELESS_INIT						NRF905_SetWireLess				// NRF905无线初始化


#define HAL_WIRELESS_AVAILABE					NRF905_HaveDataToRead			// NRF905无线有数据可读


#define HAL_WIRELESS_SEND						NRF905_TxPacket					// NRF905发送数据（一次32字节）


#define HAL_WIRELESS_RECEIVE					NRF905_RxPacket					// NRF905接收数据（一次32字节）


#define HAL_WIFI_INIT							UsrC210_Init					// USR-C210wifi初始化


#define HAL_WIFI_GETUART						UsrC210_GetUart					// 获取串口波特率


#define HAL_WIFI_LINKAP							UsrC210_LinkAP					// USR-C210wifi连接站点


#define HAL_WIFI_QUERYMAC						UsrC210_QueryMac				// USR-C210wifi查询MAC地址


#define HAL_WIFI_REBOOT							UsrC210_Reboot					// USR-C210wifi重启 


#define HAL_WIFI_SCAN							UsrC210_Scan					// USR-C210wifi扫描 


#define HAL_WIFI_HOTSPOTSTATUS					UsrC210_HotspotStatus			// USR-C210wifi查看热点连接状态


#define HAL_WIFI_SERVERSTATUS					UsrC210_ServerStatus			// USR-C210wifi查看连接服务器状态


#define HAL_WIFI_DHCP							UsrC210_Dhcp					// USR-C210wifi查看DHCP参数


#define HAL_WIFI_PING							UsrC210_Ping					// USR-C210wifi ping


#define HAL_WIFI_CONNECTSERVER					UsrC210_connectServer			// USR-C210wifi连接服务器 


#define HAL_WIFI_DISCONNECTSERVER 				UsrC210_disconnectServer		// USR-C210wifi断开连接服务器 


#define HAL_WIFI_SEND							Uart2_SendNString				// USR-C210wifi发送数据


#define HAL_WIFI_RECEIVE						Uart2_Mode0_ReceiveString		// USR-C210wifi接收数据


#define HAL_NETWORK_CH395REBOOT					CH395CMDReset					// CH395重启（重启CH395，然后设置IP地址。网关地址。掩码地址）


#define HAL_NETWORK_CH395SETIPADDR				CH395CMDSetIPAddr				// CH395设置IP地址


#define HAL_NETWORK_CH395SETGATEWAY				CH395CMDSetGWIPAddr				// CH395设置网关地址


#define HAL_NETWORK_CH395SETMASKADDR			CH395CMDSetMASKAddr				// CH395设置掩码地址


#define HAL_NETWORK_CH395GETMACADDR				CH395CMDGetMACAddr				// CH395获取MAC地址


#define HAL_NETWORK_CH395INIT					CH395CMDInitCH395				// CH395初始化CH395（设置IP地址。网关地址。掩码地址，然后初始化）


#define HAL_NETWORK_CH395SETSOCKETTYPE			CH395SetSocketProtType			// CH395设置socket的类型
	

#define HAL_NETWORK_CH395SETSOCKETSOURCEPORT	CH395SetSocketSourPort			// CH395设置socket源端口


#define HAL_NETWORK_CH395SETSOCKETDESIP			CH395SetSocketDesIP				// CH395设置远程IP地址


#define HAL_NETWORK_CH395SETSOCKETDESPORT		CH395SetSocketDesPort			// CH395设置远程端口


#define HAL_NETWORK_CH395SOCKETOPEN				CH395OpenSocket					// CH395打开连接


#define HAL_NETWORK_CH395SENDDATA				CH395SendData					// CH395发送数据


#define HAL_NETWORK_CH395CLEARRECEIVEBUFFER		CH395ClearRecvBuf				// CH295清空接收缓冲区


#define HAL_NETWORK_CH395GETGLOBALINT_ALL		CH395CMDGetGlobIntStatus_ALL	// CH395获取SOCKET全局中断


#define HAL_NETWORK_CH395GETSOCKETINT			CH395GetSocketInt				// CH395获取SOCKET中断



// =======================  公共接口数据类型 ========================
//
typedef struct
{
	uint8_t *para1;
	
	uint8_t *para2;
	
}Uint8P_Uint8P;


// --------------  参数为 (void)
//
typedef void (*ProcVoid_Void)(void);


typedef bool (*ProcVoid_Bool)(void);


typedef uint32_t (*ProcVoid_Uint32)(void);


// --------------  参数为 (void*)
//
typedef void (*ProcVoidP_Void)(void *);


// --------------  参数为 (void*, uint8_t)
//
typedef void (*ProcVoidPUint8_Void)(void *, uint8_t);


// --------------  参数为 (uint8_t)
//
typedef void (*ProcUint8_Void)(uint8_t);


// --------------  参数为 (uint8_t, uint8_t)
//
typedef void (*ProcUint8Uint8_Void)(uint8_t, uint8_t);


// --------------  参数为 (uint8_t, uint16_t)
//
typedef void (*ProcUint8Uint16_Void)(uint8_t, uint16_t);


// --------------  参数为 (uint8_t *)
//
typedef void (*ProcUint8P_Void)(uint8_t *);


typedef uint16_t (*ProcUint8P_Uint16)(uint8_t *);


// --------------  参数为 (uint8_t *, uint16_t)
//
typedef void (*ProcUint8PUint16_Void)(uint8_t *, uint16_t);


// --------------  参数为 (uint16_t)
//
typedef void (*ProcUint16_Void)(uint16_t);


typedef uint8_t (*ProcUint16_Uint8)(uint16_t);


// --------------  参数为 (uint16_t, uint8_t)
//
typedef void (*ProcUint16Uint8_Void)(uint16_t, uint8_t);


// --------------  参数为 (uint32_t)
//
typedef void (*ProcUint32_Void)(uint32_t);



// 比较两个变量的差值
//
#define HAL_DIFFERENT2_TIME(now, past)	((now >= past)? (now - past):(~past + now + 1))		// 双字节的比较


#define HAL_DIFFERENT4_TIME(now, past)	((now >= past)? (now - past):(~past + now + 1))		// 四字节的比较


// 定义模块的宏
//
#define STATIC_DRIVER_INIT(DriverType, DriverName)	static DriverType DriverName = {DriverType##_Init}



#endif



