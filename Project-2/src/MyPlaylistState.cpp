#include "MyPlaylistState.h"
#include "MyPlaylistState.h"

void MyPlaylistState::Initialize()
{
	background_screen = al_load_bitmap(MyPlaylistScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	right_click_menu = al_load_bitmap(RemoveMenu);
	if (!background_screen || !acc1 || !acc2 ||
		!acc3 || !acc4 || !right_click_menu)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more images.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* updating playlist info */
	StateControl::GetInstance()->radio.UpdateMyPlayList();
	page_to_display = 0;
}

bool MyPlaylistState::Update(ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetAvailableMusicsList().size() / 29;

	/* left mouse button pressed twice */
	if (StateControl::GetInstance()->left_mouse_button_pressed_twice &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMyPlayList().size() - (28 * page_to_display)) * 20) + 20))
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
				StateControl::GetInstance()->music_playing_title = StateControl::GetInstance()->radio.GetMusicsList()[StateControl::GetInstance()->radio.GetMyPlayList()[i + (28 * page_to_display)]].GetTitle();
				/* incrementing play count */
				StateControl::GetInstance()->radio.AddPlayToUserAndMusic(StateControl::GetInstance()->radio.GetMyPlayList()[i + (28 * page_to_display)]);
				cout << "Playing " << StateControl::GetInstance()->music_playing_title << endl;
			}
		}
		return true;
	}

	/* right mouse button pressed */
	if (StateControl::GetInstance()->right_mouse_button_released &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 655 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 516 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMyPlayList().size() - (28 * page_to_display)) * 20) + 20))
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
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMyPlayList().size() - (28 * page_to_display)) * 20) + 20))
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
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetMyPlayList().size() - (28 * page_to_display)) * 20) + 20))
	{
		cout << "Opening alternative right menu context..." << endl;
		show_right_click_menu = true;
		right_click_menu_source_x = StateControl::GetInstance()->mouse_x;
		right_click_menu_source_y = StateControl::GetInstance()->mouse_y;
		right_click_menu_upper_left_x = StateControl::GetInstance()->mouse_x - 145;
		right_click_menu_upper_left_y = StateControl::GetInstance()->mouse_y - 42;
		return true;
	}
	/* if left mouse button pressed out of right menu context, close it */
	if (StateControl::GetInstance()->left_mouse_button_released && show_right_click_menu &&
		((StateControl::GetInstance()->mouse_x < right_click_menu_upper_left_x || right_click_menu_upper_left_x + 145 < StateControl::GetInstance()->mouse_x) ||
		(StateControl::GetInstance()->mouse_y < right_click_menu_upper_left_y || right_click_menu_upper_left_y + 42 < StateControl::GetInstance()->mouse_y)))
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
				cout << "Removing from playlist... ";
				StateControl::GetInstance()->radio.RemoveMusicFromPlayList(StateControl::GetInstance()->radio.GetMyPlayList()[i + (28 * page_to_display)]);
			}
		}
		show_right_click_menu = false;
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

	return false;
}

void MyPlaylistState::Draw()
{
	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(background_screen, 0, 0, NULL); }
		case 1: { al_draw_bitmap(acc1, 0, 0, NULL); }
		case 2: { al_draw_bitmap(acc2, 0, 0, NULL); }
		case 3: { al_draw_bitmap(acc3, 0, 0, NULL); }
		case 4: { al_draw_bitmap(acc4, 0, 0, NULL); }
		}

		for (unsigned int k = 0, pos = 0; k < StateControl::GetInstance()->radio.GetMyPlayList().size(); k++)
		{
			for (unsigned int i = 0; i < StateControl::GetInstance()->radio.GetAvailableMusicsList().size(); i++)
			{
				_IDNum currentID = StateControl::GetInstance()->radio.GetAvailableMusicsList()[i].GetID();
				if (currentID == StateControl::GetInstance()->radio.GetMyPlayList()[k])
				{
					switch (j)
					{
					case 0: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 154, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetTitle().c_str()); break; }
					case 1: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 310, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetArtist().c_str()); break; }
					case 2: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 460, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetAlbum().c_str()); break; }
					case 3: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 585, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetGenre().c_str()); break; }
					case 4: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 648, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetYear().c_str()); break; }
					case 5:
						{
							ss.str(string());
							ss << StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetLikes();
							al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 692, 24 + (pos * 20), NULL, ss.str().c_str());
							break;
						}
					case 6:
						{
							ss.str(string());
							ss << StateControl::GetInstance()->radio.GetMusicsList()[currentID].GetDislikes();
							al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 738, 24 + (pos * 20), NULL, ss.str().c_str());
							break;
						}
					}

					pos++;
				}
			}
		}
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
			al_draw_line(right_click_menu_upper_left_x + 17, right_click_menu_upper_left_y + 31, right_click_menu_upper_left_x + 96, right_click_menu_upper_left_y + 31, DarkGray, 2.0);
		}
	}

	/* go back button hover */
	if (33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(33, 575, 120, 575, DarkGray, 1.0);
	}
}

void MyPlaylistState::Terminate()
{
	al_destroy_bitmap(background_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}