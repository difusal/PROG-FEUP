#include "TopTenState.h"
#include "RadioStation.h"

void TopTenState::Initialize()
{
	top_ten_screen = al_load_bitmap(TopTenScreen);
	acc1 = al_load_bitmap(AccScreen1);
	acc2 = al_load_bitmap(AccScreen2);
	acc3 = al_load_bitmap(AccScreen3);
	acc4 = al_load_bitmap(AccScreen4);
	if (!top_ten_screen || !acc1 || !acc2 ||
		!acc3 || !acc4)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more images.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* updating top ten info */
	StateControl::GetInstance()->radio.UpdateTopTenList();
	page_to_display = 0;
}

bool TopTenState::Update(ALLEGRO_EVENT * ev)
{
	/* getting number of pages */
	last_page = StateControl::GetInstance()->radio.GetAvailableMusicsList().size() / 29;

	/* left mouse button pressed twice */
	if (StateControl::GetInstance()->left_mouse_button_pressed_twice &&
		150 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 800 &&
		20 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 580 &&
		StateControl::GetInstance()->mouse_y < (int)(((StateControl::GetInstance()->radio.GetTopTenList().size() - (28 * page_to_display)) * 20) + 20))
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
				StateControl::GetInstance()->music_playing_title = StateControl::GetInstance()->radio.GetTopTenList()[i + (28 * page_to_display)].GetTitle();
				/* incrementing play count */
				if (0 == StateControl::GetInstance()->ActiveUserID || StateControl::GetInstance()->PreviousState == AdminAcc)
				{
					StateControl::GetInstance()->radio.AddPlayToMusic(i + (28 * page_to_display));
				}
				else
				{
					StateControl::GetInstance()->radio.AddPlayToUserAndMusic(i + (28 * page_to_display));
				}
				
				cout << "Playing " << StateControl::GetInstance()->music_playing_title << endl;
			}
		}
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

void TopTenState::Draw()
{
	/* printing musics */
	stringstream ss;
	for (unsigned int j = 0; j < 7; j++)
	{
		switch (j)
		{
		case 0: { al_draw_bitmap(top_ten_screen, 0, 0, NULL); }
		case 1: { al_draw_bitmap(acc1, 0, 0, NULL); }
		case 2: { al_draw_bitmap(acc2, 0, 0, NULL); }
		case 3: { al_draw_bitmap(acc3, 0, 0, NULL); }
		case 4: { al_draw_bitmap(acc4, 0, 0, NULL); }
		}

		for (unsigned int i = 0, pos = 0; i < StateControl::GetInstance()->radio.GetTopTenList().size(); i++, pos++)
		{
			switch (j)
			{
			case 0: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 154, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetTopTenList()[i].GetTitle().c_str()); break; }
			case 1: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 310, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetTopTenList()[i].GetArtist().c_str()); break; }
			case 2: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 460, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetTopTenList()[i].GetAlbum().c_str()); break; }
			case 3: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 585, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetTopTenList()[i].GetGenre().c_str()); break; }
			case 4: { al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 648, 24 + (pos * 20), NULL, StateControl::GetInstance()->radio.GetTopTenList()[i].GetYear().c_str()); break; }
			case 5:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetTopTenList()[i].GetLikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 692, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			case 6:
				{
					ss.str(string());
					ss << StateControl::GetInstance()->radio.GetTopTenList()[i].GetDislikes();
					al_draw_text(StateControl::GetInstance()->musics_font, DarkGray, 738, 24 + (pos * 20), NULL, ss.str().c_str());
					break;
				}
			}
		}
	}
	
	/* go back button hover */
	if (33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{
		al_draw_line(33, 575, 120, 575, DarkGray, 1.0);
	}
}

void TopTenState::Terminate()
{
	al_destroy_bitmap(top_ten_screen);
	al_destroy_bitmap(acc1);
	al_destroy_bitmap(acc2);
	al_destroy_bitmap(acc3);
	al_destroy_bitmap(acc4);
}