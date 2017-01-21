#ifndef __PCA_H
#define __PCA_H

#include "types.h"


#define T1000Hz  (22118400L / 12 / 1000) 		//每秒钟1000次, 即1MS一次


extern  uint16_t   PCA_Value;


void Pca_Init(void);



#endif

