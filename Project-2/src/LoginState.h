#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "User.h"

class LoginState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_KEYBOARD_STATE keyboard_state;

	ALLEGRO_BITMAP * login_screen;
	ALLEGRO_USTR * username;
	ALLEGRO_USTR * password;
	ALLEGRO_USTR * hidden_password;

	string username_str, password_str;
	bool submit;
	bool username_form_active, password_form_active;
};