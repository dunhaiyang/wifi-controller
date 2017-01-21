#ifndef __SCHEDULE_H_
#define __SCHEDULE_H_


#include "OS_HAL.h"


typedef struct
{
	ProcVoid_Bool				function;						/// ������Ⱥ���
	
	uint16_t					intervalTicks;					/// �δ���
	
	uint32_t					maxLimitMilliseconds;			/// ����ӳ�ִ��ʱ�䣨����Ϊ��λ��
	
	/// ���µĳ�Ա������������������ȵ��㷨������������͵ı���ʱ���ó�ʼ��(�������β�͵�ȷ�����ţ��Ժ���ֲ��c++�����������Ż�)
	///
	uint16_t					__intervalTicks;				/// ������Ⱥ���ִ��ʱ�ĵδ���
	
	uint32_t					__maxLimitMilliseconds;			/// ������Ⱥ���ִ��ʱ��ϵͳ������������Ϊ��λ��
	
}Task;


typedef struct
{
	// ˽�нӿ�
	//
	ProcVoidP_Void				init;
	
	// �����ӿ�
	//
	ProcVoid_Void				run;							/// Schedulerִ���߼�
	
	ProcVoidPUint8_Void			registerTask;					/// ��һ��������Task*�� �ڶ���������task����
	
	ProcUint16_Void				delayMilliseconds;				/// ���뼶����ʱ
	
	ProcVoid_Uint32				milliseconds;					/// ϵͳ����������ϵͳ������
	
	ProcVoid_Void				ticksIncrease;					/// ���������δ���
	
	// ˽�г�Ա����
	//
	uint16_t					ticks;							/// �δ���
	
	Task						*tasks;							/// ����
	
	uint8_t						taskEntries;					/// �������
	
}Scheduler;


void Scheduler_Init(void *self);



#endif

