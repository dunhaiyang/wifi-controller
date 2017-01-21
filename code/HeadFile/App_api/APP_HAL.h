#ifndef __APP_HAL_H_
#define __APP_HAL_H_


#include "Hardware.h"

#include "Led.h"

#include "Beep.h"

#include "Console.h"

#include "Parameter.h"

#include "Wireless.h"

#include "Wifi.h"

#include "Network.h"

#include "Scheduler.h"


#define USING_MODULE_NETWORK


//#define USING_MODULE_WIFI


// main函数的宏定义
//
#ifndef APP_HAL_IAP15_MAIN

#define APP_HAL_IAP15_MAIN() int main (void) {	\
        setup();								\
        for(;;) loop();							\
        return 0;								\
    }

#endif






#endif
