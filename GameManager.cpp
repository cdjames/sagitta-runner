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
	// for (int y = 0; y < maxY; y++)
	// {
	// 	gameboard.push_back( vector<ParticleInfo>(maxX, dummyParticle) );
	// }
}

void GameManager::placeShip() {
	 // ParticleInfo check {SHIP, 1};
	mvwaddch(win, (maxWinXY.y / 2), 3, '>');
	gameboard[(maxWinXY.y / 2)+DEF_BUFFER][3+DEF_BUFFER] = ParticleInfo {SHIP, 1};
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
	setScreenSize();
	initGameboard();
	initWindow();
	placeShip();
}

GameManager::~GameManager() {}

void GameManager::run() {
	wrefresh(win);
}