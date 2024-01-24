/*
 * ADC.h
 *
 * Created: 12/04/2023 02:52:04 م
 *  Author: DELL
 */ 


#ifndef ADC_H_
#define ADC_H_

#define ADC_DDR DDRA
#define ADC_pin 0


void ADC_init();
int ADC_read(unsigned char channel);



#endif /* ADC_H_ */