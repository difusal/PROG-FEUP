#include "stdIncludes.h"
#include "StateControl.h"
#include "FileManager.h"

int main ()
{
	/* checking if program is running for the first time */
	if (!file_exists(UsersCsv) || !file_exists(RadioStationMusicsCsv) || !file_exists(TopTenCsv))
	{
		cout << " ----------------------------------------" << endl;
		cout << "| First time opening the program, right? |" << endl;
		cout << "| Let me create some necessary files...  |" << endl;

		/* making folder */
		int err = _mkdir("radio_data");
		if (err != 0)
		{
			al_show_native_message_box(NULL, "Critical Error", "Ups! What have you done?", "Could not find necessary data files.\nPlease delete \"radio_data\" folder completely and restart the program.", NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << endl << endl;
			cout << "..:: An error has occured, please delete radio_data folder ::.." << endl;
			cout << "Press enter to quit ";
			cin.get();
			exit(-1);
		}

		/* creating standard users.csv */
		/* opening stream */
		ofstream users_csv (UsersCsv);
		users_csv << "id,username,password,age,gender" << endl;
		stringstream ss;
		ss << "0," << AdminUsername << ",1234,0,0";
		users_csv << ss.str();
		ss.str(string());
		/* closing stream */
		users_csv.close();

		/* creating standard radioStationMusics.csv */
		/* opening stream */
		ofstream radioStationMusics_csv (RadioStationMusicsCsv);
		radioStationMusics_csv << "id,title,artist,author,album,music genre,year,likes,dislikes,plays,availability" << endl;
		radioStationMusics_csv << "0,A Certain Romance,Arctic Monkeys,Arctic Monkeys,Whatever People Say I Am That's What I'm Not,Indie,2006,0,0,0,1" << endl;
		radioStationMusics_csv << "1,When The Sun Goes Down,Arctic Monkeys,Arctic Monkeys,Whatever People Say I Am That's What I'm Not,Indie,2006,0,0,0,1" << endl;
		radioStationMusics_csv << "2,Teddy Picker,Arctic Monkeys,Arctic Monkeys,Favourite Worst Nightmare,Indie,2007,0,0,0,1" << endl;
		radioStationMusics_csv << "3,Cornerstone,Arctic Monkeys,Arctic Monkeys,Humbug,Indie,2009,0,0,0,1" << endl;
		radioStationMusics_csv << "4,Brianstorm,Arctic Monkeys,Arctic Monkeys,Favourite Worst Nightmare,Indie,2007,0,0,0,1" << endl;
		radioStationMusics_csv << "5,Mardy Bum,Arctic Monkeys,Arctic Monkeys,Whatever People Say I Am That's What I'm Not,Indie,2006,0,0,0,1";
		/* closing stream */
		radioStationMusics_csv.close();

		/* creating standard topTen.csv */
		/* opening stream */
		ofstream topTen (TopTenCsv);
		/* closing stream */
		topTen.close();

		cout << "| Done!                                  |" << endl;
		cout << " ----------------------------------------" << endl << endl;
	}

	StateControl::GetInstance()->start_radio();

	return 0;
}