
// === α�նˣ�����̨��ָ��
//
#include "Middleware_Menu.h"


// === ��ʵʱ����
//
#include "Middleware_Task.h"


// === �㲥����
//
#include "Middleware_Boardcast.h"


// === ���ߣ�zigbee��
//
#include "Middleware_Wireless.h"


// === ���磨wifi����enthernet��
//
#include "Middleware_Socket.h"


/*
	=====================  4. settup��ִֻ��һ�Σ�  =====================
*/

void setup(void)
{
	// ϵͳ��ʼ��
	//
	App_Hal_Api.init();																			// ��ʼ��IAP15����ϵͳ
	
	App_Hal_Api.console->registerMenu(menu, sizeof(menu)/sizeof(menu[0]));						// ע��α�ն�ָ��
	
	App_Hal_Api.scheduler->registerTask(task, sizeof(task)/sizeof(task[0]));					// ע������

#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->registerErrorFunction(MiddlewareSocket_NetworkError);					// ע���������ص�����
	
#endif
	
	// APP��ʼ��
	//
	ControlerInfo_Init();																		// ������������ʼ��
	
	NormalDeviceInfo_Init();																	// ��ͨ�豸�б��ʼ��
	
	SpecialDeviceInfo_Init();																	// �����豸�б��ʼ��
	
	
	// ���ѿ�������ʼ�����
	//
	App_Hal_Api.led->setTime(ALL_LED, 1000);													// ����1000ms
	
	App_Hal_Api.beep->setTime(50);																// ��������50ms
}



/*
	====================  5. loop����ѭ����  =========================
*/
void fast_loop(void)
{
	App_Hal_Api.led->run();																		// ִ�е�����
	
	App_Hal_Api.beep->run();																	// ִ�з���������
	
#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->run();																	// ִ������ײ㺯��
	
	MiddlewareBoardcast_FastTask();																// ���չ㲥��������
	
#endif
	
	MiddlewareWireless_FastTask();																// ����������������
	
	MiddlewareSocket_FastTask();																// ����������������
}


void loop(void)
{
	static uint32_t loopTime = 0;
	
	fast_loop();
	
	if (HAL_DIFFERENT4_TIME(App_Hal_Api.scheduler->milliseconds(), loopTime) >= 5)
	{
		loopTime = App_Hal_Api.scheduler->milliseconds();
		
		App_Hal_Api.scheduler->ticksIncrease();
		
//		if (App_Hal_Api.scheduler->ticks % 200 == 0)
//		{
//			printf("milliseconds = %lu\r\n", App_Hal_Api.scheduler->milliseconds());
//		}
	}
	App_Hal_Api.scheduler->run();
}


/*
	====================  6. main macro  ======================
*/
APP_HAL_IAP15_MAIN()

