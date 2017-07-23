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

void GameManager::placeObstacle(Obstacle &o, unsigned long &id) {
	o.draw();
	std::map<unsigned long,Obstacle>::iterator cntr;
	cntr = Obstacles.insert(Obstacles.end(), std::pair<unsigned long,Obstacle>(id,o));
}

void GameManager::placeExplosion(unsigned long &id, Coord start) {
	std::map<unsigned long,Explosion>::iterator obst_it = Explosions.insert(Explosions.end(), std::pair<unsigned long,Explosion>(id,Explosion(this->win, 
											&gameboard, 
											start - Coord{0,1}, 
											maxWinXY, EXPLOSION, SPACE, id)));
	obst_it->second.draw();
	// obst_it->second.setTrajectory(Coord{1,0});
}

void GameManager::placeBullet(unsigned long &id) {
	// std::cout << "shipx=" << theShip.getFront().x << "shipy" << theShip.getFront().y << std::endl;
	std::map<unsigned long,Object>::iterator obst_it = Bullets.insert(Bullets.end(), std::pair<unsigned long,Object>(id,Bullet(this->win, 
											&gameboard, 
											theShip.getFront()+Coord{1, 0}, 
											maxWinXY, BULLET, SPACE, id)));
	
	obst_it->second.draw();
	obst_it->second.setTrajectory(Coord{1,0});
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
	fr_counter = exp_fr_counter = 0;
	fr_factor = 4;
	exp_fr_factor = 3;
	setScreenSize();
	initGameboard();
	initWindow();
	initColors();

	theShip = Ship(this->win, &gameboard, Coord {DEF_BUFFER+3, (maxWinXY.y / 2)}, maxWinXY, SHIP, SPACE, 1);
	placeShip();

	// testBullet = Bullet(this->win, &gameboard, theShip.getFront()+Coord{1, 0}, maxWinXY, BULLET, SPACE, ++bulletId);
	// testBullet.setTrajectory(Coord{1,0});
	// Bullets.insert(Bullets.end(), std::pair<unsigned long,Object>(bulletId,testBullet));
	// testBullet.draw();

	// testO = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x / 2), (maxWinXY.y / 2)}, maxWinXY, OBSTACLE, SPACE, ++obstacleId);
	// testO.setEnemy(SHIP);
	// placeObstacle(testO, obstacleId);

	// mvprintw(0, 80, "id=%d", obstacleId);

	// testO2 = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x), 0}, maxWinXY, OBSTACLE, SPACE, ++obstacleId);
	// testO2.setEnemy(SHIP);
	// placeObstacle(testO2, obstacleId);

	for (int i = 0; i < 5; i++)
	{
		testO2 = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x), i*4}, maxWinXY, OBSTACLE, SPACE, ++obstacleId);
		testO2.setEnemy(SHIP);
		placeObstacle(testO2, obstacleId);
	}

	// placeExplosion(++explosionId, Coord {DEF_BUFFER+3, (maxWinXY.y / 3)});
	// testExplosion = Explosion(this->win, &gameboard, Coord {DEF_BUFFER+3, (maxWinXY.y / 3)}, maxWinXY, EXPLOSION, SPACE, ++explosionId);
	// testExplosion.draw();
}

GameManager::~GameManager() {}

short GameManager::run() {
	// std::map<unsigned long,Obstacle>::iterator obst_it;
	// std::map<unsigned long,Bullet>::iterator bull_it;
	Particle obstStatus;
	bool moveShip = false;
	bool makeExplosion = false;
	short gameStatus = -1;
	gameover = false;
	Coord trajectory;
	Coord exp_coord;
	do 
	{
		std::map<unsigned long,Obstacle>::iterator obst_it;
		// std::map<unsigned long,Bullet>::iterator bull_it;
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
			case 32:
				mvprintw(0, 24, "pressed space  ");
				/* create a new bullet and add to Bullets map */
				// placeBullet(++bulletId);
				break;
			default: 
				break;
		}


		/* move the bullets */
		if(Bullets.size()){
			// if(exp_fr_counter == exp_fr_factor) {
			// move the objects
			
			
			for(std::map<unsigned long,Object>::iterator bull_it = Bullets.begin(); bull_it != Bullets.end(); ++bull_it) {
				explosion:
				// obstStatus = bull_it->second.dftMove();
				obstStatus = bull_it->second.move(Coord{1, 0});
				mvprintw(0, 60, "id=%d", obstStatus.info.id);
				if (obstStatus.collided == GAMEOVER) {
					/* find the Obstacle it hit and remove it */
					obst_it = Obstacles.find(obstStatus.info.id);
					obst_it->second.erase();
					Obstacles.erase(obst_it);
					
					/* must erase bullet after obstacle */
					bull_it->second.erase();
					Bullets.erase(bull_it);

					// printw("obstStatus.core.coords=%d,%d", obstStatus.core.coords.x, obstStatus.core.coords.y);
					makeExplosion = true;

				} else if (obstStatus.collided == DESTROY) {
						mvprintw(0, 48, "object is offscreen and can be destroyed");
						// std::cout << "object destroyed, num obst=" << obst_it->second.getId() << std::endl;
						bull_it->second.erase();
						Bullets.erase(bull_it); // remove from the map
					}
				// placeExplosion(++explosionId, Coord {DEF_BUFFER+3, (maxWinXY.y / 3)});
				// else if (obstStatus.collided == HIT) {
				// 	// mvprintw(0, 48, "object is offscreen and can be destroyed");
				// 	// std::cout << "object destroyed, num obst=" << obst_it->second.getId() << std::endl;

				// } 
				// else if (obstStatus.collided == NOHIT) {
				// 	std::cout << "no more object" << std::endl;
				// }

			}
			// 	exp_fr_counter = 0;
			// } else {
			// 	exp_fr_counter++;
			// }
		}
		mvprintw(1, 100, "%d  ", Bullets.size()); // testing

		// if(makeExplosion) {
		// 	printw("obstStatus.core.coords=%d,%d", obstStatus.core.coords.x, obstStatus.core.coords.y);

		// 	placeExplosion(++explosionId, obstStatus.core.coords);
		// 	makeExplosion = false;
		// }

		// /* handle explosions */
		// else if(Explosions.size()){
		// 	if(exp_fr_counter == exp_fr_factor) {
		// 		for(std::map<unsigned long,Explosion>::iterator obst_it = Explosions.begin(); obst_it != Explosions.end(); ++obst_it) {
		// 			unsigned short still_animating = obst_it->second.animate();
		// 			if (!still_animating) {
		// 				obst_it->second.erase();
		// 				Explosions.erase(obst_it);
		// 			}
		// 		}
		// 		exp_fr_counter = 0; 
		// 	} else {
		// 		exp_fr_counter++;
		// 	}
		// }

		/* move the ship */
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
				// move the objects
				for(std::map<unsigned long,Obstacle>::iterator obst_it = Obstacles.begin(); obst_it != Obstacles.end(); ++obst_it) {
					obstStatus = obst_it->second.dftMove();
					if (obstStatus.collided == GAMEOVER) {
						mvprintw(0, 48, "object hit ship");
						gameover = true;
					} else if (obstStatus.collided == DESTROY) {
						// mvprintw(0, 48, "object is offscreen and can be destroyed");
						// std::cout << "object destroyed, num obst=" << obst_it->second.getId() << std::endl;
						Obstacles.erase(obst_it); // remove from the map
					} 
					// else if (obstStatus.collided == HIT) {
					// 	// std::cout << "no more object" << std::endl;
					// 	continue;
					// }
				}
				fr_counter = 0;
			} else {
				fr_counter++;
			}
		}
		// mvprintw(0, 100, "%d  ", Obstacles.size()); // testing 

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