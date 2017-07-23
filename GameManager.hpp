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
#include "SagittaTypes.hpp"
#include "Ship.hpp" // includes Object
#include "Obstacle.hpp" // includes Object
#include "Bullet.hpp" // includes Object
#include "Explosion.hpp" // includes Object
#include <sys/ioctl.h> // for winsize
#include <iostream>

using std::vector;

class GameManager
{
protected:
	WINDOW * win;
	vector< vector<ParticleInfo> > gameboard;

	Coord maxWinXY,
		  maxGBWinXY;
	short 	baseRefresh,
			obstacleRefreshCounter,
			obstacleRefreshFactor,
			numObstaclesCreateOnPass;
	unsigned short fr_counter, fr_factor,
					exp_fr_counter, exp_fr_factor;
	Ship theShip;
	Obstacle testO;
	Obstacle testO2;
	Bullet testBullet;
	Explosion testExplosion;
	int input;
	Particle shipStatus;
	bool gameover;

	std::map<unsigned long,Obstacle> Obstacles;
	std::map<unsigned long,Bullet> Bullets;
	std::map<unsigned long,Explosion> Explosions;

	unsigned long obstacleId,
					bulletId,
					explosionId;

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
	
public:
	GameManager(WINDOW * win);
	~GameManager();
	short run();
};

#endif