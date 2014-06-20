#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "StateControl.h"
#include "Music.h"

int random_number (int min, int max);

class CompetitionState: public State
{
public:
	virtual void Initialize();
	bool Update(ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	bool submit, show_winner;
	int left_click_menu_source_x, left_click_menu_source_y;
	bool form_active;
	ALLEGRO_USTR * input;
	int sequence_size;
	ALLEGRO_USTR * winner;

	ALLEGRO_BITMAP * competition_screen;
};