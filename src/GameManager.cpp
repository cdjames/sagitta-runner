/*******************************************************************
Author: Collin James
** Date: 7/9/17
** Description: Implementation of GameManager 
*********************************************************************/

#include "GameManager.hpp"

/* public */
GameManager::GameManager(WINDOW * win, NetworkManager * NM) {
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
	score = 0;
	this->NM = NM;
	playerNum = this->NM->getPlayerNumber();
	setScreenSize();
	initGameboard();
	initColors();
	initWindow();

	theShip = Ship(this->win, &gameboard, Coord {DEF_BUFFER+3, (maxWinXY.y / 2)}, maxWinXY, SHIP, SPACE, 1, 0);
	placeShip();
}

GameManager::~GameManager() {}

short GameManager::run(vector<double> * timing_info) {
	move_ship = false;
	makeExplosion = false;
	gameStatus = -1;
	gameover = false;
	basequadsize = maxWinXY.y/QUAD_PARTS;
	quadsize = basequadsize;
	prevquadsize = 0;
	num_theme_loops = 0;
	num_time_loops = 0;

	/* turn on quit message color and put message */
	wattron(stdscr, COLOR_PAIR(QUIT_COLOR));
	mvprintw(0,0,"Press 'q' to quit.  ");	// instructions at top of screen
	wattroff(stdscr, COLOR_PAIR(QUIT_COLOR));

	start_time = time_now = time(0);
	target_time = start_time + DIFF_TIMEOUT;

	prev_hs = NM->getScore(true);

	/* main loop */
	_gameLoop(timing_info);

	/* handle game over scenario  */
	return _gameOver(); // 0 if quit, 1 if died, or -1 if some strange error occurred
}

int GameManager::getFinalScore() {
	return this->score;
}

void GameManager::updateSettings(int diff){
	//Our scales were backwards. This mostly fixes it. 
	if (diff < 2)
		diff = 10;
	else
		diff = 10 - diff;

	difficulty = diff;
	fr_factor = difficulty;
	max_bullets += difficulty;
}

/* protected */
short GameManager::_gameOver() {
	wattroff(stdscr, COLOR_PAIR(STAT_COLOR));
	bool print_hs = false;
	/* send game over */
	NM->sendCoord(GM_GAMEOVER, playerNum);
	if(score > prev_hs)
		print_hs = true;
	/* attempt to synchronize scores with other player in case games get off */
	do{
		NM->setScore(score, print_hs);
		prev_hs = score;
		score = NM->getScore(print_hs);
	} while(score > prev_hs);
	
	/* stop the server connection */
	NM->gameOver();

	/* handle game over scenario */
	if(input == 'q') // if user quit
		gameStatus = 0;
	else if (gameover) { // if user died
		wattron(stdscr, COLOR_PAIR(GO_COLOR));
		mvprintw(0, 0, "GAMEOVER - press 'q'");
		wattroff(stdscr, COLOR_PAIR(GO_COLOR));
		gameStatus = 1;
		/* erase the ship */
		theShip.erase();
				
		/* add an explosion where the ship was */
		Explosion shipExplosion(this->win, 
								&gameboard, 
								ship_coord - Coord{1,1}, 
								maxWinXY, EXPLOSION, FOOD, 1, 0);
		int cc = HS_COLOR; // for animating 
		do 
		{
			if(exp_fr_counter == exp_fr_factor) {
				/* animate high score */
				if(print_hs) {
					cc = cc == ALT_COLOR ? HS_COLOR : ALT_COLOR;
					wattron(stdscr, COLOR_PAIR(cc));
					mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS-STAT_SCORE, " new high!: %d ", score);
					wattroff(stdscr, COLOR_PAIR(cc));
				}
				/* animate explosion */
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

void GameManager::_serverComm() {
	if(playerNum == 1) { 
		if ( input != KEY_LEFT && input != KEY_RIGHT && input != KEY_SPACE )
			input = ERR; 
	} else {
		if( input != KEY_UP && input != KEY_DOWN )
			input = ERR;
	}
				
	NM->sendCoord(input, playerNum);
	op_input = NM->getCoord(playerNum);
}

void GameManager::_gameLoop(vector<double> * timing_info) {
	int y, x; // used for quit message
	int numbps, rand_pos, rand_obj_seed;
	/* https://stackoverflow.com/questions/1120478/capturing-a-time-in-milliseconds
	*/
	#ifdef TIMING
	double loop_avg_t = 0,
		loop_max_t = 0.0,
		loop_min_t = std::numeric_limits<double>::max(),
		loop_start_t = 0,
		loop_end_t = 0,
		loops = 0,
		loop_total_t = 0,
		loop_t = 0;
	#endif
	// std::thread server_comm_thread;
	/* turn on player number color and print player */
	wattron(stdscr, COLOR_PAIR(PN_COLOR));
	mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS-STAT_SCORE-STAT_PLAYER, "P%d ", playerNum); // display player number	
	wattroff(stdscr, COLOR_PAIR(PN_COLOR));
	
	/* turn on status colors*/
	wattron(stdscr, COLOR_PAIR(STAT_COLOR));
	mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS-STAT_SCORE-STAT_PLAYER+STAT_PL_MSG_OFFSET, "| "); // display player number	divider "| "

	/* main loop */
	do 
	{
		time_now = time(0);
		#ifdef TIMING
		loop_start_t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		// time_now = (int) loop_start_t *1000;
		#endif

		/* get input */
		input = getch();
		if(playerNum == 1) { 
			if ( input != KEY_LEFT && input != KEY_RIGHT && input != KEY_SPACE && input != 'q')
				input = ERR; 
		} else {
			if( input != KEY_UP && input != KEY_DOWN && input != 'q' )
				input = ERR;
		}
					
		NM->sendCoord(input, playerNum);
		op_input = NM->getCoord(playerNum);
		/* send input to server in another thread */
		// server_comm_thread = std::thread(&GameManager::_serverComm, this);

		/* increase difficulty */
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
			numbps = OBJ_BLPRNTS[OBSTACLE][curr_theme].size();
			rand_pos = (cj_rand()%(quadsize-prevquadsize)) + prevquadsize;
			rand_obj_seed = cj_rand()%numbps;
			#ifdef DEBUG
			mvprintw(1, 0, "pos=%d", rand_pos);
			mvprintw(2, 0, "seed=%d", rand_obj_seed);
			#endif
			rand_obstacle = Obstacle(this->win, &gameboard, Coord {(maxWinXY.x), 
				rand_pos}, maxWinXY, OBSTACLE, curr_theme, ++obstacleId, rand_obj_seed);
			placeObstacle(rand_obstacle, obstacleId);
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

		/* handle user input at the local computer. See _serverComm()
		   for what to expect for each player */
		// server_comm_thread.join(); // make sure you have the input you need
		switch (input) {
			/* player 1 */
			case KEY_LEFT:
				trajectory = {-1, 0}; 
				move_ship = true;
				break;

			case KEY_RIGHT:
				trajectory = {1, 0};
				move_ship = true;
				break;

			case KEY_SPACE:
				/* create a new bullet and add to Bullets map */
				if(Bullets.size() < max_bullets)
					placeBullet(++bulletId);
				break;
			/* player 2 */
			case KEY_UP:
				trajectory = {0, -1}; 
				move_ship = true;
				break;

			case KEY_DOWN:
				trajectory = {0, 1}; 
				move_ship = true;
				break;
			/* both players */
			case 'q': // user wants to quit
				gameover = true;

			/* input == ERR (i.e. no valid input) */
			default: 
				trajectory = {0, 0};
				break;
			}
		/* handle user input from the remote computer. From _serverComm() */
		switch (op_input){
			case KEY_UP:
				trajectory += {0, -1}; 
				move_ship = true;
				break;

			case KEY_DOWN:
				trajectory += {0, 1}; 
				move_ship = true;
				break;

			case KEY_LEFT:
				trajectory += {-1, 0}; 
				move_ship = true;
				break;

			case KEY_RIGHT:
				trajectory += {1, 0};
				move_ship = true;
				break;

			case KEY_SPACE:
				/* create a new bullet and add to Bullets map */
				if(Bullets.size() < max_bullets)
					placeBullet(++bulletId);
				break;
			/* in case clients are out of sync, look out for game over code */
			case 'q':
				/* other user quit, so print a message and end game (fall through to gameover) */
				/* roughly in the middle of the screen */
				y = maxWinXY.y/2 - 2;
				x = maxWinXY.x/2 - strlen(QUIT_MSG1)/2;
				mvprintw(y++, x, QUIT_MSG1);
				mvprintw(y++, x, QUIT_MSG2);
				mvprintw(y++, x, QUIT_MSG3, (playerNum == 1 ? 2 : 1) );
				mvprintw(y++, x, QUIT_MSG4);

			case GM_GAMEOVER:
				gameover = true;
				break;
				
			default: // trajectory stays {0, 0}
				break;
		}

		if(!gameover) {

			/* move the bullets */
			if(Bullets.size()){			
				bull_it = Bullets.begin();
				while(bull_it != Bullets.end()) {
					obstStatus = bull_it->second.dftMove();
					// mvprintw(0, 60, "id=%d", obstStatus.info.id);
					temp_bull_it = bull_it;
					if (obstStatus.collided == GAMEOVER) { // hit an obstacle
						#ifdef DEBUG
						mvprintw(1, 1, "        ");
						mvprintw(2, 1, "bull hit");
						#endif
						// mvprintw(maxWinXY.y-1, 50, "gameover object");
						
						/* find the Obstacle it hit and remove it */
						obst_it = Obstacles.find(obstStatus.info.id);
						temp_obst_it = obst_it;
						++obst_it;
						/* add to score */
						score += temp_obst_it->second.points;
						temp_obst_it->second.erase();
						Obstacles.erase(temp_obst_it);
						
						/* must erase bullet after obstacle */
						++bull_it;
						temp_bull_it->second.erase();
						Bullets.erase(temp_bull_it);

						/* make an explosion */
						makeExplosion = true;
						exp_coord = obstStatus.core.coords;
						numObstaclesDestroyed++;
					} else if (obstStatus.collided == DESTROY) {
						++bull_it;
						Bullets.erase(temp_bull_it);
					} else {
						++bull_it;
					}
				}
			}
			
			/* move the ship */
			if(move_ship) {
				shipStatus = theShip.move(trajectory);
				if (shipStatus.collided == EDGE) {
					continue;
				} else if(shipStatus.collided == GAMEOVER) {
					/* find the Obstacle it hit and remove it */
					obst_it = Obstacles.find(shipStatus.info.id);
					temp_obst_it = obst_it;
					++obst_it;
					temp_obst_it->second.erase();
					Obstacles.erase(temp_obst_it);
					ship_coord = shipStatus.core.coords;
					gameover = true;
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
						} else if (obstStatus.collided == DESTROY) {  // moved offscreen
							++obst_it;
							score -= temp_obst_it->second.penalty;
							if(score < 0 && difficulty > 2)
								score = 0;
							temp_obst_it->second.erase();
							Obstacles.erase(temp_obst_it); // remove from the map
						} 
						else if (obstStatus.collided == HIT) { // hit by a bullet
							#ifdef DEBUG
							mvprintw(1, 1, "hit by");
							mvprintw(2, 1, "       ");
							#endif
							/* find the Bullet that hit it and remove it */
							bull_it = Bullets.find(obstStatus.info.id);
							temp_bull_it = bull_it;
							++bull_it;
							temp_bull_it->second.erase();
							Bullets.erase(temp_bull_it);

							/* erase obstacle and add to score */
							++obst_it;
							score += temp_obst_it->second.points;
							temp_obst_it->second.erase();
							Obstacles.erase(temp_obst_it);
							
							/* make an explosion */
							makeExplosion = true;
							exp_coord = obstStatus.core.coords;
							numObstaclesDestroyed++;
						}
						else{
							++obst_it;
						}
					}
					fr_counter = 0;
				} else {
					fr_counter++;
				}
			}

			/* update status area */
			// mvprintw(0, 100, "%d  ", Obstacles.size()); // testing
			mvprintw(0, maxWinXY.x-STAT_ENEMIES, "| # enemies: %d ", numObstaclesDestroyed);
			mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS, "| # bullets: %d ", max_bullets-Bullets.size()); // testing	
			mvprintw(0, maxWinXY.x-STAT_ENEMIES-STAT_BULLETS-STAT_SCORE, " score: %d ", score); // testing	


			/* create new explosions */
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

		} // end !gameover

		#ifdef TIMING
		if(timing_info != NULL){
			loop_end_t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			loop_t = loop_end_t - loop_start_t;
			if(loop_t > loop_max_t) { loop_max_t = loop_t; }
			if(loop_t < loop_min_t && loop_t > 1) { loop_min_t = loop_t; }
			loop_total_t += loop_t;
			loops++;
		}
		#endif

	} while (input != 'q' && !gameover); // game is over if you get past here; _gameOver will be called next

	/* timing stuff */
	#ifdef TIMING
	loop_avg_t = loop_total_t/loops;
	if(timing_info != NULL){
		timing_info->push_back(loop_avg_t);
		timing_info->push_back(loop_max_t);
		timing_info->push_back(loop_min_t);
	}
	#endif
}

void GameManager::initWindow() {
	// scrollok(win, FALSE);
	win = newwin(maxWinXY.y, maxWinXY.x, 2, 0); // make a new window
	keypad(win, TRUE);

	/* clear screen */
	for (int y = 0; y < maxWinXY.y; ++y)
	{
		for (int x = 0; x < maxWinXY.x; ++x)
		{
			wattron(win, COLOR_PAIR(0)); // black on black
			wattron(stdscr, COLOR_PAIR(0)); // black on black
			if(y < 3)
				mvwaddch(stdscr, y, x, BLANK); // stdscr is only 2x24
			mvwaddch(win, y, x, BLANK);
			wattroff(win, COLOR_PAIR(0));
			wattroff(stdscr, COLOR_PAIR(0));
		}
	}
	wnoutrefresh(stdscr); // for status screen
	wnoutrefresh(win);    // for window
	doupdate();
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
        init_pair(i, i, COLOR_BLACK);
    }
}

void GameManager::placeObstacle(Obstacle &o, unsigned long &id) {
	Obstacles.insert(Obstacles.end(), std::pair<unsigned long,Obstacle>(id,o));
}

void GameManager::placeExplosion(unsigned long &id, Coord start) {
	Explosions.insert(Explosions.end(), std::pair<unsigned long,Explosion>(id,Explosion(this->win, 
											&gameboard, 
											start - Coord{0,1}, 
											maxWinXY, EXPLOSION, SPACE, id, 0)));
}

void GameManager::placeBullet(unsigned long &id) {
	Bullets.insert(Bullets.end(), std::pair<unsigned long,Bullet>(id,Bullet(this->win, 
											&gameboard, 
											theShip.getFront()+Coord{1, 0}, 
											maxWinXY, BULLET, curr_theme, id, 0)));
}

void GameManager::placeShip() {
	theShip.draw();
}

void GameManager::setScreenSize() {
    /* flexible screen size; doesn't play well with 2-player games */
	// struct winsize w;
	// ioctl(0, TIOCGWINSZ, &w);
    // maxWinXY.y = w.ws_row-2; // save top two lines for user feedback
    // maxWinXY.x = w.ws_col;

    /* fixed screen size (78x24) */
    maxWinXY.y = MAX_Y-STATUS_SIZE; // save top two lines for user feedback
    maxWinXY.x = MAX_X;
}


