

#include "../Header/EEPROM.h"

void EEPROM_init(void)    //initialize EEPROM
{  
	TWI_Init();	
}
void EEPROM_send(unsigned short Add,unsigned char Data)   //Write on EEPROM
{   	
	TWI_Start();
    TWI_Write((unsigned char)(0xA0|((Add & 0x0700)>>7)));  
	TWI_Write((unsigned char)(Add));
	TWI_Write(Data);
	TWI_Stop();
}

unsigned char EEPROM_recieve(unsigned short Add)   //Read from EEPROM
{
	TWI_Start();
	TWI_Write((unsigned char)(0xA0|((Add&0x0700)>>7)));  //1010 aaa0
	TWI_Write((unsigned char)(Add));
	TWI_Start();
	TWI_Write((unsigned char)(0xA0|((Add&0x0700)>>7)|1));  //1010 aaa0
	return TWI_Read_with_NACK();
	TWI_Stop();
}
