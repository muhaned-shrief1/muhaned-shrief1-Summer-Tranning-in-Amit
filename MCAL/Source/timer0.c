/*
 * timer0.c
 * 
 * Created: 12/04/2023 04:57:05
 * Author: DELL
 */ 

/*	******************include section start****************	*/
#include <avr/io.h>
#include "../Header/timer0.h"
#include "../../STD/STDMACROS.h"

/*	******************include section end****************	*/



void timer0_init()
{
	setbit(DDRB,3);
	
	/*to select required mode ---> Fast PWM */
	setbit(TCCR0,WGM00);
	setbit(TCCR0,WGM01);
	
	/*to select non inverting mode of comparession*/
	setbit(TCCR0,COM01);
	
	/*to select prescaler division factor 64*/
	setbit(TCCR0,CS00);
	setbit(TCCR0,CS01);
	
	timer0_dc(0.092);
}


