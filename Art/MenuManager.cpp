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

void MenuManager::initGameboard() {
	/* maxX is going to be the size of the window + a buffer of x pixels. The buffer is for the placement of new obstacles
	maxY is window + buffer on top and bottom */
	maxGBWinXY.x = maxWinXY.x + DEF_BUFFER;
	maxGBWinXY.y = maxWinXY.y + (DEF_BUFFER * 2);
	ParticleInfo dummyParticle;
	dummyParticle.type = NONE;
	dummyParticle.id = 0;

	/* create a vector of vectors, v[maxY][maxX] */
	gameboard = vector< vector<ParticleInfo> >(maxGBWinXY.y, vector<ParticleInfo>(maxGBWinXY.x, dummyParticle));
}


MenuManager::MenuManager(WINDOW * win) {
	win = win;
	input = ' ';
	setScreenSize();
	initGameboard();
	initWindow();
	initColors();
	wmove(win, 10, 10);
	


}

void MenuManager::run() {
	bool moveShip = false;
	Coord trajectory;
	do
	{
		input = getch();

		switch (input) {
		case KEY_UP:
			mvprintw(0, 24, "pressed up     ");
			// set the trajectory in the ship
			trajectory = { 0, -1 };
			moveShip = true;
			break;

		case KEY_DOWN:
			mvprintw(0, 24, "pressed down   ");
			trajectory = { 0, 1 };
			moveShip = true;
			break;

		
			// case 32-100:
			// 	mvprintw(0, 24, "pressed %c     ", input);
			// 	break;
		default:
			break;
		}

		//if (moveShip) {
		//	shipStatus = testO.move(trajectory);
		//	if (shipStatus.collided == EDGE) {
		//		mvprintw(0, 48, "hit the edge  ");
		//	}
		//	else {
		//		mvprintw(0, 48, "              ");
		//	}
		//	moveShip = false;
		//}

		refresh(); 
		wrefresh(win); 

	} while (input != 'q');
}