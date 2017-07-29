/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Implementation of GameManager 
*********************************************************************/

#include "GameManager.hpp"

/* public */
GameManager::GameManager(WINDOW * win) {
	Obstacles.reserve(MAX_OBSTACLES);
	obstacleId = bulletId = explosionId = numObstaclesDestroyed= 0;
	this->win = win;
	input = ' ';
	fr_counter = exp_fr_counter = create_counter = 0;
	fr_factor = 3;
	exp_fr_factor = 4;
	create_factor = 15;
	max_bullets = MAX_BULLETS;
	curr_theme = SPACE;
	theme_counter = DEF_THM_COUNTER;
	setScreenSize();
	initGameboard();
	initWindow();
	initColors();

	theShip = Ship(this->win, &gameboard, Coord {DEF_BUFFER+3, (maxWinXY.y / 2)}, maxWinXY, SHIP, SPACE, 1);
	placeShip();
}

GameManager::~GameManager() {}

short GameManager::run() {
	// unsigned short still_animating;
	// Particle obstStatus;
	move_ship = false;
	makeExplosion = false;
	gameStatus = -1;
	gameover = false;
	// Coord trajectory;
	// Coord exp_coord;
	// Coord ship_coord;
	basequadsize = maxWinXY.y/QUAD_PARTS;
	quadsize = basequadsize;
	prevquadsize = 0;
	// unsigned short temp_theme; 
	num_theme_loops = 0;
	num_time_loops = 0;
	// int randY = rand()%(quadsize) + prevquadsize;

	mvprintw(0,0,"Press 'q' to quit.");	// instructions at top of screen
	
	start_time = time_now = time(0);
	target_time = start_time + DIFF_TIMEOUT;

	/* main loop */
	do 
	{
		input = getch();

		/* increase difficulty */
		time_now = time(0);
		if(time_now >= target_time) {
			target_time = time_now + DIFF_TIMEOUT + num_time_loops;
			/* increase speed of object refresh rate */
			if(fr_factor > 0)
				--fr_factor;
			/* decrease number of bullets on screen simultaneously */
			if(max_bullets > MIN_BULLETS)
				--max_bullets;
			/* increase speed of object creation */
			if(num_theme_loops%OBS_CREATE_FACTOR == 0)
				--create_factor;

			num_time_loops += DIFF_TIME_ADD; 
		}

		/* change theme whenever number of obstacles destroyed is greater than the theme counter. */
		if(numObstaclesDestroyed >= theme_counter) {
			temp_theme = curr_theme;
			(temp_theme >= NUM_THEMES-1) ? temp_theme = 0 : temp_theme++;
			curr_theme = (ThemeType)temp_theme;
			theme_counter = numObstaclesDestroyed + DEF_THM_COUNTER + num_theme_loops;
			num_theme_loops++;
		}

		/* create random obstacles */
		if(create_counter >= create_factor && Obstacles.size() < MAX_OBSTACLES) {
			testO2 = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x), 
				rand()%(quadsize-prevquadsize) + prevquadsize}, maxWinXY, OBSTACLE, curr_theme, ++obstacleId);
			testO2.setEnemy(SHIP);
			placeObstacle(testO2, obstacleId);
			create_counter = 0;
			prevquadsize = quadsize;
			quadsize += basequadsize;
			if(quadsize >= maxWinXY.y) {
				quadsize = basequadsize;
				prevquadsize = 0;
			}
			create_counter = 0;
		} else {
			create_counter++;
		}
		/* the idea here is to update the user_coords variable, "move" the ship there,
			then draw a blank where it used to be, finally refreshing the window */
		switch (input){
			case KEY_UP:
				// mvprintw(0, 24, "pressed up     ");
				// set the trajectory in the ship
				trajectory = {0, -1}; 
				move_ship = true;
				break;

			case KEY_DOWN:
				// mvprintw(0, 24, "pressed down   ");
				trajectory = {0, 1}; 
				move_ship = true;
				break;

			case KEY_LEFT:
				// mvprintw(0, 24, "pressed left   ");
				trajectory = {-1, 0}; 
				move_ship = true;
				break;

			case KEY_RIGHT:
				// mvprintw(0, 24, "pressed right  ");
				trajectory = {1, 0};
				move_ship = true;
				break;
			case 32:
				// mvprintw(0, 24, "pressed space  ");
				/* create a new bullet and add to Bullets map */
				if(Bullets.size() < max_bullets)
					placeBullet(++bulletId);
				break;
			default: 
				break;
		}


		/* move the bullets */
		if(Bullets.size()){
			// if(exp_fr_counter == exp_fr_factor) {
			// move the objects
			
			bull_it = Bullets.begin();
			while(bull_it != Bullets.end()) {
				obstStatus = bull_it->second.dftMove();
				// mvprintw(0, 60, "id=%d", obstStatus.info.id);
				temp_bull_it = bull_it;
				if (obstStatus.collided == GAMEOVER) {
					// mvprintw(maxWinXY.y-1, 50, "gameover object");
					
					/* find the Obstacle it hit and remove it */
					obst_it = Obstacles.find(obstStatus.info.id);
					temp_obst_it = obst_it;
					++obst_it;
					temp_obst_it->second.erase();
					Obstacles.erase(temp_obst_it);
					
					/* must erase bullet after obstacle */
					++bull_it;
					temp_bull_it->second.erase();
					Bullets.erase(temp_bull_it);

					makeExplosion = true;
					exp_coord = obstStatus.core.coords;
					numObstaclesDestroyed++;
				} else if (obstStatus.collided == DESTROY) {
					++bull_it;
					Bullets.erase(temp_bull_it);
				} else {
					++bull_it;
				}
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
		
		/* move the ship */
		if(move_ship) {
			shipStatus = theShip.move(trajectory);
			if (shipStatus.collided == EDGE) {
				// mvprintw(0, 48, "hit the edge  ");
			} else if(shipStatus.collided == GAMEOVER) {
				/* find the Obstacle it hit and remove it */
				obst_it = Obstacles.find(shipStatus.info.id);
				temp_obst_it = obst_it;
				++obst_it;
				temp_obst_it->second.erase();
				Obstacles.erase(temp_obst_it);
				ship_coord = shipStatus.core.coords;
				gameover = true;
			} else {
				mvprintw(0, 48, "              ");
			}
			move_ship = false;

		}

		/* after user moves, move objects */
		/* determine background framerate (fr_factor * timeout) and update obstacles
			as necessary 
		*/
		if(Obstacles.size()){
			if(fr_counter >= fr_factor && !gameover) {
				// move the objects
				obst_it = Obstacles.begin();
				while(obst_it != Obstacles.end()){
					obstStatus = obst_it->second.dftMove();
					temp_obst_it = obst_it;
					if (obstStatus.collided == GAMEOVER) {

						// mvprintw(90, 48, "object hit ship");
						++obst_it;
						ship_coord = obstStatus.core.coords;
						temp_obst_it->second.erase();
						Obstacles.erase(temp_obst_it);
						gameover = true;
					} else if (obstStatus.collided == DESTROY) {
						++obst_it;
						temp_obst_it->second.erase();
						Obstacles.erase(temp_obst_it); // remove from the map
					} 
					// else if (obstStatus.collided == HIT) {
					// 	// std::cout << "no more object" << std::endl;
					// 	continue;
					// }
					else{
						++obst_it;
					}
				}
				fr_counter = 0;
			} else {
				fr_counter++;
			}
		}

		// mvprintw(0, 100, "%d  ", Obstacles.size()); // testing
		mvprintw(0, maxWinXY.x-STAT_ENEMIES, "| # enemies: %d |", numObstaclesDestroyed);
		mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS, "| # bullets: %d ", max_bullets-Bullets.size()); // testing	


		/* create new explosions */
		if(makeExplosion && !gameover) {
			// mvprintw(4, 80,"obstStatus.core.coords=%d,%d", exp_coord.x, exp_coord.y);

			placeExplosion(++explosionId, exp_coord);
			// placeExplosion(++explosionId, obstStatus.core.coords);
			makeExplosion = false;
		}

		/* animate explosions */
		if(Explosions.size() && !gameover){	
			if(exp_fr_counter >= exp_fr_factor) {
				exp_it = Explosions.begin();
				while(exp_it != Explosions.end()) {
				// for(std::map<unsigned long,Explosion>::iterator obst_it = Explosions.begin(); obst_it != Explosions.end(); ++obst_it) {
					still_animating = exp_it->second.animate();
					if (!still_animating) {
						temp_exp_it = exp_it;
						++exp_it;
						temp_exp_it->second.erase();
						Explosions.erase(temp_exp_it);
					} else {
						++exp_it;
					}
				}
				exp_fr_counter = 0; 
			} else {
				exp_fr_counter++;
			}
		}

		wnoutrefresh(stdscr); // for status screen
		wnoutrefresh(win);    // for window
		doupdate();

	} while (input != 'q' && !gameover);

	/* handle game over scenario */
	if(input == 'q') // if user quit
		gameStatus = 0;
	else if (gameover) { // if user died
		mvprintw(0, 0, "GAMEOVER - press 'q' to quit  ");
		gameStatus = 1;
		/* erase the ship */
		theShip.erase();
		// wrefresh(win); // for window
		/* add an explosion where the ship was */
		// mvprintw(4, 30,"ship_coord=%d,%d", ship_coord.x, ship_coord.y);
		Explosion shipExplosion(this->win, 
								&gameboard, 
								ship_coord - Coord{1,1}, 
								maxWinXY, EXPLOSION, FOOD, 1);
		do 
		{
			if(exp_fr_counter == exp_fr_factor) {
				shipExplosion.animate();
				exp_fr_counter = 0; 
			} else {
				exp_fr_counter++;
			}
			wrefresh(win); // for window
			input = getch();
		} while (input != 'q');
	}

	return gameStatus; // 0 if quit, 1 if died, or -1 if some strange error occurred
}

void GameManager::updateSettings(MenuManager &MM){
	difficulty = MM.difficultyLevel;
	fr_factor = difficulty;
	max_bullets += difficulty;
}

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
	// o.draw();
	std::unordered_map<unsigned long,Obstacle>::iterator cntr;
	cntr = Obstacles.insert(Obstacles.end(), std::pair<unsigned long,Obstacle>(id,o));
}

void GameManager::placeExplosion(unsigned long &id, Coord start) {
	std::map<unsigned long,Explosion>::iterator obst_it = Explosions.insert(Explosions.end(), std::pair<unsigned long,Explosion>(id,Explosion(this->win, 
											&gameboard, 
											start - Coord{0,1}, 
											maxWinXY, EXPLOSION, SPACE, id)));
	// obst_it->second.draw();
	// obst_it->second.setTrajectory(Coord{1,0});
}

void GameManager::placeBullet(unsigned long &id) {
	// std::cout << "shipx=" << theShip.getFront().x << "shipy" << theShip.getFront().y << std::endl;
	std::map<unsigned long,Bullet>::iterator obst_it = Bullets.insert(Bullets.end(), std::pair<unsigned long,Bullet>(id,Bullet(this->win, 
											&gameboard, 
											theShip.getFront()+Coord{1, 0}, 
											maxWinXY, BULLET, SPACE, id)));
	
	// obst_it->second.draw();
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


