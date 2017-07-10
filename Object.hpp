/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <curses.h>
#include <vector>
#include "SagittaTypes.hpp"
#include <sys/ioctl.h> // for winsize
#include <iostream>

using std::vector;

class Object
{
protected:
	WINDOW * win;
	vector< vector<ParticleInfo> > * gameboard;
	Coord start;
	Coord max;
	
public:
	Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max);
	Object();
	~Object();
	void testgameboard();
};

#endif