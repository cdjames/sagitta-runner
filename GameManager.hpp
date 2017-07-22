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
	unsigned short fr_counter, fr_factor;
	Ship theShip;
	Object testO;
	int input;
	Particle shipStatus;
	bool gameover;

	std::map<unsigned long,Object> Obstacles;
	std::map<unsigned long,Object> Bullets;
	std::map<unsigned long,Object> Explosions;

	unsigned long obstacleId,
					bulletId,
					explosionId;

	void initWindow();
	void initGameboard();
	void initColors();
	void placeShip();
	void placeObject(Object &o, unsigned long &id);
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