#include "CompetitionState.h"
#include "FileManager.h"

/* generates random numbers */
int random_number (int min, int max)
{
	max++;

	return ((rand() % (max-min)) + min);
}

void CompetitionState::Initialize()
{
	competition_screen = al_load_bitmap(CompetitionScreen);
	if (!competition_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more images.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	submit = false;
	show_winner = false;
	form_active = false;
	input = al_ustr_new("");
}

bool CompetitionState::Update(ALLEGRO_EVENT * ev)
{
	/* --- if tab pressed and no form is active, select first form --- */
	if (form_active == false && ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_TAB)
	{
		form_active = true;
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
	/* submit button pressed */
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		544 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 622 &&
		333 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 355)
	{
		cout << "Submit button pressed..." << endl;
		submit = true;
		return true;
	}

	/* form pressed */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		38 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 488 &&
		303 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 383)
	{
		form_active = true;
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released)
	{
		form_active = false;
		return true;
	}

	/* writing number */
	if (form_active)
	{
		/* --- keyboard input --- */
		if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (al_ustr_size(input) < 3)
			{
				switch(ev->keyboard.keycode)
				{
					/* --- NUMBERS --- */
				case ALLEGRO_KEY_0: { al_ustr_append_cstr(input, "0"); break; }
				case ALLEGRO_KEY_1: { al_ustr_append_cstr(input, "1"); break; }
				case ALLEGRO_KEY_2: { al_ustr_append_cstr(input, "2"); break; }
				case ALLEGRO_KEY_3: { al_ustr_append_cstr(input, "3"); break; }
				case ALLEGRO_KEY_4: { al_ustr_append_cstr(input, "4"); break; }
				case ALLEGRO_KEY_5: { al_ustr_append_cstr(input, "5"); break; }
				case ALLEGRO_KEY_6: { al_ustr_append_cstr(input, "6"); break; }
				case ALLEGRO_KEY_7: { al_ustr_append_cstr(input, "7"); break; }
				case ALLEGRO_KEY_8: { al_ustr_append_cstr(input, "8"); break; }
				case ALLEGRO_KEY_9: { al_ustr_append_cstr(input, "9"); break; }
				}
			}
			switch(ev->keyboard.keycode)
			{
				/* --- KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE --- */
			case ALLEGRO_KEY_BACKSPACE: { al_ustr_remove_chr(input, al_ustr_offset(input, -1)); break; }
			case ALLEGRO_KEY_TAB: { form_active = false; return true; }
			case ALLEGRO_KEY_ENTER: { submit = true; break; }
			}
		}
	}

	if (submit)
	{
		submit = false;

		/* converting input to int */
		sequence_size = atoi(al_cstr(input));

		/* console output */
		cout << "-------------------------" << endl;
		cout << "Input: " << sequence_size << endl;
		cout << "-------------------------" << endl;

		if (StateControl::GetInstance()->radio.GetUsersList().size() < 2)
		{
			cout << "..:: ERROR ::.. Could not start a competition. There are no users registered." << endl;
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Competition Error.", "Could not start a competition.\nThere are no users registered.", NULL, ALLEGRO_MESSAGEBOX_WARN);
		}
		else if (sequence_size == 0)
		{
			cout << "..:: ERROR ::.. Could not start a competition. Choose a valid number of musics to play." << endl;
			al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Ups! Competition Error.", "Could not start a competition.\nChoose a valid number of musics to be played.", NULL, ALLEGRO_MESSAGEBOX_WARN);
		}
		else
		{
			vector<_IDNum> random_sequence;
			_IDNum id_to_add;

			// creating random sequence of available musics
			cout << "Random Sequence:";
			for (int i = 0; i < sequence_size; i++)
			{
				bool available = false;
				while (!available)
				{
					id_to_add = random_number(0, StateControl::GetInstance()->radio.GetMusicsList().size() - 1);
					if (StateControl::GetInstance()->radio.GetMusicsList()[id_to_add].GetAvailability())
					{ available = true; }
				}
				random_sequence.push_back(id_to_add);
				cout << " " << id_to_add;
			}
			cout << endl;

			// creating scores vector
			struct Score { _IDNum ID; int score; };
			vector<Score> competition_scores;
			for (_IDNum i = 1; i < StateControl::GetInstance()->radio.GetUsersList().size(); i++)
			{
				Score temp_score;

				temp_score.ID = i;
				temp_score.score = 0;	// resetting score

				competition_scores.push_back(temp_score);
			}
			cout << "Competition scores size: " << competition_scores.size() << endl;

			// registering user scores
			vector<_IDNum> user_playlist;
			// updating info for every user
			for (_IDNum current_user = 1; current_user < StateControl::GetInstance()->radio.GetUsersList().size(); current_user++)
			{
				// reading current user playlist
				user_playlist = ReadUserPlaylistFromCsvToVec(current_user);
				cout << "User ID: " << current_user << "\tPlaylist size: " << user_playlist.size() << endl;

				// going through every song on random sequence
				for (int j = 0; j < sequence_size; j++)
				{
					// going through every songs on user playlist
					for (unsigned int k = 0; k < user_playlist.size(); k++)
					{
						// increment score if match found
						if (random_sequence[j] == user_playlist[k])
						{
							if (GetMusicPlaysFromUserDetails(current_user, user_playlist[k]) == 0)
							{ competition_scores[current_user-1].score += 1; }
							else
							{ competition_scores[current_user-1].score += GetMusicPlaysFromUserDetails(current_user, user_playlist[k]); }

							break;
						}
					}
				}
			}

			// showing results in console for debugging
			cout << "Competition Results:" << endl;
			for (unsigned int i = 0; i < competition_scores.size(); i++)
			{
				cout << "ID: " << competition_scores[i].ID << "\tScore: " << competition_scores[i].score << endl;
			}

			// assigning a winner
			int maximum_score = 0;
			winner = al_ustr_new(StateControl::GetInstance()->radio.GetUsersList()[0].GetUsername().c_str());
			for (unsigned int current_user = 0; current_user < competition_scores.size(); current_user++)
			{
				if (competition_scores[current_user].score > maximum_score)
				{
					maximum_score = competition_scores[current_user].score;
					winner = al_ustr_new(StateControl::GetInstance()->radio.GetUsersList()[current_user+1].GetUsername().c_str());
				}
			}

			// display winner on screen
			show_winner = true;
		}

		return true;
	}

	return false;
}

void CompetitionState::Draw()
{
	/* drawing background */
	al_draw_bitmap(competition_screen, 0, 0, NULL);

	/* username form pressed */
	if (form_active)
	{ al_draw_rectangle(38, 303, 488, 383, Yellow, 1.0); }

	/* displaying text in the forms */
	al_draw_ustr(StateControl::GetInstance()->forms_font, Black, 53, 328, 0, input);

	if (show_winner)
	{
		al_draw_ustr(StateControl::GetInstance()->forms_font, DarkGray, 125, 443, 0, winner);
	}

	/* submit button hover */
	if (544 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 622 &&
		333 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 355)
	{ al_draw_rectangle(544, 333, 622, 355, LightBlue, 1.0); }
	/* go back button hover */
	else if (33 < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < 120 &&
		555 < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < 575)
	{ al_draw_line(33, 575, 120, 575, DarkGray, 1.0); }
}

void CompetitionState::Terminate()
{
	al_destroy_bitmap(competition_screen);
}