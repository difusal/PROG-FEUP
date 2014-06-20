#include "SearchState.h"
#include "StateControl.h"

void SearchState::Initialize()
{
	top_ten_screen = al_load_bitmap(SearchScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	if (!top_ten_screen || !acc1 || !acc2 ||
		!acc3 || !acc4)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more images.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* updating top ten info */
	StateControl::GetInstance()->radio.UpdateSearchResults(StateControl::GetInstance()->radio.GetAvailableMusicsList());
	page_to_display = 0;

	search = al_ustr_new("");
	search_form_active = false;

	update_search_results = true;
}

bool SearchState::Update(ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetSearchResultsList().size() / 29;

	/* left mouse button pressed twice */
	if (StateControl::GetInstance()->left_mouse_button_pressed_twice &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetSearchResultsList().size() - (28 * page_to_display)) * 20) + 20))
	{
		left_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		left_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < left_click_menu_source_y && left_click_menu_source_y < ((20 * i) + 40))
			{
				/* placing time tracker at start */
				StateControl::GetInstance()->music_time_counter = 0;
				StateControl::GetInstance()->playing_music = true;
				/* getting title */
				StateControl::GetInstance()->music_playing_title = StateControl::GetInstance()->radio.GetSearchResultsList()[i + (28 * page_to_display)].GetTitle();
				/* incrementing play count */
				StateControl::GetInstance()->radio.AddPlayToUserAndMusic(StateControl::GetInstance()->radio.GetSearchResultsList()[i + (28 * page_to_display)].GetID());

				cout << "Playing " << StateControl::GetInstance()->music_playing_title << endl;
			}
		}
		return true;
	}

	/* go back button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		cout << "Go Back button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->PreviousState);
		return true;
	}

	/* --- scanning keyboard hits --- */
	al_get_keyboard_state(&keyboard_state);
	/* --- if tab pressed and form isn't active --- */
	if (!search_form_active && ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_TAB)
	{ search_form_active = true; return true; }

	/* --- if form is pressed --- */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		5 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 154 &&
		59 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 74)
	{ cout << "Search form active..." << endl; search_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released)
	{ search_form_active = false; return true; }

	/* ----- writing username ----- */
	if (search_form_active)
	{
		/* --- keyboard input --- */
		if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (al_ustr_size(search) < 22)
			{
				if (al_key_down(&keyboard_state, ALLEGRO_KEY_RSHIFT) ||
					al_key_down(&keyboard_state, ALLEGRO_KEY_LSHIFT))
				{
					cout << "* Shift is being held *" << endl;
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(search, "Q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(search, "W"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(search, "E"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(search, "R"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(search, "T"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(search, "Y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(search, "U"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(search, "I"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(search, "O"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(search, "P"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(search, "A"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(search, "S"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(search, "D"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(search, "F"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(search, "G"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(search, "H"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(search, "J"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(search, "K"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(search, "L"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(search, "Z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(search, "X"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(search, "C"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(search, "V"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(search, "B"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(search, "N"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(search, "M"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(search, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(search, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(search, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(search, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(search, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(search, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(search, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(search, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(search, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(search, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(search, " "); break; }
					}
				}
				else
				{
					switch(ev->keyboard.keycode)
					{
						/* --- LETTERS --- */
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(search, "q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(search, "w"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(search, "e"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(search, "r"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(search, "t"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(search, "y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(search, "u"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(search, "i"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(search, "o"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(search, "p"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(search, "a"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(search, "s"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(search, "d"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(search, "f"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(search, "g"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(search, "h"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(search, "j"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(search, "k"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(search, "l"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(search, "z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(search, "x"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(search, "c"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(search, "v"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(search, "b"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(search, "n"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(search, "m"); break; }

										/* --- NUMBERS --- */
					case ALLEGRO_KEY_0: { al_ustr_append_cstr(search, "0"); break; }
					case ALLEGRO_KEY_1: { al_ustr_append_cstr(search, "1"); break; }
					case ALLEGRO_KEY_2: { al_ustr_append_cstr(search, "2"); break; }
					case ALLEGRO_KEY_3: { al_ustr_append_cstr(search, "3"); break; }
					case ALLEGRO_KEY_4: { al_ustr_append_cstr(search, "4"); break; }
					case ALLEGRO_KEY_5: { al_ustr_append_cstr(search, "5"); break; }
					case ALLEGRO_KEY_6: { al_ustr_append_cstr(search, "6"); break; }
					case ALLEGRO_KEY_7: { al_ustr_append_cstr(search, "7"); break; }
					case ALLEGRO_KEY_8: { al_ustr_append_cstr(search, "8"); break; }
					case ALLEGRO_KEY_9: { al_ustr_append_cstr(search, "9"); break; }

										/* --- SPECIAL CHARS --- */
					case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(search, " "); break; }
					}
				}
			}

			switch(ev->keyboard.keycode)
			{
				/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
			case ALLEGRO_KEY_BACKSPACE:
				{
					al_ustr_remove_chr(search, al_ustr_offset(search, -1));
					update_search_results = true;
					return true;
				}
			case ALLEGRO_KEY_TAB:
				{
					if (search_form_active) { search_form_active = false; }
					return true;
				}
			}

			update_search_results = true;
		}
	}

	/* --- SEARCH ENGINE LOGIC --- */
	search_str = al_cstr(search);
	if (update_search_results)
	{
		/* nothing on form -> show all musics */
		if (search_str == "")
		{ StateControl::GetInstance()->radio.UpdateSearchResults(StateControl::GetInstance()->radio.GetAvailableMusicsList()); }
		else
		{
			StateControl::GetInstance()->radio.ClearSearchResults();
			for (unsigned int i = 0; i < StateControl::GetInstance()->radio.GetAvailableMusicsList().size(); i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					string haystack;
					switch (j)
					{
					case 0: { haystack = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetTitle(); break; }
					case 1: { haystack = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetArtist(); break; }
					case 2: { haystack = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetGenre(); break; }
					case 3: { haystack = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetYear(); break; }
					}

					/* if match found */
					if (al_ustr_find_str(al_ustr_new(haystack.c_str()), 0, search) != -1)
					{
						cout << "Match found!" << endl;
						StateControl::GetInstance()->radio.AddIDToSearchResults(i);
						break;
					}
				}
			}
		}

		cout << "Search results: " << StateControl::GetInstance()->radio.GetSearchResultsList().size() << endl;

		update_search_results = false;
	}

	return false;
}

void SearchState::Draw()
{
	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(top_ten_screen, 0, 0, NULL); }
		case 1: { al_draw_bitmap(acc1, 0, 0, NULL); }
		case 2: { al_draw_bitmap(acc2, 0, 0, NULL); }
		case 3: { al_draw_bitmap(acc3, 0, 0, NULL); }
		case 4: { al_draw_bitmap(acc4, 0, 0, NULL); }
		}

		for (unsigned int i = 0, pos = 0; i < StateControl::GetInstance()->radio.GetSearchResultsList().size(); i++, pos++)
		{
			switch (j)
			{
			case 0: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 154, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetTitle().c_str()); break; }
			case 1: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 310, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetArtist().c_str()); break; }
			case 2: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 460, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetAlbum().c_str()); break; }
			case 3: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 585, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetGenre().c_str()); break; }
			case 4: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 648, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetYear().c_str()); break; }
			case 5:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetLikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 692, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			case 6:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetSearchResultsList()[i].GetDislikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 738, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			}
		}
	}

	/* form outline */
	if (search_form_active) { al_draw_rectangle(5, 59, 145, 74, Yellow, 1.0); }

	/* displaying text in the forms */
	al_draw_ustr(StateControl::GetInstance()->tiny_font, DarkGray, 9, 62, 0, search);

	/* go back button hover */
	if (33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(33, 575, 120, 575, DarkGray, 1.0);
	}
}

void SearchState::Terminate()
{
	al_destroy_bitmap(top_ten_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}