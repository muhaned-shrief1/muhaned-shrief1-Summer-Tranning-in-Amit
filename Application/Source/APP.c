/*
 * APP.c
 *
 * Created: 12/04/2023 04:17:58 م
 *  Author: DELL
 */ 


/*	******************include section start****************	*/
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>

/*Application layer*/
#include "../Header/APP.h"
#include "../Header/Database.h"

/*Hal Layer*/
#include "../../MCAL/Header/ADC.h"
#include "../../MCAL/Header/timer0.h"
//#include "../../MCAL/Header/timer2.h"
#include "../../MCAL/Header/UART.h"
#include "../../MCAL/Header/I2C.h"

/*MCAL Layer*/
#include "../../HAL/Header/LCD.h"
#include "../../HAL/Header/keypad.h"
#include "../../HAL/Header/EEPROM.h"

/*STD Macros*/
#include "../../STD/STDMACROS.h"

/*	******************include section end****************	*/

extern char no_of_users_in_system;
extern char Is_admin_created;
char temp_state= '0';



void temp_mode(char check_signal)
{	
	char check=0;
	if ( 0 == check_signal )
	{
		USART_transmitstring("0-deactivate 1-activate ");
		check = USART_recieve();
		check_temp();
		
		switch(check)
		{
			case '0':   temp_state = '0';
			break;
			
			case '1':	temp_state = '1';
			break;
			
			default:    USART_transmitstring("wrong choice");
						
		}
		
		
	}
	
	if ( 1 == check_signal )
	{
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 0-deactiv 1-activ");
		
		while (check == 0)
		{
			check = KEYPAD_getkey();
			check_temp();
			
		}
		
		
		switch(check)
		{
			case '0':  
						{
							temp_state = '0';
							check_temp();
						}
			break;
			
			case '1':	
						{
							temp_state = '1';
							check_temp();
						}
			break;
			
			default:
						{
							LCD_send_cmd(0x01);
							LCD_send_cmd(0x80);
							LCD_send_string(" wrong choice");
							_delay_ms(500);
						}
		}
	}
	
}


void check_temp()
{
	int x;
	
	x = ADC_read(0);
	if(x>=57 && temp_state == '1')
	{
		setbit(PORTC,6);
	}
	else
	{
		clearbit(PORTC,6);
	}
	
}


void set_servo(char check_signal)
{
	char state = 0;
	
	if (0 == check_signal)
	{
		USART_transmitstring("1-open 0-close ");	
		
		state = USART_recieve();
		check_temp();
		
		
		if(state == '0' )
		{
			timer0_dc(0.092);  //angle 0
			
		}
		else if(state == '1')
		{
			timer0_dc(0.1229); // angle 90 
		}
		else
		{
			USART_transmitstring("Wrong choice");
		}
	}
	if (1 == check_signal)
	{
		
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 1-open 0-close");
		
		while(state == 0)
		{
			state = KEYPAD_getkey();
			check_temp();
		}
		
		if(state == '0' )
		{
			timer0_dc(0.092);  //angle 0
		}
		else if(state == '1')
		{
			timer0_dc(0.1229); // angle 90
		}
		else
		{
			LCD_send_cmd(0x01);
			LCD_send_cmd(0x80);
			LCD_send_string(" wrong choice");
			_delay_ms(1000);
			
		}
	}
	
}

void LED_init()
{
	setbit(LED_DDR , LED_one);
	setbit(LED_DDR , LED_two);
	setbit(LED_DDR , LED_three);
	setbit(LED_DDR , LED_four);
	setbit(LED_DDR , LED_five);
}


void LED_Activate(char check_signal)
{
	char num=0;
	
	if (0 == check_signal)
	{
		USART_transmitstring("Please enter the led number from 1 to 5 ");
		num = USART_recieve();
		check_temp();
		
		switch( num)
		{
			case '1': setbit(LED_PORT , LED_one);
			break;
			case '2': setbit(LED_PORT , LED_two);
			break;
			case '3': setbit(LED_PORT , LED_three);
			break;
			case '4': setbit(LED_PORT , LED_four);
			break;
			case '5': setbit(LED_PORT , LED_five);
			break;
			default: USART_transmitstring("Wrong choice");
		}
	}
	
	if (1 == check_signal)
	{
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" leds from 1:5");
		
		while (num == 0)
		{
			num = KEYPAD_getkey();
			check_temp();
		}
		
		switch( num)
		{
			case '1': setbit(LED_PORT , LED_one);
			break;
			case '2': setbit(LED_PORT , LED_two);
			break;
			case '3': setbit(LED_PORT , LED_three);
			break;
			case '4': setbit(LED_PORT , LED_four);
			break;
			case '5': setbit(LED_PORT , LED_five);
			break;
			default:
			{
				LCD_send_cmd(0x01);
				LCD_send_cmd(0x80);
				LCD_send_string(" wrong choice");
				_delay_ms(500);

			}
			
		}
	}
	
}

void LED_DeActivate(char check_signal)
{
	char num=0;
	
		if (0 == check_signal)
		{	
			USART_transmitstring("Please enter the led number from 1 to 5 ");
			num = USART_recieve();
			check_temp();
		
			switch( num)
			{
				case '1': clearbit(LED_PORT , LED_one);
						break;
				case '2': clearbit(LED_PORT , LED_two);
						break;
				case '3': clearbit(LED_PORT , LED_three);
						break;
				case '4': clearbit(LED_PORT , LED_four);
						break;
				case '5': clearbit(LED_PORT , LED_five);
						break;
				default: USART_transmitstring("Wrong choice");
			}
		}
		
			if (1 == check_signal)
			{
				LCD_send_cmd(0x01);
				LCD_send_cmd(0x80);
				LCD_send_string(" leds from 1:5");
				
				while (num == 0)
				{
					num = KEYPAD_getkey();
					check_temp();
				}
		
			
				switch( num)
				{
					case '1': clearbit(LED_PORT , LED_one);
					break;
					case '2': clearbit(LED_PORT , LED_two);
					break;
					case '3': clearbit(LED_PORT , LED_three);
					break;
					case '4': clearbit(LED_PORT , LED_four);
					break;
					case '5': clearbit(LED_PORT , LED_five);
					break;
					default: 
							{
								LCD_send_cmd(0x01);
								LCD_send_cmd(0x80);
								LCD_send_string(" wrong choice");
								_delay_ms(500);
				

							}
				
				}
			}
	
}

void Led(char check_signal)
{
	char check=0;
		
	if (0 == check_signal)
	{
		USART_transmitstring(" 1-Activate Led 2-deactivate led");
		check = USART_recieve();
		check_temp();
	
	
		switch (check)
		{
			case   '1' : LED_Activate(0);
			break;
		
			case   '2' : LED_DeActivate(0);
			break;
		
			default:USART_transmitstring("Wrong choice"); 
		}
	}
	
	if (1 == check_signal)
	{
	
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 1-en 2-dis");

		
		while (check == 0)
		{
			check = KEYPAD_getkey();
			check_temp();
		}
		
		
		switch (check)
		{
			case   '1' : {
							LED_Activate(1);
							//c=0;
						 }
			break;
			
			case   '2' : 
						{
							LED_DeActivate(1);
							//c=0;
						}

			break;
			
			default:
					{
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string("wrong choice");
						_delay_ms(1000);
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string(" 1-en 0-dis");
		
					}
		}
	}
		
	
}



void dimming_brightness(char check_signal)
{
	check_temp();
	char check=0;
		
	if (0 == check_signal)
	{
		USART_transmitstring("Enter brightness number 0:3 ");
		check = USART_recieve();
		check_temp();
		
		
		switch(check)
		{
			case '0': timer2_dc(brightness_off);
					break;
			case '1': timer2_dc(brightness_low);
					break;
			case '2': timer2_dc(brightness_medium);
					break;
			case '3': timer2_dc(brightness_high);
					break;
			default : USART_transmitstring("wrong choice");
		}
	}
		
		if (1 == check_signal)
		{
			LCD_send_cmd(0x01);
			LCD_send_cmd(0x80);
			LCD_send_string("level 0:3");
			while(check == 0)
			{
				check = KEYPAD_getkey();
				check_temp();
			}
		
			
			switch(check)
			{
				case '0': timer2_dc(brightness_off);
				break;
				case '1': timer2_dc(brightness_low);
				break;
				case '2': timer2_dc(brightness_medium);
				break;
				case '3': timer2_dc(brightness_high);
				break;
				default : 
						{
							LCD_send_cmd(0x01);
							LCD_send_cmd(0x80);
							LCD_send_string("wrong choice");
							_delay_ms(500);
						}
			}
		}
}



void APP()
{	
	char check_Usart=0,check_keypad=0;
	if (Is_admin_created == 0 )
	{
		if (no_of_users_in_system == 0 )
		{
			USART_transmitstring("choose the number 0-to add admin  ");
		}
		else 
		{
			USART_transmitstring("choose the number 0-to add admin 2-to log in to user mode");
		}
	}
	else
	{
		USART_transmitstring("choose the number 2-to login to admin mode 3- to log in to user mode  ");
	}
	
	
		check_Usart = USART_recieve();
		check_temp();
		
		switch(check_Usart)
		{
			case '0':		New_Admin();
			break;		
			/*
			case '1':		New_User();
			break;
			*/
			case '2':		login_Admin(0);
			break;
			
			case '3':		login_User(0);
			break;
			
			default: USART_transmitstring("Wrong choice Try again");
			
		}
		
		LCD_send_string("2-login admin");
		LCD_send_cmd(0x80+0x40);
		LCD_send_string("3-login user");
		
		check_keypad = KEYPAD_getkey();
		check_temp();
		
		
		switch(check_keypad)
		{
			case '2':		login_Admin(1);
			break;
			
			case '3':		login_User(1);
			break;
			
			default: 
					{
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string("Wrong choice");
						
					}
			
		}
}


void All_init()
{
	LCD_init();
	KEYPAD_init();
	
	USART_init(12);
	ADC_init();
	timer0_init();
	timer2_init();
	EEPROM_init();
	LED_init();
	Bazzer_init();
}

