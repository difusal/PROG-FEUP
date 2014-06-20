#pragma once

#include "stdIncludes.h"
#include "State.h"

class ManageMusicsState: public State
{
public:
	virtual void Initialize();
	bool Update(ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int page_to_display, last_page, id_of_first_music_on_page;

	bool show_edit_remove_menu, show_edit_add_menu;
	int right_click_menu_upper_left_x, right_click_menu_upper_left_y;
	int right_click_menu_source_x, right_click_menu_source_y;

	ALLEGRO_BITMAP * edit_remove_menu;
	ALLEGRO_BITMAP * edit_add_menu;
	ALLEGRO_BITMAP * manage_music_screen;
	ALLEGRO_BITMAP * acc1;
	ALLEGRO_BITMAP * acc2;
	ALLEGRO_BITMAP * acc3;
	ALLEGRO_BITMAP * acc4;
};