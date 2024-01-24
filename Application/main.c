/*
 * PWM with servo motor.c
 *
 * Created: 11/02/2023 11:47:29 
 * Author : DELL
 */ 


/*	******************include section start****************	*/
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>

/*Application layer*/
#include "Header/APP.h"


/*Hal Layer*/
#include "../MCAL//Header/ADC.h"
#include "../MCAL//Header/timer0.h"
#include "../MCAL//Header/timer2.h"
#include "../MCAL//Header/UART.h"
#include "../MCAL//Header/I2C.h"

/*MCAL Layer*/
#include "../HAL//Header/LCD.h"
#include "../HAL//Header/keypad.h"
#include "../HAL//Header/EEPROM.h"

/*STD Macros*/
#include "../STD/STDMACROS.h"

/*	******************include section end****************	*/


int main(void)
{
	All_init();
	
    /* Replace with your application code */
    while (1) 
    {
		check_temp();
		APP();	
	}
}

