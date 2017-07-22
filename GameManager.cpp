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
}

void GameManager::initGameboard() {
	/* maxX is going to be the size of the window + a buffer of x pixels. The buffer is for the placement of new obstacles 
	   maxY is window + buffer on top and bottom */
	maxGBWinXY.x = maxWinXY.x + (DEF_BUFFER*2);
	maxGBWinXY.y = maxWinXY.y + (DEF_BUFFER*2);
	ParticleInfo dummyInfo;
	dummyInfo.type = NONE;
	dummyInfo.id = 0;
	
	/* create a vector of vectors, v[maxY][maxX] */
	gameboard = vector< vector<ParticleInfo> > (maxGBWinXY.y, vector<ParticleInfo>(maxGBWinXY.x, dummyInfo));
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

void GameManager::placeObject(Object &o, unsigned long &id) {
	o.draw();
	Obstacles.insert(Obstacles.end(), std::pair<unsigned long,Object>(id,o));
}

void GameManager::placeShip() {
	theShip.draw();
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
	obstacleId = bulletId = explosionId = 0;
	this->win = win;
	input = ' ';
	fr_counter = 0;
	fr_factor = 4;
	setScreenSize();
	initGameboard();
	initWindow();
	initColors();

	theShip = Ship(this->win, &gameboard, Coord {DEF_BUFFER+3, (maxWinXY.y / 2)}, maxWinXY, SHIP, SPACE);
	placeShip();

	testBullet = Bullet(this->win, &gameboard, theShip.getFront()+Coord{1, 0}, maxWinXY, BULLET, SPACE, ++bulletId);
	testBullet.draw();

	testO = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x / 2), (maxWinXY.y / 2)}, maxWinXY, OBSTACLE, SPACE, ++obstacleId);
	testO.setEnemy(SHIP);
	placeObject(testO, obstacleId);

	testO2 = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x), 0}, maxWinXY, OBSTACLE, SPACE, ++obstacleId);
	testO2.setEnemy(SHIP);
	placeObject(testO2, obstacleId);

}

GameManager::~GameManager() {}

short GameManager::run() {
	std::map<unsigned long,Object>::iterator obst_it;
	bool moveShip = false;
	short gameStatus = -1;
	gameover = false;
	Coord trajectory;
	do 
	{
		input = getch();

		/* the idea here is to update the user_coords variable, "move" the ship there,
			then draw a blank where it used to be, finally refreshing the window */
		switch (input){
			case KEY_UP:
				mvprintw(0, 24, "pressed up     ");
				// set the trajectory in the ship
				trajectory = {0, -1}; 
				moveShip = true;
				break;

			case KEY_DOWN:
				mvprintw(0, 24, "pressed down   ");
				trajectory = {0, 1}; 
				moveShip = true;
				break;

			case KEY_LEFT:
				mvprintw(0, 24, "pressed left   ");
				trajectory = {-1, 0}; 
				moveShip = true;
				break;

			case KEY_RIGHT:
				mvprintw(0, 24, "pressed right  ");
				trajectory = {1, 0};
				moveShip = true;
				break;
			// case 32-100:
			// 	mvprintw(0, 24, "pressed %c     ", input);
			// 	break;
			default: 
				break;
		}

		if(moveShip) {
			shipStatus = theShip.move(trajectory);
			if (shipStatus.collided == EDGE) {
				mvprintw(0, 48, "hit the edge  ");
			} else if(shipStatus.collided == GAMEOVER) {
				mvprintw(0, 48, "gameover      ");
				gameover = true;
			} else {
				mvprintw(0, 48, "              ");
			}
			moveShip = false;
		}

		/* after user moves, move objects */
		/* determine background framerate (fr_factor * timeout) and update obstacles
			as necessary 
		*/
		if(Obstacles.size()){
			if(fr_counter == fr_factor && !gameover) {
				Particle obstStatus;
				// move the objects
				for(obst_it = Obstacles.begin(); obst_it != Obstacles.end(); ++obst_it) {
					obstStatus = obst_it->second.dftMove();
					if (obstStatus.collided == GAMEOVER) {
						// mvprintw(0, 48, "gameover object");
						gameover = true;
					} else if (obstStatus.collided == DESTROY) {
						// mvprintw(0, 48, "object is offscreen and can be destroyed");
						// std::cout << "object destroyed, num obst=" << obst_it->second.getId() << std::endl;
						Obstacles.erase(obst_it); // remove from the map
					} 
					// else if (obstStatus.collided == NOHIT) {
					// 	std::cout << "no more object" << std::endl;
					// }
				}
				fr_counter = 0;
			} else {
				fr_counter++;
			}
		}
		mvprintw(0, 100, "%d  ", Obstacles.size()); // testing 

		refresh(); // for status screen
		
		wrefresh(win); // for window

	} while (input != 'q' && !gameover);

	if(input == 'q')
		gameStatus = 0;
	else if (gameover)
		gameStatus = 1;

	return gameStatus; // 0 or 1, or -1 if some strange error occurred

	// std::cout << gameboard[(maxWinXY.y / 2)+DEF_BUFFER][3+DEF_BUFFER].id << std::endl;
}