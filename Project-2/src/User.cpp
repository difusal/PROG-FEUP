#include "User.h"
#include "StateControl.h"

User::User(_IDNum ID, string & Username, string & Password, int Age, string & Gender)
{
	id = ID;
	username = Username;
	password = Password;
	age = Age;
	gender = Gender;
}