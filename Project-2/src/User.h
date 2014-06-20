#pragma once

#include "stdIncludes.h"

class User
{
public:
	User(_IDNum ID, string & Username, string & Password, int Age, string & Gender);

	_IDNum GetID() const
	{ return id; }

	const string & GetUsername() const
	{ return username; }

	const string & GetPassword() const
	{ return password; }

	int GetAge() const
	{ return age; }

	const string & GetGender() const
	{ return gender; }

private:
	_IDNum id;
	string username, password, gender;
	int age;
};