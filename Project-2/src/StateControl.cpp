#include "StateControl.h"
#include "RadioStation.h"

StateControl * StateControl::instance = NULL;
StateControl::StateControl(): radio ("MIEIC") {};

void StateControl::Initialize()
{
	cout << endl;
	cout << "* * * * * * * * * * * * *" << endl;
	cout << "*                       *" << endl;
	cout << "*    STARTING RADIO     *" << endl;	
	cout << "*                       *" << endl;
	cout << "* * * * * * * * * * * * *" << endl;
	cout << endl;
	cout << "-------------" << endl;
	cout << "Activity Log:" << endl;
	cout << "-------------" << endl;

	cout << "Getting time seed for random numbers..." << endl;
	srand ((unsigned int) time(NULL));

	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL);
	}

	cout << "Initializing addons..." << endl;
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();

	cout << "Creating display..." << endl;
	CreateAllegroDisplay();	
	cout << "Loading fonts..." << endl;
	LoadFonts();

	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);

	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registring event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	cout << "Initializing variables..." << endl;
	left_mouse_button_pressed = false;
	left_mouse_button_released = false;
	right_mouse_button_pressed = false;
	right_mouse_button_released = false;

	playing_music = false;

	possible_double_press = false;
	double_press_counter = 0;

	player_interface_y_coord = 380;
	music_time_counter = 0;

	cout << "Starting timers..." << endl;
	al_start_timer(timer);
}

void StateControl::CreateAllegroDisplay()
{
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	/* setting new window title */
	al_set_window_title(display, "Radio Station");
}

void StateControl::LoadFonts()
{
	forms_font = al_load_font(ConsolaTTF, 36, ALLEGRO_ALIGN_CENTER);
	small_forms_font = al_load_font(ConsolaTTF, 20, ALLEGRO_ALIGN_CENTER);
	musics_font = al_load_font(ConsolaTTF, 14, ALLEGRO_ALIGN_CENTER);
	tiny_font = al_load_font(ConsolaTTF, 10, ALLEGRO_ALIGN_CENTER);
	if (!forms_font || !small_forms_font || !musics_font)
	{
		al_show_native_message_box(display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

void StateControl::start_radio ()
{
	Initialize();

	states.push_back(new LoginState());
	states.push_back(new SignUpState());
	states.push_back(new AdminAccState());
	states.push_back(new RegularAccState());
	states.push_back(new ManageMusicsState());
	states.push_back(new AddMusicState());
	states.push_back(new EditMusicState());
	states.push_back(new TopTenState());
	states.push_back(new MyPlaylistState());
	states.push_back(new SearchState());
	states.push_back(new CompetitionState());
	state = -1;
	ChangeState(Login);

	cout << "Starting control cycle..." << endl;
	done = false;
	draw = true;
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, & ev);

		/* --- controlling left mouse button double press --- */
		if (possible_double_press && double_press_counter < 15)
		{ double_press_counter++; }
		else if (possible_double_press)
		{ possible_double_press = false; double_press_counter = 0; }
		
		/* --- advancing through music --- */
		if (ev.timer.source == timer && playing_music && music_time_counter < 130)
		{ music_time_counter++; }
		else if (ev.timer.source == timer && playing_music)
		{ playing_music = false; music_time_counter = 0; }
		
		/* --- tracking mouse --- */
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;

			draw = true;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				left_mouse_button_pressed = true;
				left_mouse_button_released = false;
				draw = true;
			}
			if (ev.mouse.button & 2)
			{
				right_mouse_button_pressed = true;
				right_mouse_button_released = false;
				draw = true;
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.button & 1)
			{
				if (possible_double_press)
				{ cout << "* Left mouse button pressed twice *" << endl; left_mouse_button_pressed_twice = true; }
				else { cout << "* Left mouse button pressed *" << endl; }

				possible_double_press = true;
				left_mouse_button_pressed = false;
				left_mouse_button_released = true;
				draw = true;
			}
			if (ev.mouse.button & 2)
			{
				cout << "* Right mouse button pressed *" << endl;
				right_mouse_button_pressed = false;
				right_mouse_button_released = true;
				draw = true;
			}
		}

		/* --- UPDATING --- */
		if (states[state]->Update(& ev) || ev.type == ALLEGRO_EVENT_TIMER || draw)
		{
			StateControl::GetInstance()->left_mouse_button_released = false;
			StateControl::GetInstance()->left_mouse_button_pressed_twice = false;
			StateControl::GetInstance()->right_mouse_button_released = false;
			draw = true;
		}

		/* --- now drawing --- */
		if (draw && al_event_queue_is_empty(event_queue))
		{
			states[state]->Draw();

			/* player active UI */
			if (state != Login && state != SignUp && state != AddMusic &&
				state != EditMusic && state != ManageMusics && state != Competition)
			{
				al_draw_text(musics_font, DarkGray, 10, player_interface_y_coord, NULL, "Playing:");
				al_draw_line(10, 420, 140, 420, DarkGray, 2.0);
				switch (playing_music)
				{
				case 0:
					{
						al_draw_text(tiny_font, DarkGray, 10, player_interface_y_coord + 20, NULL, "<Double-click a music>");
						al_draw_circle(10, player_interface_y_coord + 40, 5, LightGray, 1.0);
						al_draw_filled_circle(10, player_interface_y_coord + 40, 4, White);
						break;
					}
				case 1: 
					{
						al_draw_text(tiny_font, DarkGray, 10, player_interface_y_coord + 20, NULL, music_playing_title.c_str());
						al_draw_circle(10 + music_time_counter, player_interface_y_coord + 40, 5, LightGray, 1.0);
						al_draw_filled_circle(10 + music_time_counter, player_interface_y_coord + 40, 4, White);
						break;
					}
				}
			}
			
			/*
			// mouse temp coords
			stringstream ss;
			ss << mouse_x << " " << mouse_y;
			al_draw_text(forms_font, Yellow, 0, 0, NULL, ss.str().c_str());
			// -----------------
			*/

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			draw = false;
		}

		/* if window is closed */
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			cout << "Close button pressed..." << endl;
			done = true;
		}
	}

	Terminate();
}

void StateControl::Terminate()
{
	cout << "Dealocating memory and quitting..." << endl;
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(forms_font);
	al_destroy_font(small_forms_font);
	al_destroy_font(musics_font);
}

StateControl * StateControl::GetInstance()
{
	if (!instance)
	{
		instance = new StateControl();
	}

	return instance;
}

void StateControl::ChangeState (int newState)
{
	if (state != -1)
	{
		states[state]->Terminate();
	}

	state = newState;

	states[state]->Initialize();
}