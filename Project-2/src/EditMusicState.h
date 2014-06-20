#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "StateControl.h"

class EditMusicState: public State
{
public:
	virtual void Initialize();
	bool Update(ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

	bool AllFormsInactive();
	void DeactivateAllForms();

private:
	ALLEGRO_KEYBOARD_STATE keyboard_state;

	ALLEGRO_BITMAP * add_music_screen;
	ALLEGRO_USTR * allegro_active_string;
	ALLEGRO_USTR * title;
	ALLEGRO_USTR * artist;
	ALLEGRO_USTR * author;
	ALLEGRO_USTR * album;
	ALLEGRO_USTR * genre;
	ALLEGRO_USTR * year;

	_IDNum ID;
	string title_str, artist_str, author_str, album_str, genre_str, year_str;
	int likes, dislikes, plays; bool availability;
	bool submit;
	bool title_form_active, artist_form_active, author_form_active, album_form_active, genre_form_active, year_form_active, availability_box_checked;
};