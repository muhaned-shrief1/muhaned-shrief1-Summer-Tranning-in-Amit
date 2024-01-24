/*
 * LCD.c
 *
 * Created: 14/04/2023 04:27:43 م
 *  Author: DELL
 */ 


#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "../Header/LCD.h"
#include "../../STD/STDMACROS.h"




/* ******************************************** LCD initialization *********************************************** */
void LCD_init()
{
	
	setbit(DDRA,1);
	setbit(DDRA,2);
	setbit(DDRA,3);
	
	DDRA |= 0xf0;
	
	LCD_send_cmd(0x02);
	LCD_send_cmd(0x28);	//LCD 4-bit mode
	LCD_send_cmd(0x0c);  //LCD display on, cursor off, cursor blink off
	LCD_send_cmd(0x06);  //LCD auto incrment
	LCD_send_cmd(0x01);   //clear secreen
	
	_delay_ms(5);
	
}


/* ******************************************** LCD Send Command *********************************************** */

void LCD_send_cmd(char cmd)
{
	PORTA = (PORTA & 0x0f) | (cmd & 0xf0); //send highest 4 bits
	
	clearbit(PORTA,1);		//clear RS to send command
	clearbit(PORTA,2);		//set RW 
	_delay_us(10);
	
	setbit(PORTA,3);		//enable E to enable data sending
	_delay_us(10);
	
	clearbit(PORTA,3);		//disable E
	
	PORTA = (PORTA & 0x0f) | (cmd<<4);	
	
	setbit(PORTA,3);		//enable E to enable data sending
	_delay_us(10);
	
	clearbit(PORTA,3);		//disable E

}


/* ******************************************** LCD Send Data *********************************************** */
void LCD_send_char(char data)
{
	PORTA = (PORTA & 0x0f) | (data & 0xf0); //send highest 4 bits
	
	setbit(PORTA,1);		//clear RS to send command
	clearbit(PORTA,2);		//set RW
	_delay_us(10);
	
	setbit(PORTA,3);		//enable E to enable data sending
	_delay_us(10);
	
	clearbit(PORTA,3);		//disable E
	
	PORTA = (PORTA & 0x0f) | (data<<4);
	setbit(PORTA,3);		//enable E to enable data sending
	_delay_us(10);
	
	clearbit(PORTA,3);		//disable E
}



/* ******************************************** LCD Send String *********************************************** */
void LCD_send_string(char *x)
{
	int i=0;
	while(x[i] != '\0')
	{
		LCD_send_char(x[i]);
		i++;
	}
	
}

