/*
 * UART.h
 *
 * Created: 24/02/2023 11:16:33 م
 *  Author: DELL
 */ 


#ifndef UART_H_
#define UART_H_


void USART_init(unsigned char Baud) ;
void USART_transmit( char data) ;
char USART_recieve() ;
void USART_transmitstring(char *str) ;


#endif /* UART_H_ */