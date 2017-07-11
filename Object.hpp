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
	Coord start; // starting coordinates for the object
	Coord max; // coordinates of the max drawing area of the window
	Coord trajectory;
	short width, height;
	ParticleInfo type;
	vector< vector<Particle> > particles;
	vector< vector<Particle> > prevParticles;

	Particle detectCollision(Particle p);

	/*********************************************************************
	** Description: 
	** creates the particles that make up the object
	*********************************************************************/
	void initParticles();
	
public:
	Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max);
	Object();
	~Object();
	void testgameboard();
	void draw();
	void erase();
	Particle move();
	// virtual void setType() = 0;
	void setTrajectory(Coord tr);
};

#endif