#ifndef __EEPROM_H_
#define __EEPROM_H_

#include "types.h"



void Sector_Erase(uint16_t add);



uint8_t Byte_Read(uint16_t add);



void Byte_Program(uint16_t add, uint8_t ch);



#endif