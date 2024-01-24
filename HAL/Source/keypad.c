/*
 * keypad.c
 *
 * Created: 09/02/2023 07:37:30 م
 *  Author: DELL
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "../../STD/STDMACROS.h"
#include "../Header/LCD.h"
#include "../Header/keypad.h"

void KEYPAD_init()
{
	setbit(KEYPADO_DDR,2);
	setbit(KEYPADO_DDR,3);
	setbit(KEYPADO_DDR,4);
	setbit(KEYPADO_DDR,5);

	clearbit(KEYPADI_DDR,0);
	clearbit(KEYPADI_DDR,1);
	clearbit(KEYPADI_DDR,2);
	clearbit(KEYPADI_DDR,7);
	
	
	/* ************************ internal pull up resister for input pins ************************ */
	setbit(KEYPADO_PORT,2);
	setbit(KEYPADO_PORT,3);
	setbit(KEYPADO_PORT,4);
	setbit(KEYPADO_PORT,5);
	
	/* ************************ high on the output pins ************************ */
	setbit(KEYPADI_PORT,0);
	setbit(KEYPADI_PORT,1);
	setbit(KEYPADI_PORT,2);
	setbit(KEYPADI_PORT,7);

}

char KEYPAD_getkey()
{
	char key=0;
	//first column
	clearbit(KEYPADO_PORT,2);
	if (readbit(KEYPADI_PIN,0)==0)
	{
		key='7';
		while (readbit(KEYPADI_PIN,0)==0);
	}
	else if (readbit(KEYPADI_PIN,1)==0)
	{
		key='8';
		while (readbit(KEYPADI_PIN,1)==0);
	}
	else if (readbit(KEYPADI_PIN,2)==0)
	{
		key='9';
		while (readbit(KEYPADI_PIN,2)==0);
	}
	else if (readbit(KEYPADI_PIN,7)==0)
	{
		key='/';
		while (readbit(KEYPADI_PIN,7)==0);
	}
	setbit(KEYPADO_PORT,2);
	_delay_us(1);
	
	//second column
	clearbit(KEYPADO_PORT,3);
	if (readbit(KEYPADI_PIN,0)==0)
	{
		key='4';
		while (readbit(KEYPADI_PIN,0)==0);
	}
	else if (readbit(KEYPADI_PIN,1)==0)
	{
		key='5';
		while (readbit(KEYPADI_PIN,1)==0);
	}
	else if (readbit(KEYPADI_PIN,2)==0)
	{
		key='6';
		while (readbit(KEYPADI_PIN,2)==0);
	}
	else if (readbit(KEYPADI_PIN,7)==0)
	{
		key='*';
		while (readbit(KEYPADI_PIN,7)==0);
	}
	setbit(KEYPADO_PORT,3);
	_delay_us(1);
	
	
	//third column
	clearbit(KEYPADO_PORT,4);
	if (readbit(KEYPADI_PIN,0)==0)
	{
		key='1';
		while (readbit(KEYPADI_PIN,0)==0);
		
	}
	else if (readbit(KEYPADI_PIN,1)==0)
	{
		key='2';
		while (readbit(KEYPADI_PIN,1)==0);
		
	}
	else if (readbit(KEYPADI_PIN,2)==0)
	{
		key='3';
		while (readbit(KEYPADI_PIN,2)==0);
		
	}
	else if (readbit(KEYPADI_PIN,7)==0)
	{
		key='-';
		while (readbit(KEYPADI_PIN,7)==0);
		
	}
	setbit(KEYPADO_PORT,4);
	_delay_us(1);
	
	
	//forth column
	clearbit(KEYPADO_PORT,5);
	if (readbit(KEYPADI_PIN,0)==0)
	{
		key='c';
		while (readbit(KEYPADI_PIN,0)==0);
	}
	else if (readbit(KEYPADI_PIN,1)==0)
	{
		key='0';
		while (readbit(KEYPADI_PIN,1)==0);
		
	}
	else if (readbit(KEYPADI_PIN,2)==0)
	{
		key='=';
		while (readbit(KEYPADI_PIN,2)==0);
		
	}
	else if (readbit(KEYPADI_PIN,7)==0)
	{
		key='+';
		while (readbit(KEYPADI_PIN,7)==0);
		
	}
	setbit(KEYPADO_PORT,5);
	_delay_us(1);
	
	return key;
}