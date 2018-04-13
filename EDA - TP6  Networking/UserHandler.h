#pragma once
#include <allegro5\allegro.h>
#include <fstream>

using namespace std;
// Esta clase es la encargada de allegro y toda la interaccion con el usuario con pd curses
class UserHandler
{
public:
	UserHandler();
	~UserHandler();
	const char * getNextIP(int pos, const char * file);
	int * getSequence();
	char getAnimation();
	void draw();
private:

};

