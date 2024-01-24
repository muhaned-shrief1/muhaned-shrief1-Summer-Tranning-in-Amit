/*
 * ADC.c
 *
 * Created: 12/04/2023 02:51:48 م
 *  Author: DELL
 */ 


/*	******************include section start****************	*/
#include <avr/io.h>
#include "../Header/ADC.h"
#include "../../Application/Header/APP.h"
#include "../../STD/STDMACROS.h"
/*	******************include section end****************	*/



void ADC_init()
{
	/*to config ADC pin as input*/
	clearbit(ADC_DDR,ADC_pin);
	
	/*to enable ADC*/
	setbit(ADCSRA,ADEN);
	
	/*to set external capacitor at AREF*/
	setbit(ADMUX,REFS0);
	
	/*to set division factor 16*/
	setbit(ADCSRA,ADPS0);
	setbit(ADCSRA,ADPS1);
	
	setbit(Motor_DDR,Motor_pin);
	
	setbit(Motor_PORT,Motor_pin);
	
	
	
}

int ADC_read(unsigned char channel)
{
	/*to select the required channel*/
	ADMUX = (ADMUX & 0xE0 ) | channel;
	
	/*to start conversion*/
	setbit(ADCSRA,ADSC);
	
	/*Hold system until conversion complete*/
	while(readbit(ADCSRA,ADIF)==1);
	
	/*return registers value after conversion complete*/
	return ( (int)ADCL + (int)ADCH*256 );
}




