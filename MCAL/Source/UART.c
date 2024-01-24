/*
 * UART.c
 *
 * Created: 24/02/2023 11:16:13
 *  Author: DELL
 */ 


/*	******************include section start***************	*/
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "../Header/UART.h"
#include "../../STD/STDMACROS.h"
/*	******************include section end****************	*/



void USART_init(unsigned char Baud)
{
	UBRRH = (unsigned char)(Baud>>8);
	UBRRL = (unsigned char)Baud;
	
	clearbit(UCSRC,URSEL);   // SET TO ENABLE WRITING ON UBRRH
	
	setbit(UCSRB,TXEN);   //TO ENABLE TRANSMITTER
	setbit(UCSRB,RXEN);  //TO ENABLE RECIEVER
	
	setbit(UCSRC,URSEL);   // SET TO ENABLE WRITING ON UCSRC
	
	clearbit(UCSRC,UMSEL);  //ASYNCHRONOUS MODE
	
	/*No parity*/
	
	/*1 stop bit*/
	
	
	// TO enable 8 bit mode
	setbit(UCSRC,UCSZ0);
	setbit(UCSRC,UCSZ1);
}

void USART_transmit( char data)
{
	while(readbit(UCSRA,UDRE)==0);
	UDR = data;
	while(readbit(UCSRA,TXC)==0);
}

 char USART_recieve()
{
	while(readbit(UCSRA,RXC)==0);
	return (char)UDR;
}

void USART_transmitstring(char *str) 
{
	int i =0 ;
	
	while ( (str[i])!='\0')
	{
		USART_transmit(str[i]);
		i++;
		_delay_us(20);
	}
}
