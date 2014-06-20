#include "RegularAccState.h"

void RegularAccState::Initialize()
{
	regular_acc_screen = al_load_bitmap(RegularAccScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	right_click_menu = al_load_bitmap(LikeDislikeAddMenu);
	if (!regular_acc_screen || !acc1 || !acc2 ||
		!acc3 || !acc4 || !right_click_menu)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load screen background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	StateControl::GetInstance()->radio.RefreshAvailableMusicsList();
	show_right_click_menu = false;
	page_to_display = 0;
}

bool RegularAccState::Update (ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetAvailableMusicsList().size() / 29;

	/* left mouse button pressed twice */
	if (StateControl::GetInstance()->left_mouse_button_pressed_twice &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetAvailableMusicsList().size() - (28 * page_to_display)) * 20) + 20))
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
				StateControl::GetInstance()->music_playing_title = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i + (28 * page_to_display)].GetTitle();
				/* incrementing play count */
				StateControl::GetInstance()->radio.AddPlayToUserAndMusic(StateControl::GetInstance()->radio.GetAvailableMusicsList()[i + (28 * page_to_display)].GetID());
				cout << "Playing " << StateControl::GetInstance()->music_playing_title << endl;
			}
		}
		return true;
	}
	/* right mouse button pressed */
	if (StateControl::GetInstance()->right_mouse_button_released &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 655 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 474 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetAvailableMusicsList().size() - (28 * page_to_display)) * 20) + 20))
	{
		cout << "Opening right menu context..." << endl;
		show_right_click_menu = true;
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y;
		return true;
	}
	else if (StateControl::GetInstance()->right_mouse_button_released &&
		((655 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800) &&
		(20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 100)) &&
		StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetAvailableMusicsList().size() * 20) + 20))
	{
		cout << "Opening second alternative right menu context..." << endl;
		show_right_click_menu = true;
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x - 145;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y;
		return true;
	}
	else if (StateControl::GetInstance()->right_mouse_button_released &&
		((655 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800) ||
		(474 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580)) &&
		StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetAvailableMusicsList().size() * 20) + 20))
	{
		cout << "Opening alternative right menu context..." << endl;
		show_right_click_menu = true;
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x - 145;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y - 84;
		return true;
	}
	/* if left mouse button pressed out of right menu context, close it */
	if (StateControl::GetInstance()->left_mouse_button_released && show_right_click_menu &&
		((StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x || right_click_menu_upper_left_x + 145 < StateControl::GetInstance()->mouse_x) ||
		(StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y || right_click_menu_upper_left_y + 124 < StateControl::GetInstance()->mouse_y)))
	{
		cout << "Closing right menu context..." << endl;
		show_right_click_menu = false;
		return true;
	}
	/* first option selected */
	else if (StateControl::GetInstance()->left_mouse_button_released && show_right_click_menu &&
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
				StateControl::GetInstance()->radio.AddUserLike(i + (28 * page_to_display));
			}
		}
		show_right_click_menu = false;
		return true;
	}
	/* second option selected */
	else if (StateControl::GetInstance()->left_mouse_button_released && show_right_click_menu &&
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
				StateControl::GetInstance()->radio.AddUserDislike(i + (28 * page_to_display));
			}
		}
		show_right_click_menu = false;
		return true;
	}
	/* third option selected */
	else if (StateControl::GetInstance()->left_mouse_button_released && show_right_click_menu &&
		right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
		StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
		right_click_menu_upper_left_y + 80 < StateControl::GetInstance()->mouse_y &&
		StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 120)
	{
		cout << "Third option selected..." << endl;
		for (int i = 0; i < 28; i++)
		{
			if ((20 * i) + 20 < right_click_menu_source_y && right_click_menu_source_y < ((20 * i) + 40))
			{
				cout << "Adding music to playlist..." << endl;
				StateControl::GetInstance()->radio.AddMusicToPlayList(StateControl::GetInstance()->radio.GetAvailableMusicsList()[i + (28 * page_to_display)].GetID());
			}
		}
		show_right_click_menu = false;
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

	/* my playlist button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		37 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 116 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		cout << "Manage Musics button pressed..." << endl;
		StateControl::GetInstance()->PreviousState = RegularAcc;
		StateControl::GetInstance()->ChangeState(MyPlaylist);
		return true;
	}
	/* top ten button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		45 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 105 &&
		132 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 148)
	{
		cout << "Top Ten button pressed..." << endl;
		StateControl::GetInstance()->PreviousState = RegularAcc;
		StateControl::GetInstance()->ChangeState(TopTen);
		return true;
	}
	/* search button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		50 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 100 &&
		185 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 200)
	{
		cout << "Search button pressed..." << endl;
		StateControl::GetInstance()->PreviousState = RegularAcc;
		StateControl::GetInstance()->ChangeState(Search);
		return true;
	}
	/* logout button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		40 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 110 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		cout << "Logout button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(Login);
		return true;
	}

	return false;
}

void RegularAccState::Draw()
{
	id_of_first_music_on_page = 28 * page_to_display;

	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(regular_acc_screen, 0, 0, NULL); }
		case 1: { al_draw_bitmap(acc1, 0, 0, NULL); }
		case 2: { al_draw_bitmap(acc2, 0, 0, NULL); }
		case 3: { al_draw_bitmap(acc3, 0, 0, NULL); }
		case 4: { al_draw_bitmap(acc4, 0, 0, NULL); }
		}

		for (unsigned int i = id_of_first_music_on_page, pos = 0; i < StateControl::GetInstance()->radio.GetAvailableMusicsList().size() && i < id_of_first_music_on_page + 28; i++, pos++)
		{
			int pos_x = 24 + (pos * 20);

			switch (j)
			{
			case 0: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 154, pos_x, NULL, StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetTitle().c_str()); break; }
			case 1: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 310, pos_x, NULL, StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetArtist().c_str()); break; }
			case 2: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 460, pos_x, NULL, StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetAlbum().c_str()); break; }
			case 3: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 585, pos_x, NULL, StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetGenre().c_str()); break; }
			case 4: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 648, pos_x, NULL, StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetYear().c_str()); break; }
			case 5:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetLikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 692, pos_x, NULL, ss.str().c_str());
					break;
				}
			case 6:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetDislikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 738, pos_x, NULL, ss.str().c_str());
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
	ss << StateControl::GetInstance()->radio.GetAvailableMusicsList().size() << " songs";
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

	/* right mouse button pressed */
	if (show_right_click_menu)
	{
		/* drawing menu */
		al_draw_bitmap(right_click_menu, right_click_menu_upper_left_x, right_click_menu_upper_left_y, NULL);

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
			al_draw_line(right_click_menu_upper_left_x + 17, right_click_menu_upper_left_y + 71, right_click_menu_upper_left_x + 81, right_click_menu_upper_left_y + 71, DarkGray, 2.0);
		}
		/* third option hover */
		else if (right_click_menu_upper_left_x < StateControl::GetInstance()->mouse_x &&
			StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x + 140 &&
			right_click_menu_upper_left_y + 80 < StateControl::GetInstance()->mouse_y &&
			StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y + 120)
		{
			al_draw_line(right_click_menu_upper_left_x + 17, right_click_menu_upper_left_y + 111, right_click_menu_upper_left_x + 117, right_click_menu_upper_left_y + 111, DarkGray, 2.0);
		}
	}

	/* my playlist button hover */
	if (37 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 116 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		al_draw_line(37, 96, 116, 96, DarkGray, 1.0);
	}
	/* top ten button hover */
	if (45 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 105 &&
		132 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 148)
	{
		al_draw_line(45, 148, 105, 148, DarkGray, 1.0);
	}
	/* search button pressed */
	if (50 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 100 &&
		185 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 200)
	{
		al_draw_line(50, 200, 102, 200, DarkGray, 1.0);
	}
	/* logout button hover */
	else if (40 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 110 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(40, 575, 110, 575, DarkGray, 1.0);
	}
}

void RegularAccState::Terminate()
{
	al_destroy_bitmap(right_click_menu);
	al_destroy_bitmap(regular_acc_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}