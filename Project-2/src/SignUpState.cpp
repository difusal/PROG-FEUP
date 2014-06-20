#include "SignUpState.h"

void SignUpState::Initialize()
{
	sign_up_screen = al_load_bitmap(SignUpScreen);
	if (!sign_up_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load sign up background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	submit = false;

	username_form_active = false;
	username = al_ustr_new("");

	password_form_active = false;
	password = al_ustr_new("");
	hidden_password = al_ustr_new("");

	confirm_password_form_active = false;
	confirm_password = al_ustr_new("");
	hidden_confirm_password = al_ustr_new("");

	age_form_active = false;
	age = al_ustr_new("");

	gender_form_active = false;
	gender = al_ustr_new("");
}

bool SignUpState::Update(ALLEGRO_EVENT * ev)
{
	/* --- scanning keyboard hits --- */
	al_get_keyboard_state(&keyboard_state);

	/* --- if tab pressed and no form is active, select first form --- */
	if (AllFormsInactive() &&
		ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_TAB)
	{ username_form_active = true; return true; }

	/* --- if a form is pressed --- */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 625 &&
		104 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 185)
	{ DeactivateAllForms(); cout << "Username form active..." << endl; username_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 625 &&
		208 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 289)
	{ DeactivateAllForms(); cout << "Password form active..." << endl; password_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 625 &&
		312 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 393)
	{ DeactivateAllForms(); cout << "Confirm password form active..." << endl; confirm_password_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 276 &&
		416 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 497)
	{ DeactivateAllForms(); cout << "Age form active..." << endl; age_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		325 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 626 &&
		416 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 497)
	{ DeactivateAllForms(); cout << "Gender form active..." << endl; gender_form_active = true; return true; }
	/* --- confirm button pressed --- */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		190 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 298 &&
		515 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 550)
	{ cout << "Save button pressed..." << endl; submit = true; }
	/* cancel button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		510 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 603 &&
		515 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 550)
	{ cout << "Cancel button pressed..." << endl; StateControl::GetInstance()->ChangeState(Login); return true; }
	/* --- pressed anywhere out of the forms --- */
	else if (StateControl::GetInstance()->left_mouse_button_released)
	{ DeactivateAllForms(); return true; }

	/* ----- writing username ----- */
	if (username_form_active || password_form_active || confirm_password_form_active ||
		age_form_active || gender_form_active)
	{
		if (username_form_active) { allegro_active_string = username; }
		else if (password_form_active) { allegro_active_string = password; }
		else if (confirm_password_form_active) { allegro_active_string = confirm_password; }
		else if (age_form_active) { allegro_active_string = age; }
		else if (gender_form_active) { allegro_active_string = gender; }

		/* --- keyboard input --- */
		if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if ((allegro_active_string == age && al_ustr_size(allegro_active_string) < 3) ||
				(allegro_active_string == gender && al_ustr_size(allegro_active_string) < 13) ||
				(al_ustr_size(allegro_active_string) < 21 && allegro_active_string != age && allegro_active_string != gender))
			{
				if (al_key_down(&keyboard_state, ALLEGRO_KEY_RSHIFT) ||
					al_key_down(&keyboard_state, ALLEGRO_KEY_LSHIFT))
				{
					cout << "* Shift is being held *" << endl;
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(allegro_active_string, "Q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(allegro_active_string, "W"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(allegro_active_string, "E"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(allegro_active_string, "R"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(allegro_active_string, "T"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(allegro_active_string, "Y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(allegro_active_string, "U"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(allegro_active_string, "I"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(allegro_active_string, "O"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(allegro_active_string, "P"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(allegro_active_string, "A"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(allegro_active_string, "S"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(allegro_active_string, "D"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(allegro_active_string, "F"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(allegro_active_string, "G"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(allegro_active_string, "H"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(allegro_active_string, "J"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(allegro_active_string, "K"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(allegro_active_string, "L"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(allegro_active_string, "Z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(allegro_active_string, "X"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(allegro_active_string, "C"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(allegro_active_string, "V"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(allegro_active_string, "B"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(allegro_active_string, "N"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(allegro_active_string, "M"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(allegro_active_string, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(allegro_active_string, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(allegro_active_string, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(allegro_active_string, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(allegro_active_string, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(allegro_active_string, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(allegro_active_string, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(allegro_active_string, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(allegro_active_string, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(allegro_active_string, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(allegro_active_string, " "); break; }
					}
				}
				else
				{
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(allegro_active_string, "q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(allegro_active_string, "w"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(allegro_active_string, "e"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(allegro_active_string, "r"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(allegro_active_string, "t"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(allegro_active_string, "y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(allegro_active_string, "u"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(allegro_active_string, "i"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(allegro_active_string, "o"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(allegro_active_string, "p"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(allegro_active_string, "a"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(allegro_active_string, "s"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(allegro_active_string, "d"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(allegro_active_string, "f"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(allegro_active_string, "g"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(allegro_active_string, "h"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(allegro_active_string, "j"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(allegro_active_string, "k"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(allegro_active_string, "l"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(allegro_active_string, "z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(allegro_active_string, "x"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(allegro_active_string, "c"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(allegro_active_string, "v"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(allegro_active_string, "b"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(allegro_active_string, "n"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(allegro_active_string, "m"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(allegro_active_string, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(allegro_active_string, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(allegro_active_string, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(allegro_active_string, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(allegro_active_string, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(allegro_active_string, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(allegro_active_string, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(allegro_active_string, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(allegro_active_string, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(allegro_active_string, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(allegro_active_string, " "); break; }
					}
				}

				if (password_form_active &&
					ev->keyboard.keycode != ALLEGRO_KEY_TAB &&
					ev->keyboard.keycode != ALLEGRO_KEY_BACKSPACE &&
					ev->keyboard.keycode != ALLEGRO_KEY_ENTER)
				{ al_ustr_append_cstr(hidden_password, "*"); }
				else if (confirm_password_form_active &&
					ev->keyboard.keycode != ALLEGRO_KEY_TAB &&
					ev->keyboard.keycode != ALLEGRO_KEY_ENTER)
				{ al_ustr_append_cstr(hidden_confirm_password, "*"); }
			}

			switch(ev->keyboard.keycode)
			{
				/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
			case ALLEGRO_KEY_BACKSPACE:
				{
					al_ustr_remove_chr(allegro_active_string, al_ustr_offset(allegro_active_string, -1));
					if (password_form_active)
					{
						al_ustr_remove_chr(hidden_password, al_ustr_offset(hidden_password, -1));
					}
					else if (confirm_password_form_active)
					{
						al_ustr_remove_chr(hidden_confirm_password, al_ustr_offset(hidden_confirm_password, -1));
					}

					return true;
				}
			case ALLEGRO_KEY_TAB:
				{
					if (username_form_active) { username_form_active = false; password_form_active = true; }
					else if (password_form_active) { password_form_active = false; confirm_password_form_active = true; }
					else if (confirm_password_form_active) { confirm_password_form_active = false; age_form_active = true; }
					else if (age_form_active) { age_form_active = false; gender_form_active = true; }
					else if (gender_form_active) { gender_form_active = false; }

					return true;
				}
			case ALLEGRO_KEY_ENTER: { submit = true; break; }
			}
		}
	}

	if (submit)
	{
		submit = false;

		/* converting to regular strings */
		username_str = al_cstr(username);
		password_str = al_cstr(password);
		confirm_password_str = al_cstr(confirm_password);
		age_str = al_cstr(age);
		gender_str = al_cstr(gender);
		
		/* console output */
		cout << "-------------------------" << endl;
		cout << "Add music forms current input:" << endl;
		cout << "Username: \"" << username_str << "\"" << endl;
		cout << "Password: \"" << password_str << "\"" << endl;
		cout << "Confirm Password: \"" << confirm_password_str << "\"" << endl;
		cout << "Age: \"" << age_str << "\"" << endl;
		cout << "Gender: \"" << gender_str << "\"" << endl;
		cout << "-------------------------" << endl;

		/* verifying account */
		if (username_str == "" || password_str == "" || confirm_password_str == "" ||
			age_str == "" || gender_str == "")
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "You left one or more forms empty.\nPlease fill in all of the information.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. One or more of the forms is empty." << endl;
		}
		else if (StateControl::GetInstance()->radio.UsernameExists(username_str))
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "That username has already been chosen.\nInsert a different username.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. That username already exists." << endl;
		}
		else if (password_str != confirm_password_str)
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "The passwords entered are not the same.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. The passwords entered are not the same." << endl;
		}
		else if (atoi(age_str.c_str()) < 1 || 200 < atoi(age_str.c_str()))
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "Incorrect age.\nPlease insert a valid age.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. The age is incorrect." << endl;
		}
		else if (gender_str != "Male" && gender_str != "Female")
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "Incorrect gender.\nPlease type exactly \"Male\" or \"Female\".", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. The gender is incorrect." << endl;
		}
		else
		{
			cout << "Adding new user data..." << endl;
			StateControl::GetInstance()->radio.AddUser(username_str, password_str, atoi(age_str.c_str()), gender_str);

			/* going to user page */
			StateControl::GetInstance()->ChangeState(Login);
			return true;
		}

		return true;
	}
	return false;
}

void SignUpState::Draw()
{
	/* drawing background */
	al_draw_bitmap(sign_up_screen, 0, 0, NULL);

	/* drawing form outlines */
	if (username_form_active) { al_draw_rectangle(175, 104, 626, 185, Yellow, 1.0); }
	else if (password_form_active) { al_draw_rectangle(175, 208, 626, 289, Yellow, 1.0); }
	else if (confirm_password_form_active) { al_draw_rectangle(175, 312, 626, 393, Yellow, 1.0); }
	else if (age_form_active) { al_draw_rectangle(176, 416, 276, 497, Yellow, 1.0); }
	else if (gender_form_active) { al_draw_rectangle(325, 416, 626, 497, Yellow, 1.0); }

	/* displaying text in the forms */
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 130, 0, username);
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 234, 0, hidden_password);
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 338, 0, hidden_confirm_password);
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 442, 0, age);
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 340, 442, 0, gender);

	/* confirm button hover */
	if (190 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 298 &&
		515 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 550)
	{
		al_draw_rectangle(190, 515, 298, 550, LightBlue, 1.0);
	}
	/* cancel button hover */
	else if (510 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 603 &&
		515 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 550)
	{
		al_draw_rectangle(510, 515, 603, 550, LightBlue, 1.0);
	}
}

void SignUpState::Terminate()
{
	al_destroy_bitmap(sign_up_screen);

	al_ustr_free(username);
	al_ustr_free(password);
	al_ustr_free(confirm_password);
}

bool SignUpState::AllFormsInactive()
{
	if (username_form_active == false &&
		password_form_active == false &&
		confirm_password_form_active == false &&
		age_form_active == false &&
		gender_form_active == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SignUpState::DeactivateAllForms()
{
	cout << "Deactivating all forms..." << endl;
	username_form_active = false;
	password_form_active = false;
	confirm_password_form_active = false;
	age_form_active = false;
	gender_form_active = false;
}