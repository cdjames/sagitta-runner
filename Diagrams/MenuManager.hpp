#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <curses.h>
#include <vector>
#include "SagittaTypes.hpp"
#include <sys/ioctl.h> // for winsize
#include <iostream>
#include "Object.hpp"

using std::vector;

class MenuManager {
private:
	Object testO;
	int input;
	int yCoord;
	int xCoord;
	Coord maxWinXY,
		maxGBWinXY;
	WINDOW *win;
	vector< vector<ParticleInfo> > gameboard;

public:
	MenuManager(WINDOW *win);
	void initWindow();
	void initColors();
	void setScreenSize();
	int settingsScreen();
	void initMenu();
	int run();
	//void initGameboard();
};

#endif