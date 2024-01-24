

#ifndef EEPROM_H_
#define EEPROM_H_




#include "../../MCAL/Header/I2C.h"

void EEPROM_init(void);  
void EEPROM_send(unsigned short Add,unsigned char Data);  
unsigned char EEPROM_recieve(unsigned short Add);     



#endif

