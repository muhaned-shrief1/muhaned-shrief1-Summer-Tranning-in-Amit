/*
 * Database.h
 *
 * Created: 23/04/2023 11:27:22 م
 *  Author: DELL
 */ 


#ifndef DATABASE_H_
#define DATABASE_H_

#include "../../STD/STD.h"


struct SUserorAdmin
{
	char name[8];
	char password[4];	
};

void login_Admin();
void login_User();

void check_User();
void check_Admin();

void New_Admin();
void New_User();

void User_Mode(char check_signal);
void Admin_Mode(char check_signal);

void Bazzer_init();
void Bazzer();

//void Remove_User(char check_signal);




#endif /* DATABASE_H_ */