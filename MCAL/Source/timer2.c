/*
 * timer0.c
 * 
 * Created: 12/04/2023 04:57:05
 * Author: DELL
 */ 

/*	******************include section start****************	*/
#include <avr/io.h>
#include "../Header/timer2.h"
#include "../../Application//Header/APP.h"
#include "../../STD/STDMACROS.h"

/*	******************include section end****************	*/



void timer2_init()
{
	setbit(DDRD,7);
	
	/*to select required mode ---> Fast PWM */
	setbit(TCCR2,WGM20);
	setbit(TCCR2,WGM21);
	
	/*to select non inverting mode of comparession*/
	setbit(TCCR2,COM21);
	
	/*to select prescaler division factor 64*/
	setbit(TCCR2,CS20);
	setbit(TCCR2,CS21);
	
	timer2_dc(brightness_off);
	
}


void timer2_dc(float dc)
{
	OCR2 = dc * 255.0;
}
