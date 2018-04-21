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

void UserHandler::draw()
{
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