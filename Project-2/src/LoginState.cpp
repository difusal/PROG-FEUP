#include "LoginState.h"
#include "StateControl.h"

void LoginState::Initialize()
{
	login_screen = al_load_bitmap(LoginScreen);
	if (!login_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load login background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	submit = false;
	username_form_active = password_form_active = false;
	username = al_ustr_new("");
	password = al_ustr_new("");
	hidden_password = al_ustr_new("");
}

bool LoginState::Update(ALLEGRO_EVENT * ev)
{
	/* scanning keyboard hits */
	al_get_keyboard_state(&keyboard_state);

	/* --- if tab pressed and no form is active, select first form --- */
	if (username_form_active == false && password_form_active == false &&
		ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_TAB)
	{
		username_form_active = true;
		password_form_active = false;
		return true;
	}

	/* username form pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 626 &&
		234 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 315)
	{
		username_form_active = true;
		password_form_active = false;
		return true;
	}
	/* password form pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		175 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 626 &&
		364 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 444)
	{
		username_form_active = false;
		password_form_active = true;
		return true;
	}
	/* confirm button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		336 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 465 &&
		480 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 517)
	{
		submit = true;
	}
	/* sign up button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		670 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 775 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		StateControl::GetInstance()->ChangeState(SignUp);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released)
	{
		username_form_active = false;
		password_form_active = false;
		return true;
	}

	/* writing username */
	if (username_form_active)
	{
		/* --- keyboard input --- */
		if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (al_ustr_size(username) < 21)
			{
				if (al_key_down(&keyboard_state, ALLEGRO_KEY_RSHIFT) ||
					al_key_down(&keyboard_state, ALLEGRO_KEY_LSHIFT))
				{
					cout << "* Shift is being held *" << endl;
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(username, "Q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(username, "W"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(username, "E"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(username, "R"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(username, "T"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(username, "Y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(username, "U"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(username, "I"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(username, "O"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(username, "P"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(username, "A"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(username, "S"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(username, "D"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(username, "F"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(username, "G"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(username, "H"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(username, "J"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(username, "K"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(username, "L"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(username, "Z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(username, "X"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(username, "C"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(username, "V"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(username, "B"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(username, "N"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(username, "M"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(username, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(username, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(username, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(username, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(username, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(username, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(username, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(username, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(username, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(username, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(username, " "); break; }
					}
				}
				else
				{
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(username, "q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(username, "w"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(username, "e"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(username, "r"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(username, "t"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(username, "y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(username, "u"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(username, "i"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(username, "o"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(username, "p"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(username, "a"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(username, "s"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(username, "d"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(username, "f"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(username, "g"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(username, "h"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(username, "j"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(username, "k"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(username, "l"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(username, "z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(username, "x"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(username, "c"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(username, "v"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(username, "b"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(username, "n"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(username, "m"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(username, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(username, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(username, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(username, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(username, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(username, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(username, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(username, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(username, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(username, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(username, " "); break; }
					}
				}
			}
			switch(ev->keyboard.keycode)
			{
				/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
			case ALLEGRO_KEY_BACKSPACE: { al_ustr_remove_chr(username, al_ustr_offset(username, -1)); break; }
			case ALLEGRO_KEY_TAB: { username_form_active = false; password_form_active = true; return true; }
			case ALLEGRO_KEY_ENTER: { submit = true; break; }
			}
		}
	}
	/* writing password */
	if (password_form_active)
	{
		/* --- keyboard input --- */
		if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (al_ustr_size(password) < 21)
			{
				switch(ev->keyboard.keycode)
				{
					/* --- LETTERS --- */
				case ALLEGRO_KEY_Q: { al_ustr_append_cstr(password, "q"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_W: { al_ustr_append_cstr(password, "w"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_E: { al_ustr_append_cstr(password, "e"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_R: { al_ustr_append_cstr(password, "r"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_T: { al_ustr_append_cstr(password, "t"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_Y: { al_ustr_append_cstr(password, "y"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_U: { al_ustr_append_cstr(password, "u"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_I: { al_ustr_append_cstr(password, "i"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_O: { al_ustr_append_cstr(password, "o"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_P: { al_ustr_append_cstr(password, "p"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_A: { al_ustr_append_cstr(password, "a"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_S: { al_ustr_append_cstr(password, "s"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_D: { al_ustr_append_cstr(password, "d"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_F: { al_ustr_append_cstr(password, "f"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_G: { al_ustr_append_cstr(password, "g"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_H: { al_ustr_append_cstr(password, "h"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_J: { al_ustr_append_cstr(password, "j"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_K: { al_ustr_append_cstr(password, "k"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_L: { al_ustr_append_cstr(password, "l"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_Z: { al_ustr_append_cstr(password, "z"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_X: { al_ustr_append_cstr(password, "x"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_C: { al_ustr_append_cstr(password, "c"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_V: { al_ustr_append_cstr(password, "v"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_B: { al_ustr_append_cstr(password, "b"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_N: { al_ustr_append_cstr(password, "n"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_M: { al_ustr_append_cstr(password, "m"); al_ustr_append_cstr(hidden_password, "*"); break; }

									/* --- NUMBERS --- */
				case ALLEGRO_KEY_0: { al_ustr_append_cstr(password, "0"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_1: { al_ustr_append_cstr(password, "1"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_2: { al_ustr_append_cstr(password, "2"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_3: { al_ustr_append_cstr(password, "3"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_4: { al_ustr_append_cstr(password, "4"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_5: { al_ustr_append_cstr(password, "5"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_6: { al_ustr_append_cstr(password, "6"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_7: { al_ustr_append_cstr(password, "7"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_8: { al_ustr_append_cstr(password, "8"); al_ustr_append_cstr(hidden_password, "*"); break; }
				case ALLEGRO_KEY_9: { al_ustr_append_cstr(password, "9"); al_ustr_append_cstr(hidden_password, "*"); break; }

									/* --- SPECIAL CHARS --- */
				case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(password, " "); al_ustr_append_cstr(password, "*"); break; }
				case ALLEGRO_KEY_BACKSPACE:
					{
						al_ustr_remove_chr(password, al_ustr_offset(password, -1));
						al_ustr_remove_chr(hidden_password, al_ustr_offset(hidden_password, -1));
						break;
					}
				case ALLEGRO_KEY_TAB: { username_form_active = true; password_form_active = false; return true; }
				case ALLEGRO_KEY_ENTER: { submit = true; break; }
				}
			}
			else
			{
				switch(ev->keyboard.keycode)
				{
					/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
				case ALLEGRO_KEY_BACKSPACE:
					{
						al_ustr_remove_chr(password, al_ustr_offset(password, -1));
						al_ustr_remove_chr(hidden_password, al_ustr_offset(hidden_password, -1));
						break;
					}
				case ALLEGRO_KEY_TAB: { username_form_active = true; password_form_active = false; return true; }
				case ALLEGRO_KEY_ENTER: { submit = true; break; }
				}
			}
		}
	}

	if (submit)
	{
		submit = false;

		/* converting to regular strings */
		username_str = al_cstr(username);
		password_str = al_cstr(password);

		/* console output */
		cout << "-------------------------" << endl;
		cout << "Login form current input:" << endl;
		cout << "User: \"" << username_str << "\"" << endl;
		cout << "Pass: \"" << password_str << "\"" << endl;
		cout << "-------------------------" << endl;

		/* verifying account */
		if (StateControl::GetInstance()->radio.UsernameExists(username_str))
		{
			if (StateControl::GetInstance()->radio.CorrectPassword(username_str, password_str))
			{
				cout << endl << "-----------------------" << endl;
				cout << "! ACCESS GRANTED !" << endl;
				cout << "! Logged in as: " << username_str << " !" << endl;
				cout << "-----------------------" << endl << endl;

				if (username_str == AdminUsername)
				{
					StateControl::GetInstance()->ChangeState(AdminAcc);
					return true;
				}
				else
				{
					cout << "Assigning variable: ActiveUserID = " << StateControl::GetInstance()->radio.GetUserID(username_str) << endl;
					StateControl::GetInstance()->ActiveUserID = StateControl::GetInstance()->radio.GetUserID(username_str);
					StateControl::GetInstance()->ChangeState(RegularAcc);
					return true;
				}
			}
			else
			{
				al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Login Error.", "The given password does not match the username.", NULL, ALLEGRO_MESSAGEBOX_WARN);
				cout << "..::Error::.. The given password does not match the username." << endl;
			}			
		}
		else
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Login Error.", "This username does not exist.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. This username does not exist." << endl;
		}

		return true;
	}

	return false;
}

void LoginState::Draw()
{
	/* drawing background */
	al_draw_bitmap(login_screen, 0, 0, NULL);

	/* username form pressed */
	if (username_form_active)
	{
		al_draw_rectangle(175, 234, 626, 315, Yellow, 1.0);
	}
	/* username form pressed */
	else if (password_form_active)
	{
		al_draw_rectangle(175, 364, 626, 444, Yellow, 1.0);
	}

	/* displaying text in the forms */
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 259, 0, username);
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 190, 389, 0, hidden_password);

	/* confirm button hover */
	if (336 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 465 &&
		480 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 517)
	{
		al_draw_rectangle(336, 480, 465, 517, LightBlue, 1.0);
	}
	/* sign up button hover */
	else if (665 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 775 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(670, 575, 775, 575, White, 1.0);
	}
}

void LoginState::Terminate()
{
	al_destroy_bitmap(login_screen);
	al_ustr_free(username);
	al_ustr_free(password);
	al_ustr_free(hidden_password);
}