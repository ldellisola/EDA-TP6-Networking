#include "UserHandler.h"



void drawSequenceInterface(vector<int>& sequence);

UserHandler::UserHandler()
{
	display = NULL;
	nodelaySet = true;
}


UserHandler::~UserHandler()
{
}

const char * UserHandler::getNextIP(int pos, vector<string>& ips)
{
	return ips[pos-1].c_str();
}

void UserHandler::initGetter()
{
	display = initscr();
	start_color();

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	color_set(1, NULL);

	nodelay(display, nodelaySet);
	noecho();


}

void UserHandler::killGetter()
{
	endwin();
	display = NULL;
}

char UserHandler::getAnimation()
{
	clear();
	char retValue = ' ';
	char leave = false;

	do {
		mvprintw(0, 0, ANIMATION_ASK);	// Le pido que ingrese un valor
		mvprintw(1, 0, SELECTED_ANIMATION , toupper(retValue));
		retValue = getSingleLoweredCharInRange('a', 'f', 4, 0, ERROR_ANIMATION);
		mvprintw(0, 0, ANIMATION_ASK);	// Le pido que ingrese un valor
		mvprintw(1, 0, SELECTED_ANIMATION, toupper(retValue));
		mvprintw(2, 0, CONFIRM_ANIMATION);
		bool leave_a = false;

		do {							// En este bloque estoy validando si el usuario quiere usar la animacion
			char a = getch();
			if (a != ERR) {
				if (a == '\n')
				{
					leave_a = true;
					leave = true;
				}
				else if (a == 27)		// 27 es el ASCII de esc
				{
					leave_a = true;
					leave = false;
					mvdeleteln(2, 0);
					retValue = ' ';
				}
			}
		} while (!leave_a);



	} while (!leave);

	return retValue;
}

bool UserHandler::askToStart()
{
	color_set(1, NULL);
	mvprintw(0, 0, "Would you like to start the program?");
	mvprintw(1, 0, "Press 'Y' to continue or 'N' to stop");
	int a;
	bool keep = true;
	bool retValue = true;

	do {
		move(3, 0);
		color_set(1, NULL);
		a = getch();
		if (a != ERR) {


			if (a == 'y') {
				keep = false;
				retValue = true;
			}
			else if (a == 'n') {
				keep = false;
				retValue = false;
			}
			else {
				color_set(2, 0);
				mvprintw(2, 0, "ERROR: Pleas try again");
			}
		}

	} while (keep);
	color_set(1, NULL);
	
	return retValue;
}


void UserHandler::draw(Animation * an, ALLEGRO_BITMAP * background)
{

	float xMax = al_get_display_width(al_get_current_display());
	float yMax = al_get_display_height(al_get_current_display());

	if (an->x == -1)
		an->x = xMax / 2 - an->width / 2;
	else
		an->x -= an->width;
	if (an->y == -1)
		an->y = yMax / 2 - an->height / 2;

	AllegroClass::playSong(an->background_music,1.0,1.0, ALLEGRO_PLAYMODE_LOOP);

	if (an->ID == 'C' || an->ID == 'B') {
		for (int i = 0; i < an->frames.size(); i++)
		{
			al_clear_to_color(al_color_name("black")); //al_draw_bitmap(background, 0, 0, 0);
			al_draw_bitmap(an->display_background, 0, 0, 0);
			al_draw_bitmap(an->frames[i], an->x, an->y, 0);
			al_flip_display();
			al_rest(an->time / 1000.0);
		}
	}
	else if (an->ID == 'F') {
		bool keep = true;
		int a = 0;
		while (keep) {
			for (int i = 0; i < an->frames.size() && keep; i++) {
				al_clear_to_color(al_color_name("black")); //al_draw_bitmap(background, 0, 0, 0);
				al_draw_bitmap(an->display_background, 0, 0, 0);
				al_draw_bitmap(an->frames[i], an->x, an->y, ALLEGRO_FLIP_HORIZONTAL);
				al_flip_display();
				if (!(a % 4))
					an->x += an->speed;
				al_rest(an->time / 1000.0);
				if (an->x >= xMax)
					keep = false;
				a++;
			}
		}
	}
	else {
		bool keep = true;
		while (keep) {
			for (int i = 0; i < an->frames.size() && keep; i++) {
				al_clear_to_color(al_color_name("black")); //al_draw_bitmap(background, 0, 0, 0);
				al_draw_bitmap(an->display_background, 0, 0, 0);
				al_draw_bitmap(an->frames[i], an->x, an->y, 0);
				al_flip_display();
				an->x += an->speed;
				al_rest(an->time / 1000.0);
				if (an->x >= xMax)
					keep = false;
			}
		}
	}

	AllegroClass::unloadSong(an->background_music);
}

vector<int> UserHandler::getSequence(int sequenceLenght)
{
	vector<int> sequence;
	sequence.reserve(sequenceLenght);
	bool leave = false;

	clear();

	do {
		echo();
		do {



			drawSequenceInterface(sequence);
			sequence.emplace_back(getNumberString(4, 0, ERROR_SEQUENCE));
			mvdeleteln(3, 0);
			drawSequenceInterface(sequence);

		} while (sequence.size() < sequenceLenght);


		mvprintw(3, 0, CONFIRM_SEQUENCE);
		bool leave_a = false;
		noecho();
		do {							// En este bloque estoy validando si el usuario quiere usar la sequencia
			char a = getch();
			if (a != ERR) {
				if (a == '\n')
				{
					leave_a = true;
					leave = true;
				}
				else if (a == 27)		// 27 es el ASCII de esc
				{
					leave_a = true;
					leave = false;
					clear();
					sequence.clear();
				}
			}
		} while (!leave_a);

	} while (!leave);


	return sequence;
}




int UserHandler::getNumberString(int posY, int posX, const char * errorMessage) {
	bool leave = false;
	bool isNum = true;
	bool numEnded = false;

	char str[4] = { 0,0,0,0 };


	do {
		isNum = true;
		move(posY, posX);
		if (getnstr(str, 3) != ERR) {

			for (int i = 0; i < 4 && isNum && !numEnded; i++) {

				if (!isdigit(str[i]) && str[i] != 0 && str[i] != '\n') {
					isNum = false;
					color_set(2, NULL);
					mvprintw(posY - 1, posX, errorMessage);
					mvdeleteln(posY, posX);
					color_set(1, NULL);
				}
				else if (str[i] == '\n')
					str[i] = 0;
				if (str[i] == 0)
				{
					numEnded = true;
					leave = true;
				}


			}
		}

	} while (!leave);

	mvdeleteln(posY - 1, 0);
	mvdeleteln(posY, 0);

	return atoi(str);
}


char UserHandler::getSingleLoweredCharInRange(char min, char max, int posY, int posX, const char * errorMessage) {

	char retValue;
	bool leave = false;
	bool err = false;
	do {
		move(posY, posX);
		retValue = getch();
		if (retValue != ERR) {
			retValue = tolower(retValue);
			if ((retValue >= min && retValue <= max))
			{
				leave = true;
				if (err) {
					mvdeleteln(3, 0);
					err = false;
				}

			}
			else
			{
				if (!err)
				{
					color_set(2, NULL);
					mvdeleteln(posY - 1, 0);
					mvprintw(posY - 1, 0, errorMessage);
					err = true;
					color_set(1, NULL);
				}

			}
		}

	} while (!leave);

	return retValue;
}


void drawSequenceInterface(vector<int>& sequence) {
	mvprintw(0, 0, SEQUENCE_ASK);
	mvprintw(1, 0, SELECTED_SEQUENCE);
	move(2, 0);

	for (int num : sequence) {
		string a = to_string(num);
		printw(a.c_str());
		printw("  ");
	}
}

