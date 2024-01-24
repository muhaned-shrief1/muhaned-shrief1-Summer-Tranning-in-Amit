/*
 * timer.h
 *
 * Created: 11/02/2023 11:48:40 ص
 *  Author: DELL
 */ 


#ifndef TIMER_H_
#define TIMER_H_



#define timer0_dc(dc) OCR0 = dc * 255.0


void timer0_init();


#endif /* TIMER_H_ */