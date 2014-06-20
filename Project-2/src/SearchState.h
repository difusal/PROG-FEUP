#pragma once

#include "stdIncludes.h"
#include "State.h"

class SearchState: public State
{
public:
	virtual void Initialize();
	bool Update(ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int page_to_display, last_page, id_of_first_music_on_page;

	bool update_search_results, search_form_active;

	int left_click_menu_source_x, left_click_menu_source_y;

	ALLEGRO_KEYBOARD_STATE keyboard_state;
	ALLEGRO_USTR * search;
	string search_str;

	ALLEGRO_BITMAP * top_ten_screen;
	ALLEGRO_BITMAP * acc1;
	ALLEGRO_BITMAP * acc2;
	ALLEGRO_BITMAP * acc3;
	ALLEGRO_BITMAP * acc4;
};