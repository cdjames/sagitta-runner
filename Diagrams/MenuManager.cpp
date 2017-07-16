#include "MenuManager.hpp"

void MenuManager::initWindow() {
	// scrollok(win, FALSE);
	win = newwin(maxWinXY.y, maxWinXY.x, 2, 0); // make a new window
	keypad(win, TRUE);
	// char c = 32;
	// keypad(win, TRUE);
	// for (int y = 0; y < maxGBWinXY.y; y++)
	// {
	// 	for (int x = 0; x < maxGBWinXY.x; x++)
	// 	{
	// mvwaddch(win, 5, 10, '>');
	// 		// if(c < 126)
	// 		// 	c++;
	// 		// else
	// 		// 	c = 32;
	// 	}
	// }
	// wrefresh(win);
}


void MenuManager::initColors() {
	start_color();
	// printw("This terminal supports %d colors\n", COLORS);
	for (int i = 0; i < COLORS; i++)
	{
		/* code */
		init_pair(i, i, COLOR_BLACK);
		// attron(COLOR_PAIR(i));
		// printw("%d ", i);
	}
}

void MenuManager::setScreenSize() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	maxWinXY.y = w.ws_row - 2; // save top two lines for user feedback
	maxWinXY.x = w.ws_col;
	// std::cout << "maxWinXY.y=" << maxWinXY.y << std::endl;
	// std::cout << "maxWinXY.x=" << maxWinXY.x << std::endl;
}
//
//void MenuManager::initGameboard() {
//	/* maxX is going to be the size of the window + a buffer of x pixels. The buffer is for the placement of new obstacles
//	maxY is window + buffer on top and bottom */
//	maxGBWinXY.x = maxWinXY.x + DEF_BUFFER;
//	maxGBWinXY.y = maxWinXY.y + (DEF_BUFFER * 2);
//	//ParticleInfo dummyParticle;
//	//dummyParticle.type = NONE;
//	//dummyParticle.id = 0;
//
//	/* create a vector of vectors, v[maxY][maxX] */
////	gameboard = vector< vector<ParticleInfo> >(maxGBWinXY.y, vector<ParticleInfo>(maxGBWinXY.x, dummyParticle));
//}


MenuManager::MenuManager(WINDOW * win) {
	win = win;
	input = ' ';
	setScreenSize();
//	initGameboard();
	initWindow();
	initColors(); 
}

void MenuManager::initMenu() {
	yCoord = 10;
	xCoord = 13;
	mvprintw(6, 8, "Use up and down to move the cursor and enter to select an option.");
	mvprintw(yCoord, 13, ">");
	mvprintw(10, xCoord + 2, "Start Game");
	mvprintw(11, xCoord + 2, "Settings");
	mvprintw(12, xCoord + 2, "Quit");
}


int MenuManager::settingsScreen() {
	yCoord = 10;
	xCoord = 13;
	mvprintw(6, 8, "Select the setting that you would like to change. Press escape or choose quit to go back");
	mvprintw(yCoord, 13, ">");
	mvprintw(10, xCoord + 2, "Difficulty");
	mvprintw(11, xCoord + 2, "Setting2");
	mvprintw(12, xCoord + 2, "Setting3");
	mvprintw(13, xCoord + 2, "Quit");
	input = getch();
	int choice = 0; //stores the user's menu choice
	switch (input) {
		case 10: // Enter
			if (yCoord == 10) { 
				choice = 1;
			}
			else if (yCoord == 11) {
				choice = 2;
			}
			else if (yCoord == 12) {
				choice = 3;
			}
			else if (yCoord == 13) {
				choice = 4;
			}

		case KEY_UP:
			if (yCoord > 10) {
				mvprintw(yCoord, xCoord, " ");
				yCoord--;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yCoord < 14) {
				mvprintw(yCoord, xCoord, " ");
				yCoord++;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

	}
}

int MenuManager::run() {
	initMenu();
	int quit = 0;
	do
	{
		input = getch();
		switch (input) {
		case KEY_UP:
			if (yCoord > 10) {
				mvprintw(yCoord, xCoord, " ");
				yCoord--;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yCoord < 12) {
				mvprintw(yCoord, xCoord, " ");
				yCoord++;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case 10:	// Enter key: "KEY_ENTER" doesn't work. 
			if (yCoord == 10) {
				quit = -1; //quit the game
			}
			else if (yCoord == 11) {
				wrefresh(win);
				int option = settingsScreen();
				if (option == 10) { // difficulty menu
					// finish
					//wrefresh(win);
				}
				else if (option == 11) { //another setting menu
					//finish
				}

				else if (option == 12) { //another setting menu
					//finish
				}

				else if (option == 13) { // go back a screen
					run();
				}
				yCoord = 10;
				xCoord = 13;
			}
			else if (yCoord == 12) {
				quit = 1; //play the game
			}
			break; 

		default:
			break;
		}
		refresh(); 

	} while (quit == 0);
	wrefresh(win);

	return quit;
}