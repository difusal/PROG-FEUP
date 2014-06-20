#include "FileManager.h"
#include "StateControl.h"

bool file_exists (const string & filename)
{
	/* trying to open input file stream */
	ifstream infile (filename);

	return infile.good();
}


vector<User> ReadUsersFromCsvToVec()
{
	string data;
	_IDNum id; string username, password; int age; string gender;
	vector<User> vec;

	/* opening stream */
	ifstream users (UsersCsv);

	/* discarding first line */
	getline(users, data);

	/* reading data */
	cout << "Reading user data from users.csv..." << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Content of users.csv:" << endl;
	while (!users.eof())
	{
		/* id */
		if (getline(users, data, ',') == "\n")
		{ break; }
		else
		{
			id = atoi(data.c_str());
			cout << "ID: " << id << "\t";
		}
		/* username */
		getline(users, username, ',');
		cout << "Username: " << username << "\t";
		/* password */
		getline(users, password, ',');
		cout << "Password: " << password << "\t";
		/* age */
		getline(users, data, ',');
		age = atoi(data.c_str());
		cout << "Age: " << age << "\t";
		/* gender */
		getline(users, gender);
		cout << "Gender: " << gender << endl;

		User temp_user (id, username, password, age, gender);

		/* pushing back temp vec */
		vec.push_back(temp_user);
	}

	cout << "-----------------------------------------------------------------" << endl;
	cout << "Number of users based on users.csv file: " << vec.size() << endl;

	return vec;
}

void SaveUsersFromVecToCsv(const vector<User> & vec)
{
	cout << "Saving user data to users.csv..." << endl;

	/* opening stream */
	ofstream musics_csv (UsersCsv);

	musics_csv << "id,username,password,age,gender" << endl;

	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (i == vec.size() - 1)
		{
			musics_csv << vec[i].GetID() << ",";
			musics_csv << vec[i].GetUsername() << ",";
			musics_csv << vec[i].GetPassword() << ",";
			musics_csv << vec[i].GetAge() << ",";
			musics_csv << vec[i].GetGender();
		}
		else
		{
			musics_csv << vec[i].GetID() << ",";
			musics_csv << vec[i].GetUsername() << ",";
			musics_csv << vec[i].GetPassword() << ",";
			musics_csv << vec[i].GetAge() << ",";
			musics_csv << vec[i].GetGender() << "\n";
		}
	}
}


int GetMusicPlaysFromUserDetails(_IDNum UserID, _IDNum MusicID)
{
	stringstream ss;
	string data;
	vector<unsigned int> temp;
	vector<vector<unsigned int> > vec;

	// assigning correct filename
	if (UserID < 10) { ss << "radio_data//userDetails" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//userDetails" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//userDetails" << UserID << ".csv"; }

	/* opening stream */
	ifstream csv (ss.str());

	/* discarding first line */
	getline(csv, data);

	/* reading data */
	while (!csv.eof())
	{
		/* musicID */
		if (getline(csv, data, ',') == "\n") { break; }
		else { temp.push_back(atoi(data.c_str())); }

		/* likes */
		getline(csv, data, ',');
		temp.push_back(atoi(data.c_str()));

		/* dislikes */
		getline(csv, data, ',');
		temp.push_back(atoi(data.c_str()));

		/* plays */
		getline(csv, data);
		temp.push_back(atoi(data.c_str()));


		/* pushing back temp vec */
		vec.push_back(temp);

		temp.clear();
	}

	return vec[MusicID][3];
}

const vector<vector<unsigned int> > ReadUserDetailsFromCsvToVec()
{
	_IDNum UserID = StateControl::GetInstance()->ActiveUserID;
	stringstream ss;

	string data;
	string line;
	vector<unsigned int> temp;
	vector<vector<unsigned int> > vec;

	/* assigning correct filename */
	if (UserID < 10) { ss << "radio_data//userDetails" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//userDetails" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//userDetails" << UserID << ".csv"; }

	/* opening stream */
	ifstream csv (ss.str());

	/* discarding first line */
	getline(csv, line);

	/* reading data */
	cout << "Reading userDetails.csv... ";
	while (!csv.eof())
	{
		/* musicID */
		if (getline(csv, data, ',') == "\n") { break; }
		else { temp.push_back(atoi(data.c_str())); }

		/* likes */
		getline(csv, data, ',');
		temp.push_back(atoi(data.c_str()));

		/* dislikes */
		getline(csv, data, ',');
		temp.push_back(atoi(data.c_str()));

		/* plays */
		getline(csv, data);
		temp.push_back(atoi(data.c_str()));


		/* pushing back temp vec */
		vec.push_back(temp);

		temp.clear();
	}
	cout << "Done!" << endl;

	return vec;
}

void SaveUserDetailsFromVecToCsv(const vector<vector<unsigned int> > & vec)
{
	_IDNum UserID = StateControl::GetInstance()->ActiveUserID;
	stringstream ss;

	/* assigning correct filename */
	if (UserID < 10) { ss << "radio_data//userDetails" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//userDetails" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//userDetails" << UserID << ".csv"; }

	cout << "Saving music data to radioStationMusics.csv... ";

	/* opening stream */
	ofstream musics_csv (ss.str());
	musics_csv << "musicID,likes,dislikes,plays" << endl;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		for (unsigned int j = 0; j < vec[0].size(); j++)
		{
			if (j == vec[0].size() - 1 &&
				i == vec.size() - 1)
			{
				musics_csv << vec[i][j];
			}
			else if (j == vec[0].size() - 1)
			{
				musics_csv << vec[i][j] << "\n";
			}
			else
			{
				musics_csv << vec[i][j] << ",";
			}
		}
	}
	cout << "Done!" << endl;
}


const vector<Music> ReadMusicsFromCsvToVec()
{
	string data;
	_IDNum id;
	string title, artist, author, album, genre, year;
	int likes, dislikes, plays;
	bool availability;
	vector<Music> vec;

	/* opening stream */
	ifstream users (RadioStationMusicsCsv);

	/* discarding first line */
	getline(users, data);

	/* reading data */
	cout << "Reading music data from radioStationMusics.csv..." << endl << endl;
	cout << "----------------------------------" << endl;
	cout << "Content of radioStationMusics.csv:" << endl;
	cout << "----------------------------------" << endl;
	while (!users.eof())
	{
		/* id */
		if (getline(users, data, ',') == "\n")
		{ break; }
		else
		{
			id = atoi(data.c_str());
			cout << "ID: " << id << "\t";
		}
		/* title */
		getline(users, title, ',');
		cout << "Title: " << title << "\t";
		/* artist */
		getline(users, artist, ',');
		cout << "Artist: " << artist << "\t";
		/* author */
		getline(users, author, ',');
		cout << "Author: " << author << "\t";
		/* album */
		getline(users, album, ',');
		cout << "Album: " << album << "\t";
		/* genre */
		getline(users, genre, ',');
		cout << "Genre: " << genre << "\t";
		/* year */
		getline(users, year, ',');
		cout << "Year: " << year << "\t";
		/* likes */
		getline(users, data, ',');
		likes = atoi(data.c_str());
		cout << "Likes: " << likes << "\t";
		/* dislikes */
		getline(users, data, ',');
		dislikes = atoi(data.c_str());
		cout << "Dislikes: " << dislikes << "\t";
		/* plays */
		getline(users, data, ',');
		plays = atoi(data.c_str());
		cout << "Plays: " << plays << "\t";
		/* availability */
		getline(users, data);
		availability = atoi(data.c_str());
		cout << "Availability: " << availability << endl;
		
		Music temp_music (id, title, artist, author, album, genre, year, likes, dislikes, plays, availability);

		/* pushing back temp vec */
		vec.push_back(temp_music);
	}

	cout << "-------------------------------------------------------" << endl;
	cout << "Number of musics based on users.csv file: " << vec.size() << endl;

	return vec;
}

void SaveMusicsFromVecToCsv(const vector<Music> & vec)
{
	cout << "Saving music data to radioStationMusics.csv..." << endl;

	/* opening stream */
	ofstream musics_csv (RadioStationMusicsCsv);

	musics_csv << "id,title,artist,author,album,music genre,year,likes,dislikes,plays,availability" << endl;
	
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (i == vec.size() - 1)
		{
			musics_csv << vec[i].GetID() << ",";
			musics_csv << vec[i].GetTitle() << ",";
			musics_csv << vec[i].GetArtist() << ",";
			musics_csv << vec[i].GetAuthor() << ",";
			musics_csv << vec[i].GetAlbum() << ",";
			musics_csv << vec[i].GetGenre() << ",";
			musics_csv << vec[i].GetYear() << ",";
			musics_csv << vec[i].GetLikes() << ",";
			musics_csv << vec[i].GetDislikes() << ",";
			musics_csv << vec[i].GetPlays() << ",";
			musics_csv << vec[i].GetAvailability();
		}
		else
		{
			musics_csv << vec[i].GetID() << ",";
			musics_csv << vec[i].GetTitle() << ",";
			musics_csv << vec[i].GetArtist() << ",";
			musics_csv << vec[i].GetAuthor() << ",";
			musics_csv << vec[i].GetAlbum() << ",";
			musics_csv << vec[i].GetGenre() << ",";
			musics_csv << vec[i].GetYear() << ",";
			musics_csv << vec[i].GetLikes() << ",";
			musics_csv << vec[i].GetDislikes() << ",";
			musics_csv << vec[i].GetPlays() << ",";
			musics_csv << vec[i].GetAvailability() << "\n";
		}
	}
}


void SaveTopTenFromVecToCsv(const vector<Music> & vec)
{
	cout << "Saving Top Ten to topTen.csv..." << endl;

	/* opening stream */
	ofstream top_ten_csv (TopTenCsv);

	top_ten_csv << "id,title,artist,author,album,music genre,year,likes,dislikes,plays,availability" << endl;

	for (unsigned int i = 0; i < vec.size() && i < 10; i++)
	{
		if (i == vec.size() - 1)
		{
			top_ten_csv << vec[i].GetID() << ",";
			top_ten_csv << vec[i].GetTitle() << ",";
			top_ten_csv << vec[i].GetArtist() << ",";
			top_ten_csv << vec[i].GetAuthor() << ",";
			top_ten_csv << vec[i].GetAlbum() << ",";
			top_ten_csv << vec[i].GetGenre() << ",";
			top_ten_csv << vec[i].GetYear() << ",";
			top_ten_csv << vec[i].GetLikes() << ",";
			top_ten_csv << vec[i].GetDislikes() << ",";
			top_ten_csv << vec[i].GetPlays() << ",";
			top_ten_csv << vec[i].GetAvailability();
		}
		else
		{
			top_ten_csv << vec[i].GetID() << ",";
			top_ten_csv << vec[i].GetTitle() << ",";
			top_ten_csv << vec[i].GetArtist() << ",";
			top_ten_csv << vec[i].GetAuthor() << ",";
			top_ten_csv << vec[i].GetAlbum() << ",";
			top_ten_csv << vec[i].GetGenre() << ",";
			top_ten_csv << vec[i].GetYear() << ",";
			top_ten_csv << vec[i].GetLikes() << ",";
			top_ten_csv << vec[i].GetDislikes() << ",";
			top_ten_csv << vec[i].GetPlays() << ",";
			top_ten_csv << vec[i].GetAvailability() << "\n";
		}
	}
}


/* returns vector with the IDs of the musics on user playlist */
const vector<_IDNum> ReadUserPlaylistFromCsvToVec()
{
	_IDNum UserID = StateControl::GetInstance()->ActiveUserID;
	stringstream ss;
	string data;
	vector<_IDNum> vec;

	/* assigning correct filename */
	if (UserID < 10) { ss << "radio_data//playListUser" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//playListUser" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//playListUser" << UserID << ".csv"; }

	/* opening stream */
	ifstream csv (ss.str());

	/* reading data */
	cout << "Reading playlist from playListUserXXX.csv..." << endl << endl;
	cout << "Content:" << endl;
	cout << "----------------------------------";
	while (!csv.eof())
	{
		getline(csv, data, ',');
		if (data == "") { break; }
		cout << endl << "ID: " << data << " Availability: " << StateControl::GetInstance()->radio.GetMusicsList()[atoi(data.c_str())].GetAvailability();
		if (StateControl::GetInstance()->radio.GetMusicsList()[atoi(data.c_str())].GetAvailability())
		{
			vec.push_back(atoi(data.c_str()));
		}
	}

	cout << endl << "----------------------------------" << endl;
	cout << "Number of musics based on .csv file and availability: " << vec.size() << endl;

	return vec;
}

const vector<_IDNum> ReadUserPlaylistFromCsvToVec(_IDNum UserID)
{
	stringstream ss;
	string data;
	vector<_IDNum> vec;

	/* assigning correct filename */
	if (UserID < 10) { ss << "radio_data//playListUser" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//playListUser" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//playListUser" << UserID << ".csv"; }

	/* opening stream */
	ifstream csv (ss.str());

	/* reading data */
	cout << "Reading playlist from playListUserXXX.csv..." << endl << endl;
	cout << "Content:" << endl;
	cout << "----------------------------------";
	while (!csv.eof())
	{
		getline(csv, data, ',');
		if (data == "") { break; }
		cout << endl << "ID: " << data << " Availability: " << StateControl::GetInstance()->radio.GetMusicsList()[atoi(data.c_str())].GetAvailability();
		if (StateControl::GetInstance()->radio.GetMusicsList()[atoi(data.c_str())].GetAvailability())
		{
			vec.push_back(atoi(data.c_str()));
		}
	}

	cout << endl << "----------------------------------" << endl;
	cout << "Number of musics based on .csv file and availability: " << vec.size() << endl;

	return vec;
}

void SaveUserPlaylistFromVecToCsv(const vector<_IDNum> & vec)
{
	_IDNum UserID = StateControl::GetInstance()->ActiveUserID;
	stringstream ss;

	/* assigning correct filename */
	if (UserID < 10) { ss << "radio_data//playListUser" << "00" << UserID << ".csv"; }
	else if (UserID < 100) { ss << "radio_data//playListUser" << "0" << UserID << ".csv"; }
	else { ss << "radio_data//playListUser" << UserID << ".csv"; }
	
	/* opening stream */
	ofstream csv (ss.str());

	cout << "Saving playlist to .csv... ";
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (i == vec.size() - 1)
		{
			csv << vec[i];
		}
		else
		{
			csv << vec[i] << ",";
		}
	}
	cout << "Done!" << endl;
}