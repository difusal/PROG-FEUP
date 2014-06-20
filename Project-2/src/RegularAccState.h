#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "StateControl.h"
#include "Music.h"

class RegularAccState: public State
{
public:
	virtual void Initialize();
	bool Update(ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int page_to_display, last_page, id_of_first_music_on_page;

	int left_click_menu_source_x, left_click_menu_source_y;
	bool show_right_click_menu;
	int right_click_menu_upper_left_x, right_click_menu_upper_left_y;
	int right_click_menu_source_x, right_click_menu_source_y;

	ALLEGRO_BITMAP * right_click_menu;
	ALLEGRO_BITMAP * regular_acc_screen;
	ALLEGRO_BITMAP * acc1;
	ALLEGRO_BITMAP * acc2;
	ALLEGRO_BITMAP * acc3;
	ALLEGRO_BITMAP * acc4;
};