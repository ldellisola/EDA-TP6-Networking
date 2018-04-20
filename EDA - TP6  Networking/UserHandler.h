#pragma once
#include <allegro5\allegro.h>
#include <fstream>
#include <vector>
#include "curses.h"
#include <string>

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


// Esta clase es la encargada de allegro y toda la interaccion con el usuario con pd curses
class UserHandler
{
public:
	UserHandler();
	~UserHandler();
	const char * getNextIP(int pos, const char * file);

	// PDCurses functions that return information from the user
	void initGetter();
	void killGetter();
	vector<int> getSequence(int sequenceLenght);
	char getAnimation();

	// Allegro Function that draws the animation
	void draw();
private:
	WINDOW * display;
	bool  nodelaySet;
	int getNumberString(int posY, int posX, const char * errorMessage);
	char getSingleLoweredCharInRange(char min, char max, int posY, int posX, const char * errorMessage);
};

