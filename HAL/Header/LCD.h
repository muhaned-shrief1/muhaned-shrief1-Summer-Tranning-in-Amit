/*
 * LCD.h
 *
 * Created: 14/04/2023 04:27:58 م
 *  Author: DELL
 */ 


#ifndef LCD_H_
#define LCD_H_


void LCD_init();
void LCD_send_cmd(char cmd);
void LCD_send_char(char data);
void LCD_send_string(char *data);



#endif /* LCD_H_ */