#pragma once

/* allegro includes */
#include "allegro5\allegro.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

/* necessary includes */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <direct.h>

using namespace std;

/* global variables */
#define ScreenWidth 800
#define ScreenHeight 600
#define AdminUsername "Admin"
const float FPS = 60.0;

/* defining user-friendly color names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(70, 70, 70)
#define LightGray al_map_rgb(110, 110, 110)
#define DarkBlue al_map_rgb(0, 0, 150)
#define Blue al_map_rgb(0, 0, 255)
#define DarkGreen al_map_rgb(0, 200, 0)
#define Green al_map_rgb(0, 255, 0)
#define LightBlue al_map_rgb(14, 108, 150)
#define DarkRed al_map_rgb(200, 0, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

/* file paths */
#define UsersCsv "radio_data//users.csv"
#define RadioStationMusicsCsv "radio_data//radioStationMusics.csv"
#define TopTenCsv "radio_data//topTen.csv"

/* images */
#define LikeDislikeMenu "res//images//like_dislike_menu.png"
#define LikeDislikeAddMenu "res//images//like_dislike_add_menu.png"
#define EditRemoveMenu "res//images//edit_remove_menu.png"
#define EditAddMenu "res//images//edit_add_menu.png"
#define RemoveMenu "res//images//remove_menu.png"

#define LoginScreen "res//images//login.png"
#define SignUpScreen "res//images//sign_up.png"
#define AdminAccScreen "res//images//admin_acc.png"
#define RegularAccScreen "res//images//regular_acc.png"
#define ManageMusicsScreen "res//images//manage_musics.png"
#define TopTenScreen "res//images//top_ten.png"
#define MyPlaylistScreen "res//images//my_playlist.png"
#define AddMusicScreen "res//images//add_music.png"
#define SearchScreen "res//images//search.png"
#define CompetitionScreen "res//images//competition.png"

#define AccScreen1 "res//images//acc1.png"
#define AccScreen2 "res//images//acc2.png"
#define AccScreen3 "res//images//acc3.png"
#define AccScreen4 "res//images//acc4.png"

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"

typedef unsigned int _IDNum;
typedef vector<_IDNum> _List;
typedef vector<vector<_IDNum> > _UserPlaylist;