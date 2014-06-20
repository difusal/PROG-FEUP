#include "Music.h"
#include "StateControl.h"
#include "SearchState.h"
#include "FileManager.h"

Music::Music()
{
	id = -1;
	title = "Unknown";
	artist = "Unknown";
	author = "Unknown";
	album = "Unknown";
	genre = "Unknown";
	year = "Unknown";
	likes = 0;
	dislikes = 0;
	plays = 0;
	availability = 1;
}

Music::Music(_IDNum ID, string & Title, string & Artist, string & Author, string & Album, string & Genre, string & Year, int Likes, int Dislikes, int Plays, bool Availability)
{
	id = ID;
	title = Title;
	artist = Artist;
	author = Author;
	album = Album;
	genre = Genre;
	year = Year;
	likes = Likes;
	dislikes = Dislikes;
	plays = Plays;
	availability = Availability;
}

void Music::SetTitle(string & Title)
{
	title = Title;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetArtist(string & Artist)
{
	artist = Artist;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetAuthor(string & Author)
{
	author = Author;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetAlbum(string & Album)
{
	album = Album;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetGenre(string & Genre)
{
	genre = Genre;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetYear(string & Year)
{
	year = Year;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::AddLike()
{
	likes++;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::AddDislike()
{
	dislikes++;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::RemoveLike()
{
	likes--;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::RemoveDislike()
{
	dislikes--;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::AddPlay()
{
	plays++;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}

void Music::SetAvailability(bool Availability)
{
	availability = Availability;
	SaveMusicsFromVecToCsv(StateControl::GetInstance()->radio.GetMusicsList());
}