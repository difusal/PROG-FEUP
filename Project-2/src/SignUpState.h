#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "StateControl.h"

class SignUpState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

	bool AllFormsInactive();
	void DeactivateAllForms();

private:
	ALLEGRO_KEYBOARD_STATE keyboard_state;

	ALLEGRO_BITMAP * sign_up_screen;
	ALLEGRO_USTR * allegro_active_string;
	ALLEGRO_USTR * username;
	ALLEGRO_USTR * password;
	ALLEGRO_USTR * hidden_password;
	ALLEGRO_USTR * confirm_password;
	ALLEGRO_USTR * hidden_confirm_password;
	ALLEGRO_USTR * age;
	ALLEGRO_USTR * gender;

	string username_str, password_str, confirm_password_str, age_str, gender_str;
	bool submit;
	bool username_form_active, password_form_active, confirm_password_form_active, age_form_active, gender_form_active;
};