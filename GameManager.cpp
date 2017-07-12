/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Implementation of GameManager 
*********************************************************************/

#include "GameManager.hpp"

/* protected */
void GameManager::initWindow() {
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

void GameManager::initGameboard() {
	/* maxX is going to be the size of the window + a buffer of x pixels. The buffer is for the placement of new obstacles 
	   maxY is window + buffer on top and bottom */
	maxGBWinXY.x = maxWinXY.x + DEF_BUFFER;
	maxGBWinXY.y = maxWinXY.y + (DEF_BUFFER*2);
	ParticleInfo dummyParticle;
	dummyParticle.type = NONE;
	dummyParticle.id = 0;
	
	/* create a vector of vectors, v[maxY][maxX] */
	gameboard = vector< vector<ParticleInfo> > (maxGBWinXY.y, vector<ParticleInfo>(maxGBWinXY.x, dummyParticle));
}

void GameManager::initColors() {
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

void GameManager::placeShip() {
	// mvwaddch(win, (maxWinXY.y / 2), 3, '>');
	// gameboard[(maxWinXY.y / 2)+DEF_BUFFER][3+DEF_BUFFER] = ParticleInfo {SHIP, 1};
	testO.draw();
}

void GameManager::moveShip() {}
void GameManager::createObstacles() {}
void GameManager::moveObstacles() {}
void GameManager::doExplosions() {}
void GameManager::fireBullet() {}
void GameManager::moveBullets() {}
void GameManager::gameOver() {}

void GameManager::setScreenSize() {
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    maxWinXY.y = w.ws_row-2; // save top two lines for user feedback
    maxWinXY.x = w.ws_col;
    // std::cout << "maxWinXY.y=" << maxWinXY.y << std::endl;
    // std::cout << "maxWinXY.x=" << maxWinXY.x << std::endl;
}

/* public */
GameManager::GameManager(WINDOW * win) {
	this->win = win;
	input = ' ';
	setScreenSize();
	initGameboard();
	initWindow();
	initColors();
	testO = Object(this->win, &gameboard, Coord {3, (maxWinXY.y / 2)}, maxWinXY);
	placeShip();
}

GameManager::~GameManager() {}

void GameManager::run() {
	do 
	{
		input = getch();
		// save the previous user coordinates
		// prev_user_coords = user_coords;
		// /* determine background framerate (gTimeout * fr_multiplier) and update background
		// 	as necessary 
		// */
		// if(fr_counter == fr_multiplier) {
		// 	moveScreenLeft(); // pure virtual; needs to be implemented in child class
		// 	fr_counter = 0;
		// } else {
		// 	fr_counter++;
		// }

		/* the idea here is to update the user_coords variable, "move" the ship there,
			then draw a blank where it used to be, finally refreshing the window */
		switch (input){
			case KEY_UP:
				mvprintw(0, 24, "pressed up     ");
				// refresh();
				// if(user_coords.y > 0)
				// 	user_coords.y--;
				break;
			case KEY_DOWN:
				mvprintw(0, 24, "pressed down   ");
				// refresh();
				// if(user_coords.y < winY-1)
				// 	user_coords.y++;
				break;
			case KEY_LEFT:
				mvprintw(0, 24, "pressed left   ");
				// refresh();
				// if(user_coords.x > 0)
				// 	user_coords.x--;
				break;
			case KEY_RIGHT:
				mvprintw(0, 24, "pressed right  ");
				// refresh();
				// if(user_coords.x < winX-1)
				// 	user_coords.x++;
				break;
			// case 32-100:
			// 	mvprintw(0, 24, "pressed %c     ", input);
			// 	break;
			default: 
				break;
		}
		refresh(); // for status screen
		
		// erase the old ship
		// mvwaddch(win, prev_user_coords.y, prev_user_coords.x, BLANK);
		// // move the ship
		// if(currentCell[user_coords.y][user_coords.x] != 0 || currentCell[prev_user_coords.y][prev_user_coords.x] != 0) {
		// 	wrefresh(win);
		// 	doGameOver = TRUE;
		// 	break; // get out of loop, game is over
		// }
		// else {
		// 	mvwaddch(win, user_coords.y, user_coords.x, SHIP);
		// }
		wrefresh(win); // for window
		// refresh();

	} while (input != 'q');
	// wrefresh(win);
	// refresh();
	// testO.testgameboard();
	// std::cout << gameboard[(maxWinXY.y / 2)+DEF_BUFFER][3+DEF_BUFFER].id << std::endl;
}