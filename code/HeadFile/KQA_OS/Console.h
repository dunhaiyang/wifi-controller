#ifndef __CONSOLE_H_
#define __CONSOLE_H_


#include "OS_HAL.h"


#define MENU_COMMAND_MAX		10						// ָ����������ַ���

#define PROMPT_MAX				10						// ������ʾ��


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
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;
	
	// �����ӿ�
	//
	ProcVoid_Void				run;					// Console����(��Ҫ�����Եص���)
	
	ProcUint8P_Void				print;					// ��ӡ�ַ������ն�(������)
	
	ProcUint8P_Void				printLn;				// ��ӡ�ַ������ն�(����)
	
	ProcUint8PUint16_Void		printDec;				// ��ӡ����,��10���Ƶ���ʽ
	
	ProcUint8PUint16_Void		printDecLn;				// ��ӡ"�ַ����� ����(��10���Ƶ���ʽ)"
	
	ProcVoidPUint8_Void			registerMenu ;			// ע���ն�ָ��
	
	ProcUint8P_Void				setPrompt;				// ����������ʾ��
	
	// ˽�г�Ա����
	//
	uint8_t						prompt[PROMPT_MAX + 1];	// ������ʾ��
	
	Menu						*menu;					// ָ��ṹ��
	
	uint8_t						menuEntries;			// ָ��ṹ����ָ������
	
}Console;


void Console_Init(void *self);


#endif

