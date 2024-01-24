/*
 * APP.h
 *
 * Created: 12/04/2023 04:18:22 م
 *  Author: DELL
 */ 


#ifndef APP_H_
#define APP_H_


#include "../../STD/STD.h"

#define Motor_DDR DDRC
#define Motor_pin 6

#define Motor_PORT PORTC

#define close_angle '0'
#define open_angle '1'

#define LED_one		2
#define LED_two		3
#define LED_three	4
#define LED_four	5
#define LED_five	6

#define LED_DDR		DDRD
#define LED_PORT		PORTD


#define brightness_off		0.01
#define brightness_low		0.33
#define brightness_medium	0.66
#define brightness_high		1.0

void temp_mode(char check_signal);
void set_servo(char check_signal);
void LED_Activate(char check_signal);
void LED_DeActivate(char check_signal);
void Led(char check_signal);
void dimming_brightness(char check_signal);
void APP();
void check_temp();

void LED_init();
void All_init();






#endif /* APP_H_ */