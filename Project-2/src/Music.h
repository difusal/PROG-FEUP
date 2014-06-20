#pragma once

#include "stdIncludes.h"

class Music
{
public:
	Music();
	Music(_IDNum ID, string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, int Likes, int Dislikes, int Plays, bool Availability);

	_IDNum GetID() const { return id; }
	string GetTitle() const { return title; }
	string GetArtist() const { return artist; }
	string GetAuthor() const { return author; }
	string GetAlbum() const { return album; }
	string GetGenre() const { return genre; }
	string GetYear() const { return year; }
	int GetLikes() const { return likes; }
	int GetDislikes() const { return dislikes; }
	int GetRanking() const { return likes - dislikes; }
	int GetPlays() const { return plays; }
	int GetAvailability() const { return availability; }

	void SetTitle(string & Title);
	void SetArtist(string & Artist);
	void SetAuthor(string & Author);
	void SetAlbum(string & Album);
	void SetGenre(string & Genre);
	void SetYear(string & Year);
	void AddLike();
	void AddDislike();
	void RemoveLike();
	void RemoveDislike();
	void AddPlay();
	void SetAvailability(bool Availability);

private:
	_IDNum id;
	string title, artist, author, album, genre, year;
	int likes, dislikes, plays;
	bool availability;
};