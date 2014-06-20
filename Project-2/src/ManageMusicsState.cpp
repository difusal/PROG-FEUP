#include "ManageMusicsState.h"
#include "StateControl.h"
#include "Music.h"

void ManageMusicsState::Initialize()
{
	manage_music_screen = al_load_bitmap(ManageMusicsScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	edit_remove_menu = al_load_bitmap(EditRemoveMenu);
	edit_add_menu = al_load_bitmap(EditAddMenu);
	if (!manage_music_screen || !acc1 || !acc2 ||
		!acc3 || !acc4 || !edit_remove_menu || !edit_add_menu)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more images.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	show_edit_remove_menu = false;
	show_edit_add_menu = false;
	page_to_display = 0;
}

bool ManageMusicsState::Update(ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetMusicsList().size() / 29;
	if (page_to_display > last_page) { page_to_display = last_page; }

	/* right mouse button pressed */
	if (StateControl::GetInstance()->right_mouse_button_released &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 655 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 516 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMusicsList().size() - (28 * page_to_display)) * 20) + 20))
	{
		cout << "Opening right menu context..." << endl;
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Getting availability state..." << endl;
				switch (StateControl::GetInstance()->radio.GetMusicsList()[i + (28 * page_to_display)].GetAvailability())
				{
				case 1: { show_edit_remove_menu = true; show_edit_add_menu = false; break; }
				case 0: { show_edit_remove_menu = false; show_edit_add_menu = true; break; }
				}
			}
		}
		return true;
	}
	else if (StateControl::GetInstance()->right_mouse_button_released &&
		((655 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800) &&
		(20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 100)) &&
		StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetMusicsList().size() * 20) + 20))
	{
		cout << "Opening second alternative right menu context..." << endl;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Getting availability state..." << endl;
				switch (StateControl::GetInstance()->radio.GetMusicsList()[i + (28 * page_to_display)].GetAvailability())
				{
				case 1: { show_edit_remove_menu = true; show_edit_add_menu = false; break; }
				case 0: { show_edit_remove_menu = false; show_edit_add_menu = true; break; }
				}
			}
		}
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x - 145;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y;
		return true;
	}
	else if (StateControl::GetInstance()->right_mouse_button_released &&
		((655 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800) ||
		(516 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580)) &&
		StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetMusicsList().size() * 20) + 20))
	{
		cout << "Opening alternative right menu context..." << endl;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Getting availability state..." << endl;
				switch (StateControl::GetInstance()->radio.GetMusicsList()[i + (28 * page_to_display)].GetAvailability())
				{
				case 1: { show_edit_remove_menu = true; show_edit_add_menu = false; break; }
				case 0: { show_edit_remove_menu = false; show_edit_add_menu = true; break; }
				}
			}
		}
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x - 145;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y - 84;
		return true;
	}
	/* if left mouse button pressed out of right menu context, close it */
	if (StateControl::GetInstance()->left_mouse_button_released && (show_edit_remove_menu || show_edit_add_menu) &&
		((StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x || right_click_menu_upper_left_x + 145 < StateControl::GetInstance()->mouse_x) ||
		(StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y || right_click_menu_upper_left_y + 84 < StateControl::GetInstance()->mouse_y)))
	{
		cout << "Closing right menu context..." << endl;
		show_edit_remove_menu = false;
		show_edit_add_menu = false;
		return true;
	}
	/* first option selected */
	else if (StateControl::GetInstance()->left_mouse_button_released && (show_edit_remove_menu || show_edit_add_menu) &&
		right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
		StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
		right_click_menu_upper_left_y < StateControl::GetInstance()->mouse_y &&
		StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 40)
	{
		cout << "First option selected..." << endl;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Editing music..." << endl;
				/* saving ID of music to edit */
				StateControl::GetInstance()->MusicID = i + (28 * page_to_display);
				StateControl::GetInstance()->ChangeState(EditMusic);
				return true;
			}
		}
		show_edit_remove_menu = false;
		show_edit_add_menu = false;
		return true;
	}
	/* second option selected */
	else if (StateControl::GetInstance()->left_mouse_button_released && (show_edit_remove_menu || show_edit_add_menu) &&
		right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
		StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
		right_click_menu_upper_left_y + 40 < StateControl::GetInstance()->mouse_y &&
		StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 80)
	{
		cout << "Second option selected..." << endl;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Switching availability state..." << endl;
				StateControl::GetInstance()->radio.SwitchMusicAvailability(i + (28 * page_to_display));
			}
		}
		show_edit_remove_menu = false;
		show_edit_add_menu = false;
		return true;
	}

	/* if right arrow pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		480 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 487 &&
		584 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 596)
	{
		if (page_to_display != last_page)
		{
			page_to_display++;
		}		
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		463 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 470 &&
		584 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 596)
	{
		if (page_to_display != 0)
		{
			page_to_display--;
		}		
	}

	/* add new music button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		18 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 132 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		cout << "Add New Music button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(AddMusic);
		return true;
	}
	/* go back button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		cout << "Go Back button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(AdminAcc);
		return true;
	}

	return false;
}

void ManageMusicsState::Draw()
{
	id_of_first_music_on_page = 28 * page_to_display;

	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(manage_music_screen, 0, 0, NULL); }
		case 1: { al_draw_bitmap(acc1, 0, 0, NULL); }
		case 2: { al_draw_bitmap(acc2, 0, 0, NULL); }
		case 3: { al_draw_bitmap(acc3, 0, 0, NULL); }
		case 4: { al_draw_bitmap(acc4, 0, 0, NULL); }
		}

		for (unsigned int i = id_of_first_music_on_page, pos = 0; i < StateControl::GetInstance()->radio.GetMusicsList().size() && i < id_of_first_music_on_page + 28; i++, pos++)
		{
			ALLEGRO_COLOR text_color;
			switch (StateControl::GetInstance()->radio.GetMusicsList()[i].GetAvailability())
			{
			case 1: { text_color = DarkGray; break; }
			case 0: { text_color = Red; break; }
			}

			switch (j)
			{
			case 0: { al_draw_text(StateControl::GetInstance()->musics_font, text_color, 154, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[i].GetTitle().c_str()); break; }
			case 1: { al_draw_text(StateControl::GetInstance()->musics_font, text_color, 310, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[i].GetArtist().c_str()); break; }
			case 2: { al_draw_text(StateControl::GetInstance()->musics_font, text_color, 460, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[i].GetAlbum().c_str()); break; }
			case 3: { al_draw_text(StateControl::GetInstance()->musics_font, text_color, 585, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[i].GetGenre().c_str()); break; }
			case 4: { al_draw_text(StateControl::GetInstance()->musics_font, text_color, 648, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[i].GetYear().c_str()); break; }
			case 5:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetMusicsList()[i].GetLikes();
					al_draw_text(StateControl::GetInstance()->musics_font, text_color, 692, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			case 6:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetMusicsList()[i].GetDislikes();
					al_draw_text(StateControl::GetInstance()->musics_font, text_color, 738, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			}
		}
	}

	/* page count */
	ss.str(string());
	ss << "Page: " << page_to_display + 1 << "/" << last_page + 1;
	al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 154, 584, NULL, ss.str().c_str());
	ss.str(string());		// clearing stringstream content

	/* musics count */
	ss << StateControl::GetInstance()->radio.GetMusicsList().size() << " songs";
	al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 796, 584, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
	ss.str(string());		// clearing stringstream content

	/* --- page navigation --- */
	/* right arrow hover */
	if (480 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 487 &&
		584 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 596 &&
		page_to_display != last_page)
	{
		al_draw_filled_triangle(480, 596, 480, 584, 487, 590, LightGray);
	}
	/* right arrow */
	else if (page_to_display != last_page)
	{
		al_draw_filled_triangle(480, 596, 480, 584, 487, 590, DarkGray);
	}
	/* left arrow hover */
	if (463 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 470 &&
		584 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 596 &&
		page_to_display != 0)
	{
		al_draw_filled_triangle(470, 596, 470, 584, 463, 590, LightGray);
	}
	/* left arrow */
	else if (page_to_display != 0)
	{
		al_draw_filled_triangle(470, 596, 470, 584, 463, 590, DarkGray);
	}
	/* ------ */

	/* right mouse button pressed */
	if (show_edit_remove_menu || show_edit_add_menu)
	{
		/* drawing menu */
		if(show_edit_add_menu)
		{ al_draw_bitmap(edit_add_menu, right_click_menu_upper_left_x, right_click_menu_upper_left_y, NULL); }
		else if (show_edit_remove_menu)
		{ al_draw_bitmap(edit_remove_menu, right_click_menu_upper_left_x, right_click_menu_upper_left_y, NULL); }

		/* first option hover */
		if (right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
			StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
			right_click_menu_upper_left_y < StateControl::GetInstance()->mouse_y &&
			StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 40)
		{
			al_draw_line(right_click_menu_upper_left_x + 17, right_click_menu_upper_left_y + 31, right_click_menu_upper_left_x + 55, right_click_menu_upper_left_y + 31, DarkGray, 2.0);
		}
		/* second option hover */
		else if (right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
			StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
			right_click_menu_upper_left_y + 40 < StateControl::GetInstance()->mouse_y &&
			StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 80)
		{
			if(show_edit_add_menu)
			{ al_draw_line(right_click_menu_upper_left_x + 15, right_click_menu_upper_left_y + 71, right_click_menu_upper_left_x + 52, right_click_menu_upper_left_y + 71, DarkGray, 2.0); }
			else if (show_edit_remove_menu)
			{ al_draw_line(right_click_menu_upper_left_x + 17, right_click_menu_upper_left_y + 71, right_click_menu_upper_left_x + 95, right_click_menu_upper_left_y + 71, DarkGray, 2.0); }			
		}
	}

	/* add new music button hover */
	if (18 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 134 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		al_draw_line(18, 96, 134, 96, DarkGray, 1.0);
	}
	/* go back button hover */
	else if (33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(33, 575, 120, 575, DarkGray, 1.0);
	}
}

void ManageMusicsState::Terminate()
{
	al_destroy_bitmap(edit_remove_menu);
	al_destroy_bitmap(manage_music_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}