#include "RadioStation.h"
#include "FileManager.h"
#include "StateControl.h"

RadioStation::RadioStation()
{
	name = "MIEIC";
	users = ReadUsersFromCsvToVec();
	musics = ReadMusicsFromCsvToVec();
	RefreshAvailableMusicsList();
}

RadioStation::RadioStation(string RadioName)
{
	name = RadioName;
	users = ReadUsersFromCsvToVec();
	musics = ReadMusicsFromCsvToVec();
	RefreshAvailableMusicsList();
}

RadioStation::~RadioStation(void)
{
}


// --- MUSICS LIST METHODS --- //
void RadioStation::UpdateMusicsList()
{
	cout << "Updating Music List with data from Available Musics List..." << endl;
	for (unsigned int i = 0, j = 0; i < musics.size() && j < available_musics.size(); i++)
	{
		if (musics[i].GetID() == available_musics[j].GetID())
		{
			musics[i] = available_musics[j];
			j++;
		}
	}
}

void RadioStation::RefreshAvailableMusicsList()
{
	cout << "-------------------------------------------------------" << endl;
	cout << "Refreshing list of available musics..." << endl;
	available_musics.clear();
	for (unsigned int i = 0; i < musics.size(); i++)
	{
		if (musics[i].GetAvailability() == 1)
		{
			available_musics.push_back(musics[i]);
		}
	}
}

bool RadioStation::MusicAlreadyInTopTen(_IDNum ID)
{
	for (unsigned int i = 0; i < top_ten.size(); i++)
	{
		if (top_ten[i].GetID() == ID)
		{ return true; }
	}

	return false;
}

void RadioStation::UpdateTopTenList()
{
	SaveMusicsFromVecToCsv(musics);
	RefreshAvailableMusicsList();

	cout << "Updating Top Ten List..." << endl;

	// clear top ten
	top_ten.clear();

	// update content
	if (available_musics.size() != 0)
	{
		top_ten.push_back(available_musics[0]);

		for (unsigned int i = 1; i < available_musics.size(); i++)
		{
			for (unsigned int j = 0; j < top_ten.size(); j++)
			{
				if (available_musics[i].GetRanking() > top_ten[j].GetRanking())
				{
					top_ten.insert(top_ten.begin() + j, available_musics[i]);
					break;
				}
				else if (j == top_ten.size() - 1)
				{
					top_ten.push_back(available_musics[i]);
					break;
				}
			}

			// cutting off lose ends
			if (top_ten.size() > 10)
			{
				top_ten.resize(10);
			}
		}
	}

	// saving to .csv
	SaveTopTenFromVecToCsv(top_ten);
}

void RadioStation::UpdateMyPlayList()
{
	cout << "Updating My PlayList..." << endl;
	my_playlist = ReadUserPlaylistFromCsvToVec();
}

void RadioStation::AddMusicToPlayList(_IDNum MusicID)
{
	bool MusicAlreadyOnPlaylist = false;

	for (unsigned int i = 0; i < my_playlist.size(); i++)
	{
		if (MusicID == my_playlist[i])
		{
			cout << "That music is already on your playlist." << endl;
			MusicAlreadyOnPlaylist = true;
		}
	}

	bool playlist_full = false;
	if (my_playlist.size() >= 28) { al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Playlist is full.", "You can not add more musics to your playlist.\nPlease remove a music before you add another.", NULL, ALLEGRO_MESSAGEBOX_ERROR); playlist_full = true; }

	if (!MusicAlreadyOnPlaylist && !playlist_full)
	{
		cout << "Successfully added music to your playlist." << endl;
		my_playlist.push_back(MusicID);
		SaveUserPlaylistFromVecToCsv(my_playlist);
	}
}

void RadioStation::RemoveMusicFromPlayList(_IDNum MusicID)
{
	for (unsigned int i = 0; i < my_playlist.size(); i++)
	{
		if (MusicID == my_playlist[i])
		{
			my_playlist.erase(my_playlist.begin() + i);
			SaveUserPlaylistFromVecToCsv(my_playlist);
			break;
		}
	}
	cout << "Done!" << endl;
}


void RadioStation::UpdateSearchResults(const vector<Music> & vec)
{
	cout << "Updating search results..." << endl;
	search_results = vec;
}

void RadioStation::AddIDToSearchResults(_IDNum ID)
{
	search_results.push_back(StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID]);
}


void RadioStation::AddMusic(string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, bool Availability)
{
	_IDNum id = musics.size();
	Music new_music (id, Title, Artist, Author, Album, Genre, Year, 0, 0, 0, Availability);
	musics.push_back(new_music);

	stringstream ss;
	cout << "Updating each userDetails.csv..." << endl;
	for (unsigned int id = 1; id < users.size(); id++)
	{
		// assigning correct name
		ss.str(string());
		if (id < 10) { ss << "radio_data//userDetails" << "00" << id << ".csv"; }
		else if (id < 100) { ss << "radio_data//userDetails" << "0" << id << ".csv"; }
		else { ss << "radio_data//userDetails" << id << ".csv"; }

		// opening stream
		cout << "opening stream";
		ofstream userDetails_csv (ss.str(), ios::app);
		userDetails_csv << endl << musics.size()-1 << ",0,0,0";
		userDetails_csv.close();
	}

	SaveMusicsFromVecToCsv(musics);
	UpdateMusicsList();
}

void RadioStation::EditMusic(_IDNum ID, string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, int Likes, int Dislikes, int Plays, bool Availability)
{
	Music edited_music (ID, Title, Artist, Author, Album, Genre, Year, Likes, Dislikes, Plays, Availability);

	musics[ID] = edited_music;

	SaveMusicsFromVecToCsv(musics);
}


void RadioStation::AddPlayToMusic(_IDNum ID)
{
	musics[ID].AddPlay();
}

void RadioStation::SwitchMusicAvailability(_IDNum ID)
{
	switch (musics[ID].GetAvailability())
	{
	case 0:
		{
			cout << "Marking as available" << endl;
			musics[ID].SetAvailability(1);
			break;
		}
	case 1:
		{
			cout << "Marking as unavailable" << endl;
			musics[ID].SetAvailability(0);
			break;
		}
	}
}


// --- USERS LIST METHODS --- //
void RadioStation::AddUser(string & Username, string & Password, int Age, string & Gender)
{
	_IDNum ID = users.size();
	User new_user (ID, Username, Password, Age, Gender);
	users.push_back(new_user);

	SaveUsersFromVecToCsv(users);

	cout << "Creating user playlist .csv..." << endl;
	stringstream ss;
	ss.str(string());
	if (ID < 10) { ss << "radio_data//playListUser" << "00" << ID << ".csv"; }
	else if (ID < 100) { ss << "radio_data//playListUser" << "0" << ID << ".csv"; }
	else { ss << "radio_data//playListUser" << ID << ".csv"; }
	// opening stream
	ofstream user_csv (ss.str());
	user_csv.close();

	cout << "Creating user details .csv..." << endl;
	ss.str(string());
	if (ID < 10) { ss << "radio_data//userDetails" << "00" << ID << ".csv"; }
	else if (ID < 100) { ss << "radio_data//userDetails" << "0" << ID << ".csv"; }
	else { ss << "radio_data//userDetails" << ID << ".csv"; }
	// opening stream
	ofstream userDetails_csv (ss.str());
	userDetails_csv << "musicID,likes,dislikes,plays";
	for (unsigned int i = 0; i < musics.size(); i++)
	{
		userDetails_csv << endl;
		// id
		userDetails_csv << musics[i].GetID() << ",";
		// likes, dislikes, plays
		userDetails_csv << "0,0,0";
	}
	userDetails_csv.close();
}

bool RadioStation::UsernameExists (string & Username)
{
	// scanning for a match
	for (unsigned int i = 0; i < users.size(); i++)
	{
		if (Username == users[i].GetUsername())
		{ return true; }
	}

	return false;
}

bool RadioStation::CorrectPassword (string & Username, string & Password)
{
	// scanning for a match
	for (unsigned int i = 0; i < users.size(); i++)
	{
		if (Username == users[i].GetUsername() && Password == users[i].GetPassword())
		{ return true; }
	}

	return false;
}

_IDNum RadioStation::GetUserID(string & Username) const
{
	// scanning for a match
	for (unsigned int i = 0; i < users.size(); i++)
	{
		if (Username == users[i].GetUsername())
		{ return i; }
	}

	return 0;
}

bool RadioStation::UserAlreadyLiked(_IDNum ID)
{
	userDetails = ReadUserDetailsFromCsvToVec();

	if (userDetails[ID][1] >= 1)
	{ return true; }

	return false;
}

bool RadioStation::UserAlreadyDisliked(_IDNum ID)
{
	userDetails = ReadUserDetailsFromCsvToVec();

	if (userDetails[ID][2] >= 1)
	{ return true; }

	return false;
}

void RadioStation::AddPlayToUserAndMusic(_IDNum ID)
{
	userDetails = ReadUserDetailsFromCsvToVec();

	userDetails[ID][3]++;
	SaveUserDetailsFromVecToCsv(userDetails);

	musics[ID].AddPlay();
}

void RadioStation::AddUserLike(_IDNum ID)
{
	StateControl::GetInstance()->radio.RefreshAvailableMusicsList();
	userDetails = ReadUserDetailsFromCsvToVec();

	// if user already liked that music
	if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] >= 1)
	{ cout << "* Already liked that music *" << endl; }
	// adding first like to music
	else if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] == 0 &&
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] == 0)
	{
		cout << "Adding Like..." << endl;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] = 1;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] = 0;
		available_musics[ID].AddLike();
		UpdateMusicsList();
		SaveMusicsFromVecToCsv(musics);
	}
	// if user is adding like and had already disliked the music
	else if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] == 0 &&
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] == 1)
	{
		cout << "Adding Like..." << endl;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] = 1;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] = 0;
		available_musics[ID].RemoveDislike();
		available_musics[ID].AddLike();
		UpdateMusicsList();
		SaveMusicsFromVecToCsv(musics);
	}

	SaveUserDetailsFromVecToCsv(userDetails);
}

void RadioStation::AddUserDislike(_IDNum ID)
{
	StateControl::GetInstance()->radio.RefreshAvailableMusicsList();
	userDetails = ReadUserDetailsFromCsvToVec();

	// if user already disliked that music
	if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] >= 1)
	{ cout << "* Already disliked that music *" << endl; }
	// adding first dislike to music
	else if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] == 0 &&
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] == 0)
	{
		cout << "Adding Dislike..." << endl;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] = 0;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] = 1;
		available_musics[ID].AddDislike();
		UpdateMusicsList();
		SaveMusicsFromVecToCsv(musics);
	}
	// if user is adding dislike and had already liked the music
	else if (userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] == 1 &&
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] == 0)
	{
		cout << "Adding Dislike..." << endl;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][1] = 0;
		userDetails[StateControl::GetInstance()->radio.GetAvailableMusicsList()[ID].GetID()][2] = 1;
		available_musics[ID].RemoveLike();
		available_musics[ID].AddDislike();
		UpdateMusicsList();
		SaveMusicsFromVecToCsv(musics);
	}

	SaveUserDetailsFromVecToCsv(userDetails);
}

void RadioStation::AddAdminLike(_IDNum ID)
{
	musics[ID].AddLike();
}

void RadioStation::AddAdminDislike(_IDNum ID)
{
	musics[ID].AddDislike();
}