/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: The managing class of the infinite runner
*********************************************************************/

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <curses.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <limits>
#include <chrono>
#include "MenuManager.hpp"
// #include "SagittaTypes.hpp"
#include "Ship.hpp" // includes Object
#include "Obstacle.hpp" // includes Object
#include "Bullet.hpp" // includes Object
#include "Explosion.hpp" // includes Object
#include <sys/ioctl.h> // for winsize
#include <iostream>
#include <cstdlib> // rand
#include <ctime> // for seeding rand
#include <cmath>

using std::vector;
// using std::chrono;

class GameManager
{
protected:
	WINDOW * win;
	vector< vector<ParticleInfo> > gameboard;

	Coord maxWinXY,
		  maxGBWinXY;
	Obstacle rand_obstacle;

	std::unordered_map<unsigned long,Obstacle> Obstacles;
	std::map<unsigned long,Bullet> Bullets;
	std::map<unsigned long,Explosion> Explosions;

	std::unordered_map<unsigned long,Obstacle>::iterator obst_it;
	std::map<unsigned long,Bullet>::iterator bull_it;
	std::map<unsigned long,Explosion>::iterator exp_it;

	std::unordered_map<unsigned long,Obstacle>::iterator temp_obst_it;
	std::map<unsigned long,Bullet>::iterator temp_bull_it;
	std::map<unsigned long,Explosion>::iterator temp_exp_it;

	/* used in run() */
	short 	baseRefresh,
			obstacleRefreshCounter,
			obstacleRefreshFactor,
			numObstaclesCreateOnPass;
	unsigned short fr_counter, fr_factor,
					exp_fr_counter, exp_fr_factor,
					create_counter, create_factor,
					theme_counter,
					max_bullets;
	ThemeType curr_theme;
	unsigned long numObstaclesDestroyed;
	Ship theShip;
	int input;
	Particle shipStatus;
	bool gameover;
	unsigned short still_animating;
	Particle obstStatus;
	bool move_ship;
	bool makeExplosion;
	short gameStatus;
	Coord trajectory;
	Coord exp_coord;
	Coord ship_coord;
	int basequadsize;
	int quadsize;
	int prevquadsize;
	unsigned short temp_theme; 
	unsigned int num_theme_loops;
	unsigned int num_time_loops;
	unsigned long obstacleId,
					bulletId,
					explosionId;
	int difficulty;	
	time_t start_time,
		   target_time,
		   time_now;
	// int max_obs_points;
	int score;

	void initWindow();
	void initGameboard();
	void initColors();
	void placeShip();
	void placeObstacle(Obstacle &o, unsigned long &id);
	void placeBullet(unsigned long &id);
	void placeExplosion(unsigned long &id, Coord start);
	void moveShip();
	void createObstacles();
	void moveObstacles();
	void doExplosions();
	void fireBullet();
	void moveBullets();
	void gameOver();
	void setScreenSize();
	void _gameLoop(vector<double> * timing_info);
	short _gameOver(int * final_score);

public:
	GameManager(WINDOW * win);
	~GameManager();
	short run(int * final_score, vector<double> * timing_info);
	void updateSettings(MenuManager &MM);
};

#endif
