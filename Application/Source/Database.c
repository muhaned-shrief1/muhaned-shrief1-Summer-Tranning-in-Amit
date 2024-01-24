/*
 * Database.c
 *
 * Created: 23/04/2023 11:27:12 م
 *  Author: DELL
 */ 

/*
choose mode
 
1 for Admin
enter 1 for user

1 for existing  ----> password 
2 for new       ----> user name and password

*/


#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "../Header/APP.h"
#include "../Header/Database.h"

#include "../../HAL/Header/LCD.h"
#include "../../HAL/Header/EEPROM.h"

#include "../../MCAL/Header/UART.h"
#include "../../HAL/Header/keypad.h"
#include "../../STD/STDMACROS.h"

#define initial_Admin_add 0x12
#define initial_user_add   0x20

struct SUserorAdmin U,A;



char	no_of_users_in_system       = 0 ;
char	Is_admin_created	        = 0 ;




void login_User()
{
	int i, n=0;
	char check[3];
	int flag = 0;
	struct SUserorAdmin U_check;
	
	USART_transmitstring("Enter your password (3 numbers)");
	
	for(i=0;i<8;i++)
	{
		_delay_ms(20);
		U_check.name[i] = EEPROM_recieve( (initial_user_add)+ i );
	}
	for(i=0;i<3;i++)
	{
		_delay_ms(20);
		U_check.password[i] = EEPROM_recieve( (initial_user_add+( (no_of_users_in_system-1)*8)+8+i ) );
	}
	
	while (n!=3)
	{
		//to recieve password and check it
		for(i=0;i<3;i++)
		{
			check[i] = USART_recieve();
			if(check[i] != U_check.password[i])
			{
				flag = 0;
			}
			else
			{
				flag++;
			}
			
		}
		
		
		if(flag==3)
		{
			USART_transmitstring("Welcome ");
			User_Mode(1);
		}
		else
		{
			n++;
			if(n==1)
			{
				USART_transmitstring("Wrong Password remaining 2 times  ");
			}
			if(n==2)
			{
				USART_transmitstring("Wrong Password remaining 1 time  ");
			}
			if(n==3)
			{
				USART_transmitstring("Wrong Password last chance  ");
			}
		}
	}
	//if n==3 can be used without if (^_^) the password is entered wrong three timer activate Bzzer
	if(n==3)
	{
		USART_transmitstring("You Entered Wrong password. Please Reset the System");
		Bazzer();
	}
}

void login_Admin()
{
	
	int i, n=0;
	char check[3];
	int flag = 0;
	struct SUserorAdmin A_check;
	
	USART_transmitstring("Enter your password (3 numbers)");
	
		for(i=0;i<3;i++)
		{
			_delay_ms(20);
			A_check.password[i] = EEPROM_recieve( (initial_Admin_add)+8+i );
		}
		
		while (n!=3)
		{
			//to recieve password and check it
			for(i=0;i<3;i++)
			{
				check[i] = USART_recieve();
				if(check[i] != A_check.password[i])
				{
					flag = 0;
				}
				else
				{
					flag++;
				}
				
			}
			
					
			if(flag==3)
			{
				USART_transmitstring("Welcome ");
				Admin_Mode(0);
			}
			else
			{
				n++;
				if(n==1)
				{
					USART_transmitstring("Wrong Password remaining 2 times  ");
				}
				if(n==2)
				{
					USART_transmitstring("Wrong Password remaining 1 time  ");
				}
				if(n==3)
				{
					USART_transmitstring("Wrong Password last chance  ");
				}
			}
		}
		//if n==3 can be used without if (^_^) the password is entered wrong three timer activate Bzzer
		if(n==3)
		{
			USART_transmitstring("You Entered Wrong password. Please Reset the System");
			Bazzer();
		}
		
}
	



void New_Admin()
{
	char ch;
	struct SUserorAdmin New_A;
	int i;
	
	USART_transmitstring("Enter Name with 0 at the end of the name");
	
	for(i=0;i<8;i++)
	{
		ch = USART_recieve();
		if( ch != '0')
		{
			New_A.name[i] = ch;
		}
		else
		{
			break;
		}
	}
	
	USART_transmitstring("Enter Password three numbers ");
	
	for(i=0;i<3;i++)
	{
		ch = USART_recieve();
		New_A.password[i] =(char) ch;
		
	}
	
	
	for(i=0;i<8;i++)
	{
		_delay_ms(20);
		EEPROM_send( initial_Admin_add+i ,New_A.name[i]);
	
	}
	
	for(i=0;i<3;i++)
	{
		_delay_ms(20);
		EEPROM_send( initial_Admin_add+8+i ,New_A.password[i]);
		
	}
	
	Is_admin_created = 1;
	USART_transmitstring("data saved ");
	
	Admin_Mode(0);

}


void New_User()
{
	char ch;
	struct SUserorAdmin New_U;
	int i;
	
	USART_transmitstring("Enter Name with 0 at the end of the name");
	
	for(i=0;i<8;i++)
	{
		ch = USART_recieve();
		if( ch != '0')
		{
			New_U.name[i] = ch;
		}
		else
		{
			break;
		}
	}
	
	USART_transmitstring("Enter Password three numbers ");
	
	for(i=0;i<3;i++)
	{
		ch = USART_recieve();
		New_U.password[i] =(char) ch;
		
	}
	
	
	for(i=0;i<8;i++)
	{
		_delay_ms(20);
		EEPROM_send( initial_user_add+(no_of_users_in_system*8)+i ,New_U.name[i]);
	}
	
	for(i=0;i<3;i++)
	{
		_delay_ms(20);
		EEPROM_send( initial_user_add+(no_of_users_in_system*8)+8+i ,New_U.password[i]);
	}
	
	no_of_users_in_system++ ;
	USART_transmitstring("data saved ");
	
	User_Mode(1);

}





void User_Mode(char check_signal)
{
	
	char c=0,check=0,temp = 0;
	
	if ( 0 ==check_signal)
	{
		USART_transmitstring("Choose option you want to control 2 -Led  3-Dimming 4-Air Conditioner 0-skip User mode");
		c = USART_recieve();
		while (check != '0')
		{
			switch(c)
			{
				case '0': check = '0';
				break;
				
				case '2': Led(check_signal);
				break;
				
				case '3':dimming_brightness(check_signal);
				break;
				
				case '4': temp_mode(check_signal);
				break;
				
				default: USART_transmitstring("Wrong choice Try again");
			}
		}
	}

	if ( 1 ==check_signal)
	{
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 2-Led 3-Dimming");
		LCD_send_cmd(0x80+0x40);
		
		LCD_send_string(" 4-Air Cond");
		_delay_ms(2000);
		
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 0-skip User mode");
		
		while (check != '0')
		{
			while (c == 0)
			{
				c = KEYPAD_getkey();
				check_temp();
			}
			
			if (temp != c)
			{
				
				switch(c)
				{
					case '0': check = '0';
					break;
								
					case '2': {
								Led(check_signal);
								LCD_send_cmd(0x01);
								LCD_send_cmd(0x80);
								LCD_send_string(" 2-Led 3-Dimming");
								LCD_send_cmd(0x80+0x40);
								
								LCD_send_string(" 4-Air Cond");
								_delay_ms(2000);
								
								LCD_send_cmd(0x01);
								LCD_send_cmd(0x80);
								LCD_send_string(" 0-skip User mode");
								c=0;
						
								}
					break;	
					
					case '3':
								{
									dimming_brightness(check_signal);
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 2-Led 3-Dimming");
									LCD_send_cmd(0x80+0x40);
									
									LCD_send_string(" 4-Air Cond");
									_delay_ms(2000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mode");
									c=0;
								}
					break;
					
					case '4':
								{
									temp_mode(check_signal);
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 2-Led 3-Dimming");
									LCD_send_cmd(0x80+0x40);
									
									LCD_send_string(" 4-Air Cond");
									_delay_ms(2000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mode");
									c=0;
								}
					
					break;
					
					default:
								{
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" Wrong choice");
									_delay_ms(1000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 2-Led 3-Dimming");
									LCD_send_cmd(0x80+0x40);
									
									LCD_send_string(" 4-Air Cond");
									_delay_ms(2000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mode");
									c=0;
						
								}
				}
				temp = c;
			}
		}
	}
		
	/*to skip user mode*/
	APP();
}

void Admin_Mode(char check_signal)
{
	
	char c=0,check=1,temp=0;
	
	if ( 0 == check_signal)
	{
		if (no_of_users_in_system==0)
		{
			while (check != '0')
			{
				
				USART_transmitstring("Choose number operation you want to control 1-Door 2-Led  3-Dimming 4-Air Conditioner 5-to add user 0-to close Admin mode");
				c = USART_recieve();
				check_temp();
				switch(c)
				{
					case '0': check = '0';
					break;
					
					case '1':set_servo(check_signal);
					break;
					
					case '2': Led(check_signal);
					break;
					
					case '3':dimming_brightness(check_signal);
					break;
					
					case '4': temp_mode(check_signal);
					break;
					
					case '5': New_User(check_signal);
					
					default: USART_transmitstring("Wrong choice Try again");
				}
			}
		
		}
		else
		{
			while (check != '0')
			{
				
				USART_transmitstring("Choose number operation you want to control 1-Door 2-Led  3-Dimming 4-Air Conditioner 5-to add user 0-to close Admin mode");
				c = USART_recieve();
				check_temp();
				switch(c)
				{
					case '0': check = '0';
					break;
					
					case '1':set_servo(check_signal);
					break;
					
					case '2': Led(check_signal);
					break;
					
					case '3':dimming_brightness(check_signal);
					break;
					
					case '4': temp_mode(check_signal);
					break;
					
					case '5': New_User(check_signal);
					break;
					
					default: USART_transmitstring("Wrong choice Try again");
				}
		}
	}

	if ( 1 == check_signal)
	{	
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 1-door 2-Led");
		LCD_send_cmd(0x80+0x40);
		LCD_send_string("3-Dimming 4-Air");
		_delay_ms(2000);
		
		LCD_send_cmd(0x01);
		LCD_send_cmd(0x80);
		LCD_send_string(" 0-skip User mod");
		_delay_ms(1000);
		
		while (check != '0')
		{	
			while (c == 0)
			{
				c = KEYPAD_getkey();
				check_temp();
			}
			
			if (temp != c)
			{
			
				switch(c)
				{
					case '0': check = '0';
					break;
				
					case '1':
								{
									set_servo(check_signal);
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 1-door 2-Led");
									LCD_send_cmd(0x80+0x40);
									LCD_send_string("3-Dimming 4-Air");
									_delay_ms(2000);
							
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mod");
									c=0;
								}
					
					break;
				
					case '2': {
								Led(check_signal);
								LCD_send_cmd(0x01);
								LCD_send_cmd(0x80);
								LCD_send_string(" 1-door 2-Led");
								LCD_send_cmd(0x80+0x40);
								LCD_send_string("3-Dimming 4-Air");
								_delay_ms(2000);
								
								LCD_send_cmd(0x01);
								LCD_send_cmd(0x80);
								LCD_send_string(" 0-skip User mod");
								c=0;
									
							  }
					break;
				
					case '3':
								{
									dimming_brightness(check_signal);
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 1-door 2-Led");
									LCD_send_cmd(0x80+0x40);
									LCD_send_string("3-Dimming 4-Air");
									_delay_ms(2000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mod");
									c=0;
								}
					break;
				
					case '4': 
								{
									temp_mode(check_signal);
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 1-door 2-Led");
									LCD_send_cmd(0x80+0x40);
									LCD_send_string("3-Dimming 4-Air");
									_delay_ms(2000);
									
									LCD_send_cmd(0x01);
									LCD_send_cmd(0x80);
									LCD_send_string(" 0-skip User mod");
									c=0;
								}
					
					break;
				
					default:
					{
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string("  Wrong choice");
						_delay_ms(1000);
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string("1-door 2-Led");
						LCD_send_cmd(0x80+0x40);
						LCD_send_string("3-Dimming 4-Air");
						_delay_ms(1750);
					
						LCD_send_cmd(0x01);
						LCD_send_cmd(0x80);
						LCD_send_string(" 0-skip User mod");
						_delay_ms(1750);
						c=0;
									
					
					}
				}
				temp = c;
			}
		}
	}
		
	/*to skip admin mode*/
		APP();

}
}

void Bazzer_init()
{
	setbit(DDRC,7);
}

void Bazzer()
{
	
	while(1)
	{
		setbit(PORTC,7);
	}
}

	