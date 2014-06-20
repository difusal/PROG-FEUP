#include "AdminAccState.h"

void AdminAccState::Initialize()
{
	admin_acc_screen = al_load_bitmap(AdminAccScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	right_click_menu = al_load_bitmap(LikeDislikeMenu);
	if (!admin_acc_screen || !acc1 || !acc2 ||
		!acc3 || !acc4 || !right_click_menu)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load screen background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	show_right_click_menu = false;
	page_to_display = 0;
}

bool AdminAccState::Update (ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetMusicsList().size() / 29;
	
	/* left mouse button pressed twice */
	if (StateControl::GetInstance()->left_mouse_button_pressed_twice &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMusicsList().size() - (28 * page_to_display)) * 20) + 20))
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
				StateControl::GetInstance()->music_playing_title = StateControl::GetInstance()->radio.GetMusicsList()[i + (28 * page_to_display)].GetTitle();
				/* incrementing play count */
				StateControl::GetInstance()->radio.AddPlayToMusic(i + (28 * page_to_display));
				cout << "Playing " << StateControl::GetInstance()->music_playing_title << endl;
			}
		}
		return true;
	}
	/* right mouse button pressed */
	if (StateControl::GetInstance()->right_mouse_button_released &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 655 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 516 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMusicsList().size() - (28 * page_to_display)) * 20) + 20))
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
		StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetMusicsList().size() * 20) + 20))
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
	(516 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580)) &&
	StateControl::GetInstance()->mouse_y < (int)((StateControl::GetInstance()->radio.GetMusicsList().size() * 20) + 20))
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
		(StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y || right_click_menu_upper_left_y + 84 < StateControl::GetInstance()->mouse_y)))
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
				cout << "Adding Like..." << endl;
				StateControl::GetInstance()->radio.AddAdminLike(i + (28 * page_to_display));
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
				cout << "Adding Dislike..." << endl;
				StateControl::GetInstance()->radio.AddAdminDislike(i + (28 * page_to_display));
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

	/* manage musics button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		18 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 130 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		cout << "Manage Musics button pressed..." << endl;
		StateControl::GetInstance()->ChangeState(ManageMusics);
		return true;
	}
	/* top ten button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		45 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 105 &&
		132 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 148)
	{
		cout << "Top Ten button pressed..." << endl;
		StateControl::GetInstance()->PreviousState = AdminAcc;
		StateControl::GetInstance()->ChangeState(TopTen);
		return true;
	}
	/* start competition button pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		8 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 144 &&
		184 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 200)
	{
		cout << "Start Competition button pressed..." << endl;
		StateControl::GetInstance()->PreviousState = AdminAcc;
		StateControl::GetInstance()->ChangeState(Competition);
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

void AdminAccState::Draw()
{
	id_of_first_music_on_page = 28 * page_to_display;

	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(admin_acc_screen, 0, 0, NULL); }
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
	}

	/* manage musics button hover */
	if (18 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 132 &&
		80 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 95)
	{
		al_draw_line(18, 96, 132, 96, DarkGray, 1.0);
	}
	/* top ten button hover */
	if (45 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 105 &&
		132 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 148)
	{
		al_draw_line(45, 148, 105, 148, DarkGray, 1.0);
	}
	/* start competition button hover */
	if (8 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 144 &&
		184 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 200)
	{
		al_draw_line(8, 200, 144, 200, DarkGray, 1.0);
	}
	/* logout button hover */
	else if (40 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 110 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(40, 575, 110, 575, DarkGray, 1.0);
	}
}

void AdminAccState::Terminate()
{
	al_destroy_bitmap(right_click_menu);
	al_destroy_bitmap(admin_acc_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}