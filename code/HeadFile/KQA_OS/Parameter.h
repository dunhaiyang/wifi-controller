#ifndef __PARAMETER_H_
#define __PARAMETER_H_


#include "OS_HAL.h"


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;
	
	
	// �����ӿ�
	//
	ProcUint16_Void				erase;					// ����
	
	ProcUint16_Uint8			read;					// ��ȡ
	
	ProcUint16Uint8_Void		write;					// д��
	
}Parameter;


void Parameter_Init(void *self);



#endif

