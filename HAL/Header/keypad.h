/*
 * keypad.h
 *
 * Created: 09/02/2023 07:37:48 م
 *  Author: DELL
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

void KEYPAD_init();
char KEYPAD_getkey();

#define KEYPADO_DDR DDRC
#define KEYPADI_DDR DDRB

#define KEYPADO_PORT PORTC
#define KEYPADI_PORT PORTB

#define KEYPADI_PIN PINB



#endif /* KEYPAD_H_ */