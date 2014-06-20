#pragma once

#include "stdIncludes.h"
#include "Music.h"
#include "User.h"

class RadioStation
{
public:
	RadioStation();
	RadioStation(string RadioName);
	~RadioStation(void);

	// --- MUSICS LIST METHODS --- //
	const vector<Music> & GetMusicsList() { return musics; }
	void UpdateMusicsList();

	const vector<Music> & GetAvailableMusicsList() { return available_musics; }
	void RefreshAvailableMusicsList();

	const vector<Music> & GetTopTenList() { return top_ten; }
	void UpdateTopTenList();
	bool MusicAlreadyInTopTen(_IDNum ID);

	const vector<_IDNum> & GetMyPlayList() { return my_playlist; }
	void UpdateMyPlayList();
	void AddMusicToPlayList(_IDNum MusicID);
	void RemoveMusicFromPlayList(_IDNum MusicID);

	const vector<Music> & GetSearchResultsList() { return search_results; }
	void UpdateSearchResults(const vector<Music> & vec);
	void AddIDToSearchResults(_IDNum ID);
	void ClearSearchResults() { search_results.clear(); }

	void AddMusic(string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, bool Availability);
	void EditMusic(_IDNum ID, string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, int Likes, int Dislikes, int Plays, bool Availability);

	void AddPlayToMusic(_IDNum ID);
	void SwitchMusicAvailability(_IDNum ID);

	// --- USERS LIST METHODS --- //
	const vector<User> & GetUsersList() { return users; }
	void AddUser(string & Username, string & Password, int Age, string & Gender);
	bool UsernameExists (string & Username);
	bool CorrectPassword (string & Username, string & Password);
	_IDNum GetUserID(string & Username) const;
	bool UserAlreadyLiked(_IDNum ID);
	bool UserAlreadyDisliked(_IDNum ID);
	void AddPlayToUserAndMusic(_IDNum ID);
	void AddUserLike(_IDNum ID);
	void AddUserDislike(_IDNum ID);
	void AddAdminLike(_IDNum ID);
	void AddAdminDislike(_IDNum ID);

private:
	string name;	// radio name

	vector<Music> musics;
	vector<Music> available_musics;

	vector<Music> top_ten;
	vector<Music> search_results;

	vector<User> users;
	vector<_IDNum> my_playlist;
	vector<vector<unsigned int> > userDetails;
};