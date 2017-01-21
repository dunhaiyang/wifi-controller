#ifndef __CH395_UART_H_
#define __CH395_UART_H_



#include "Ch395Inc.h"
#include "types.h"

#define xCH395CmdStart( )         {CH395_SPI_SCS = 0;}
#define xEndCH395Cmd()            {CH395_SPI_SCS = 1;}

void xWriteCH395Cmd(UINT8 cmd);


void  xWriteCH395Data(UINT8 mdata);


UINT8  xReadCH395Data(void);




#endif
	
	