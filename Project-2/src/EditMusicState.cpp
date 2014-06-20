#include "EditMusicState.h"

void EditMusicState::Initialize()
{
	add_music_screen = al_load_bitmap(AddMusicScreen);
	if (!add_music_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load login background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	submit = false;

	/* getting ID of music to edit */
	ID = StateControl::GetInstance()->MusicID;
	stringstream ss;

	title_form_active = false;
	title = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetTitle().c_str());

	artist_form_active = false;
	artist = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetArtist().c_str());

	author_form_active = false;
	author = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetAuthor().c_str());

	album_form_active = false;
	album = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetAlbum().c_str());

	genre_form_active = false;
	genre = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetGenre().c_str());

	year_form_active = false;
	year = al_ustr_new(StateControl::GetInstance()->radio.GetMusicsList()[ID].GetYear().c_str());

	likes = StateControl::GetInstance()->radio.GetMusicsList()[ID].GetLikes();
	dislikes = StateControl::GetInstance()->radio.GetMusicsList()[ID].GetDislikes();

	/* getting play count of music to edit */
	plays = StateControl::GetInstance()->radio.GetMusicsList()[ID].GetPlays();

	/* getting availability of music to edit */
	availability = StateControl::GetInstance()->radio.GetMusicsList()[ID].GetAvailability();
	availability_box_checked = StateControl::GetInstance()->radio.GetMusicsList()[ID].GetAvailability();
}

bool EditMusicState::Update(ALLEGRO_EVENT * ev)
{
	/* --- scanning keyboard hits --- */
	al_get_keyboard_state(&keyboard_state);

	/* --- if tab pressed and no form is active, select first form --- */
	if (AllFormsInactive() && ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_TAB)
	{ title_form_active = true; return true; }

	/* --- if a form is pressed --- */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		99 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 139)
	{ DeactivateAllForms(); title_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		151 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 191)
	{ DeactivateAllForms(); artist_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		203 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 243)
	{ DeactivateAllForms(); author_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		255 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 295)
	{ DeactivateAllForms(); album_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		307 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 347)
	{ DeactivateAllForms(); genre_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		98 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 748 &&
		359 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 399)
	{ DeactivateAllForms(); year_form_active = true; return true; }
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		147 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 186 &&
		411 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 451)
	{
		DeactivateAllForms();
		cout << "Switching availability..." << endl;
		switch (availability_box_checked)
		{
		case 0: { availability_box_checked = true; availability = 1; break; }
		case 1: { availability_box_checked = false; availability = 0; break; }
		}
		return true;
	}
	/* --- save button pressed --- */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		238 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 302 &&
		500 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 526)
	{ cout << "Save button pressed..." << endl; submit = true; }
	/* --- cancel button pressed --- */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		487 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 571 &&
		500 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 526)
	{
		cout << "Cancel button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(ManageMusics);
		return true;
	}
	/* --- pressed anywhere out of the forms --- */
	else if (StateControl::GetInstance()->left_mouse_button_released)
	{ DeactivateAllForms(); return true; }

	/* ----- writing username ----- */
	if (title_form_active || artist_form_active || author_form_active ||
		album_form_active || genre_form_active || year_form_active)
	{
		if (title_form_active) { allegro_active_string = title; }
		else if (artist_form_active) { allegro_active_string = artist; }
		else if (author_form_active) { allegro_active_string = author; }
		else if (album_form_active) { allegro_active_string = album; }
		else if (genre_form_active) { allegro_active_string = genre; }
		else if (year_form_active) { allegro_active_string = year; }

		/* --- keyboard input --- */
		if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (al_ustr_size(allegro_active_string) < 56)
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
			}

			switch(ev->keyboard.keycode)
			{
				/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
			case ALLEGRO_KEY_BACKSPACE: { al_ustr_remove_chr(allegro_active_string, al_ustr_offset(allegro_active_string, -1)); break; }
			case ALLEGRO_KEY_TAB:
				{
					if (title_form_active) { title_form_active = false; artist_form_active = true; }
					else if (artist_form_active) { artist_form_active = false; author_form_active = true; }
					else if (author_form_active) { author_form_active = false; album_form_active = true; }
					else if (album_form_active) { album_form_active = false; genre_form_active = true; }
					else if (genre_form_active) { genre_form_active = false; year_form_active = true; }
					else if (year_form_active) { year_form_active = false; }

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
		title_str = al_cstr(title);
		artist_str = al_cstr(artist);
		author_str = al_cstr(author);
		album_str = al_cstr(album);
		genre_str = al_cstr(genre);
		year_str = al_cstr(year);

		/* console output */
		cout << "-------------------------" << endl;
		cout << "Add music forms current input:" << endl;
		cout << "Title: \"" << title_str << "\"" << endl;
		cout << "Artist: \"" << artist_str << "\"" << endl;
		cout << "Author: \"" << author_str << "\"" << endl;
		cout << "Album: \"" << album_str << "\"" << endl;
		cout << "Genre: \"" << genre_str << "\"" << endl;
		cout << "Year: \"" << year_str << "\"" << endl;
		cout << "-------------------------" << endl;

		/* verifying account */
		if (title_str == "" || artist_str == "" || author_str == "" ||
			album_str == "" || genre_str == "" || year_str == "")
		{
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Form Error.", "You left one or more forms empty.\nPlease fill in all of the information.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << "..::Error::.. One or more of the forms is empty." << endl;
		}
		else
		{
			cout << "Replacing music data right now..." << endl;
			StateControl::GetInstance()->radio.EditMusic(ID, title_str, artist_str, author_str, album_str, genre_str, year_str, likes, dislikes, plays, availability);

			/* going back*/
			StateControl::GetInstance()->ChangeState(ManageMusics);
			return true;
		}

		return true;
	}

	return false;
}

void EditMusicState::Draw()
{
	/* drawing background */
	al_draw_bitmap(add_music_screen, 0, 0, NULL);

	/* drawing form outlines */
	if (title_form_active)
	{
		al_draw_rectangle(98, 99, 748, 139, Yellow, 1.0);
	}
	else if (artist_form_active)
	{
		al_draw_rectangle(98, 151, 748, 191, Yellow, 1.0);
	}
	else if (author_form_active)
	{
		al_draw_rectangle(98, 203, 748, 243, Yellow, 1.0);
	}
	else if (album_form_active)
	{
		al_draw_rectangle(98, 255, 748, 295, Yellow, 1.0);
	}
	else if (genre_form_active)
	{
		al_draw_rectangle(98, 307, 748, 347, Yellow, 1.0);
	}
	else if (year_form_active)
	{
		al_draw_rectangle(98, 359, 748, 399, Yellow, 1.0);
	}
	switch (availability_box_checked)
	{
	case true: { al_draw_filled_circle(167, 431, 8, DarkGreen); break; }
	case false: { al_draw_filled_circle(167, 431, 8, Red); break; }
	}

	/* displaying text in the forms */
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 110, 0, title);
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 162, 0, artist);
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 214, 0, author);
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 266, 0, album);
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 318, 0, genre);
	al_draw_ustr(StateControl::GetInstance()->small_forms_font, Black, 115, 370, 0, year);

	/* save button hover */
	if (238 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 302 &&
		500 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 526)
	{
		al_draw_rectangle(238, 500, 304, 526, White, 1.0);
	}
	/* cancel button hover */
	else if (487 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 571 &&
		500 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 526)
	{
		al_draw_rectangle(487, 500, 573, 526, White, 1.0);
	}
}

void EditMusicState::Terminate()
{
	al_destroy_bitmap(add_music_screen);

	al_ustr_free(title);
	al_ustr_free(artist);
	al_ustr_free(author);
	al_ustr_free(album);
	al_ustr_free(genre);
	al_ustr_free(year);
}

bool EditMusicState::AllFormsInactive()
{
	if (title_form_active == false &&
		artist_form_active == false &&
		author_form_active == false &&
		album_form_active == false &&
		genre_form_active == false &&
		year_form_active == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EditMusicState::DeactivateAllForms()
{
	cout << "Deactivating all forms..." << endl;
	title_form_active = false;
	artist_form_active = false;
	author_form_active = false;
	album_form_active = false;
	genre_form_active = false;
	year_form_active = false;
}