/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <curses.h>
#include "ObjectBlueprints.hpp"
#include <sys/ioctl.h> // for winsize
#include <iostream>
#include <algorithm>

using std::vector;

class Object
{
protected:
	WINDOW * win; // inherited from GameManager
	vector< vector<ParticleInfo> > * gameboard; // inherited; max.x+DEF_BUFFER x max.y+(DEF_BUFFER*2)
	Coord start; // starting coordinates for the object
	Coord max; // coordinates of the max drawing area of the window
	Coord trajectory; // amount in x and y to adjust in each direction
	unsigned short width, height; // for computing top, left, right, bottom values
	int topy, bottomy, leftx, rightx;
	short numParticles; // how many particles actually make up the object
	unsigned long id; // id of object
	ParticleInfo info; // info about the object meant for the gameboard
	vector<Particle> particles; // the actual particles that make up the object
	vector<Particle> prevParticles; // place for storing particles

	Particle detectCollision(Particle p);

	/*********************************************************************
	** Description: initParticles()
	** creates the particles that make up the object
	** may become virtual depending on implementation
	*********************************************************************/
	void initParticles();
	void _drawParticle(Particle &p, ParticleInfo pi);
	
public:
	/*********************************************************************
	** Description: Object constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max);
	Object(); // unused
	~Object(); // unused currently

	/*********************************************************************
	** Description: draw()
	** Place the object on the window and gameboard
	*********************************************************************/
	void draw();
	void erase();
	Particle move(Coord tr);
	// virtual void setType() = 0;
	void setTrajectory(Coord tr);
	// void setThemeBP(vector< vector<int> > &bp);
};

#endif