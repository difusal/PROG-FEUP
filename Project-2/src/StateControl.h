#pragma once

#include "stdIncludes.h"
#include "RadioStation.h"
#include "Music.h"
#include "User.h"
#include "LoginState.h"
#include "SignUpState.h"
#include "AdminAccState.h"
#include "RegularAccState.h"
#include "ManageMusicsState.h"
#include "AddMusicState.h"
#include "EditMusicState.h"
#include "TopTenState.h"
#include "MyPlaylistState.h"
#include "SearchState.h"
#include "CompetitionState.h"

class State;

enum _screenState
{
	Login,
	SignUp,
	AdminAcc,
	RegularAcc,
	ManageMusics,
	AddMusic,
	EditMusic,
	TopTen,
	MyPlaylist,
	Search,
	Competition
};

class StateControl
{
public:
	void Initialize();
	void CreateAllegroDisplay();
	void LoadFonts();
	void start_radio();
	void Terminate();

	static StateControl * GetInstance();
	void ChangeState(int newState);

	ALLEGRO_DISPLAY * GetDisplay() { return display; }

	_IDNum ActiveUserID;
	_IDNum MusicID;
	_screenState PreviousState;

	int mouse_x, mouse_y;

	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	bool left_mouse_button_pressed_twice;
	bool right_mouse_button_pressed;
	bool right_mouse_button_released;

	bool playing_music;
	unsigned int music_time_counter;
	string music_playing_title;

	ALLEGRO_FONT * forms_font;
	ALLEGRO_FONT * small_forms_font;
	ALLEGRO_FONT * musics_font;
	ALLEGRO_FONT * tiny_font;
	
private:
	RadioStation radio;

	bool possible_double_press;
	unsigned int double_press_counter;
	bool done, draw;

	int player_interface_y_coord;

	StateControl();
	static StateControl * instance;

	int state;
	vector<State*> states;

	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;

	friend class RadioStation;
	friend class TopTenState;
	friend class SignUpState;
	friend class SearchState;
	friend class RegularAccState;
	friend class MyPlaylistState;
	friend class ManageMusicsState;
	friend class LoginState;
	friend const vector<_IDNum> ReadUserPlaylistFromCsvToVec();
	friend const vector<_IDNum> ReadUserPlaylistFromCsvToVec(_IDNum UserID);
	friend class EditMusicState;
	friend class AdminAccState;
	friend class AddMusicState;
	friend class Music;
	friend class CompetitionState;
};