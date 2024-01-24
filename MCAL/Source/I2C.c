#include "../Header/I2C.h"
#include "../../STD/STDMACROS.h"
void TWI_Init(void){
    TWBR = 0x02;  //bit rate register
	TWSR = 0x00;  // status register initially = 0
    TWAR = 0b00000010; // my address = 0x01
    TWCR = (1<<TWEN);  // enable TWI 
}


void TWI_Start(void){
	//Enable interrupt flag + TWI START Condition Bit + TWI Enable Bit
	  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	
	while (readbit(TWCR,TWINT)==0);  //wait till interrupt flag = 0
}

void TWI_Stop(void){
	//Enable interrupt flag +  TWI STOP Condition Bit + TWI Enable Bit
     TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_Write(unsigned char data){  
TWDR =data;  //Fill Data Register With Data i want to send
TWCR = (1 << TWINT) | (1 << TWEN); //Enable interrupt flag + TWI Enable Bit
while(readbit(TWCR,TWINT)==0);  //wait till interrupt flag = 0
}

unsigned char  TWI_Read_with_ACK(void)
{
	//Enable Interrupt Flag  + TWI Enable Acknowledge Bit +  TWI Enable Bit
 TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
 	while(readbit(TWCR,TWINT)==0); //wait till interrupt flag = 0
	return TWDR; //retuen data registers;
}
	
unsigned char  TWI_Read_with_NACK(void)
{
	//Enable Interrupt Flag  + TWI Enable Bit
 TWCR = (1 << TWINT) | (1 << TWEN); 
 	while(readbit(TWCR,TWINT)==0);   //wait till interrupt flag = 0
	return TWDR; //return data registers
}

unsigned char TWI_Status(void)
{
	unsigned char status;
	status = TWSR & 0xF8;
     return status;
}