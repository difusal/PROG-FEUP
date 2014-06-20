#pragma once

#include "stdIncludes.h"
#include "User.h"
#include "Music.h"

bool file_exists (const string & filename);

vector<User> ReadUsersFromCsvToVec();
void SaveUsersFromVecToCsv(const vector<User> & vec);

int GetMusicPlaysFromUserDetails(_IDNum UserID, _IDNum MusicID);
const vector<vector<unsigned int> > ReadUserDetailsFromCsvToVec();
void SaveUserDetailsFromVecToCsv(const vector<vector<unsigned int> > & vec);

const vector<Music> ReadMusicsFromCsvToVec();
void SaveMusicsFromVecToCsv(const vector<Music> & vec);

void SaveTopTenFromVecToCsv(const vector<Music> & vec);

const vector<_IDNum> ReadUserPlaylistFromCsvToVec();
const vector<_IDNum> ReadUserPlaylistFromCsvToVec(_IDNum UserID);
void SaveUserPlaylistFromVecToCsv(const vector<_IDNum> & vec);