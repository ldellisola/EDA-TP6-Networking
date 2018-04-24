#pragma once
#include <allegro5\allegro.h>
#include <fstream>
#include <vector>
#include "curses.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_color.h"
#include <string>
#include "AllegroClass.h"

using namespace std;
// Messages for user input
#define ANIMATION_ASK "Hello, please select the animation you want to play. Values range from A to F included (lower and upper case allowed)\n"
#define SELECTED_ANIMATION "You have selected Animation '%c'"
#define CONFIRM_ANIMATION  "Press 'enter' to confirm or esc to select a new animation"
#define ERROR_ANIMATION "Error: incorrect input. Try Again"

#define SEQUENCE_ASK "Hello, please select the order in which the animation will be played"
#define SELECTED_SEQUENCE "The current selected sequence is :"
#define CONFIRM_SEQUENCE "Press 'enter' to confirm, or esc to select a new sequence"
#define ERROR_SEQUENCE "Error: incorrect Input. Try agin"

//Tokens
#define CAT_AN "Cat/Cat Running-F"
#define EXP1_AN "Explosion 1/Explosion 1-F"
#define EXP2_AN "Explosion 2/Explosion 2-F"
#define HOMER_AN "Homer/homerdance-F"
#define MARIO_AN "Mario/Super Mario Running-F"
#define SONIC_AN "Sonic/Sonic Running-F"
//Extensions
#define EXT ".png"
#define EXT2 ".jpg"
#define EXT3 ".wav"

//Backgrounds
#define CAT_BG "Backgrounds/CatBackground.jpg"
#define HOMER_BG "Backgrounds/LosSimpsonsBackground.jpg"
#define MARIO_BG "Backgrounds/MarioBackground.png"
#define SONIC_BG "Backgrounds/SonicBackground.jpg"
//Soundtracks
#define CAT_SD "Cat/Otrogato.wav"
#define EXP1_SD "Soundtracks/Explosion1.wav"
#define EXP2_SD "Soundtracks/Explosion1.wav"
#define HOMER_SD "Soundtracks/Haveyouever.wav"
#define MARIO_SD "Soundtracks/SuperMario.wav"
#define SONIC_SD "Soundtracks/Sonic.wav"

typedef struct Animation
{
	vector<ALLEGRO_BITMAP *> frames;
	char ID;
	float time = -1;					// Tiempo que tarda la animacion en ms
	float speed = -1;					// Velocidad de la animacion (px/frame)
	float x = -1;
	float y = -1;
	float width;
	float height;
	ALLEGRO_SAMPLE * background_music = NULL;
	ALLEGRO_BITMAP *display_background = NULL;

	Animation(char an) {

		string path;
		int ammount;


		ID = toupper(an);

		switch (an) {
		case 'A':
			path = CAT_AN;
			display_background = al_load_bitmap(CAT_BG);
			background_music = AllegroClass::loadSong(CAT_SD);
			ammount = 12;
			speed = 2;
			time = 100;
			x = 0;
			break;
		case 'B':
			path = EXP1_AN;			
			background_music = AllegroClass::loadSong(EXP2_SD);
			ammount = 8;
			speed = 0;
			time = 120;
			break;
		case 'C':
			path = EXP2_AN;
			background_music = AllegroClass::loadSong(CAT_SD);
			ammount = 48;
			speed = 0;
			time = 100;
			break;
		case 'D':
			x = 0;
			path = HOMER_AN;
			display_background = al_load_bitmap(HOMER_BG);
			background_music = AllegroClass::loadSong(HOMER_SD);
			ammount = 10;
			speed = 100;
			time = 100;
			break;
		case 'E':
			x = 0;
			path = MARIO_AN;
			display_background = al_load_bitmap(MARIO_BG);
			background_music = AllegroClass::loadSong(MARIO_SD);
			ammount = 12;
			speed = 2;
			time = 40;
			break;
		case 'F':
			x = 0;
			path = SONIC_AN;
			display_background = al_load_bitmap(SONIC_BG);
			background_music = AllegroClass::loadSong(SONIC_SD);
			ammount = 10;
			speed = 70;
			time = 60;
			break;

		}

		loadAnimation(fillAnimation(path, EXT, ammount));

		height = al_get_bitmap_height(frames[1]);
		width = al_get_bitmap_height(frames[1]);
	}

	vector<string> fillAnimation(string path, string ext, int ammount)
	{
		vector<string> retValue;

		for (int i = 0; i < ammount; i++) {
			string a = (path + to_string(i + 1) + ext);
			retValue.push_back(a);
		}



		return retValue;
	}

	void loadAnimation(vector<string> a) {

		for (int i = 0; i < a.size(); i++)
			frames.push_back(al_load_bitmap(a[i].c_str()));
	}

	~Animation() {
		for (int i = 0; i < frames.size(); i++)
			al_destroy_bitmap(frames[i]);
		al_destroy_bitmap(this->display_background);
	}
};


// Esta clase es la encargada de allegro y toda la interaccion con el usuario con pd curses
class UserHandler
{
public:
	UserHandler();
	~UserHandler();
	const char * getNextIP(int pos, vector<string>& ips);

	// PDCurses functions that return information from the user
	void initGetter();
	void killGetter();
	vector<int> getSequence(int sequenceLenght);
	char getAnimation();
	bool askToStart();

	// Allegro Function that draws the animation
	void draw(Animation * an, ALLEGRO_BITMAP * background);
private:
	WINDOW * display;
	bool  nodelaySet;
	int getNumberString(int posY, int posX, const char * errorMessage);
	char getSingleLoweredCharInRange(char min, char max, int posY, int posX, const char * errorMessage);
};

