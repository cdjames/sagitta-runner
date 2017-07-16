/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: The managing class of the infinite runner
*********************************************************************/

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <curses.h>
#include <vector>
#include "MenuManager.hpp"
#include "SagittaTypes.hpp"
#include "Object.hpp"
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

	Object testO;
	int input;
	Particle shipStatus;

	void initWindow();
	void initGameboard();
	void initColors();
	void placeShip();
	void moveShip();
	void createObstacles();
	void moveObstacles();
	void doExplosions();
	void fireBullet();
	void moveBullets();
	void gameOver();
	void setScreenSize();
	int difficulty;	
public:
	GameManager(WINDOW * win);
	~GameManager();
	void run();
	void updateSettings(MenuManager);
};

#endif
