#ifndef __CONSOLE_H_
#define __CONSOLE_H_


#include "OS_HAL.h"


#define MENU_COMMAND_MAX		10						// 指令名称最大字符数

#define PROMPT_MAX				10						// 命令提示符


typedef struct
{
	uint8_t 					command[MENU_COMMAND_MAX + 1];
	
	ProcVoidP_Void					func;
	
}Menu;


enum
{
	HEX,
	
	DEC,
};


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;
	
	// 公共接口
	//
	ProcVoid_Void				run;					// Console任务(需要周期性地调用)
	
	ProcUint8P_Void				print;					// 打印字符串到终端(不换行)
	
	ProcUint8P_Void				printLn;				// 打印字符串到终端(换行)
	
	ProcUint8PUint16_Void		printDec;				// 打印数字,以10进制的形式
	
	ProcUint8PUint16_Void		printDecLn;				// 打印"字符串： 数字(以10进制的形式)"
	
	ProcVoidPUint8_Void			registerMenu ;			// 注册终端指令
	
	ProcUint8P_Void				setPrompt;				// 设置命令提示符
	
	// 私有成员变量
	//
	uint8_t						prompt[PROMPT_MAX + 1];	// 命令提示符
	
	Menu						*menu;					// 指令结构体
	
	uint8_t						menuEntries;			// 指令结构体中指令数量
	
}Console;


void Console_Init(void *self);


#endif

