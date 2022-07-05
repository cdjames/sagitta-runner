/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <curses.h>
#include "ObjectBlueprints.hpp"
#include "cj_random.hpp"
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
	Coord gbMax; // maximum indexes for gameboard
	Coord trajectory; // amount in x and y to adjust in each direction
	unsigned short front;
	unsigned short width, height; // for computing top, left, right, bottom values
	int topy, bottomy, leftx, rightx;
	short numParticles; // how many particles actually make up the object
	short theme; // the theme of the object
	ParticleInfo info; // info about the object meant for the gameboard
	vector<Particle> particles; // the actual particles that make up the object
	vector<Particle> prevParticles; // place for storing particles
	vector<ParticleCore> blueprint;
	ObjectType enemy;
	int y_and_buffer,
		x_and_buffer,
		color;
	bool no_color;

	virtual bool detectCollision(Particle &p, ParticleInfo &pi);

	/*********************************************************************
	** Description: initParticles()
	** creates the particles that make up the object
	** may become virtual depending on implementation
	*********************************************************************/
	void initParticles();

	/*********************************************************************
	** Description: _drawParticle()
	** Change color to color of particle, add the particle to the screen and
	** its ParticleInfo to the gameboard
	*********************************************************************/
	void _drawParticle(Particle &p, ParticleInfo pi);

	/*********************************************************************
	** Description: _eraseParticle()
	** Change the particle symbol to ' ' and send particle and blank info to 
	** _drawParticle()
	*********************************************************************/
	void _eraseParticle(Particle &p);

	bool _inBounds(Coord nc);
	
public:
	int points, // points earned for destroying
		penalty; // points lost for letting pass

	/*********************************************************************
	** Description: Object constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme, unsigned long id, int seed);
	Object(); // unused
	~Object(); // unused currently

	Coord getFront();
	unsigned long getId();
	/*********************************************************************
	** Description: draw()
	** Place the object on the window and gameboard
	*********************************************************************/
	void draw();

	/*********************************************************************
	** Description: erase()
	** call _eraseParticle on each particle in this->particles
	*********************************************************************/
	void erase();

	/*********************************************************************
	** Description: clearObject()
	** call erase(); call vector.clear() on particles, resulting in a 
	** vector of size 0
	*********************************************************************/
	void clearObject();

	/*********************************************************************
	** Description: move()
	** Parameter: Coord tr = trajectory for the movement. I.e. -1, -1 means
	** move diagonally up.
	**
	** Sets trajectory of object
	** Erases old particle, draws new one, updating particle coords.
	** Recomputes ship boundaries (topy, topx, etc.)
	** Detects collisions
	**
	** Returns: Particle with collided set to EDGE if edge is encountered;
				Partice with collided set to GAMEOVER if obstacle is encountered;
				Particle with collided set to HIT if bullet hits obstacle
	*********************************************************************/
	virtual Particle move(Coord tr);
	Particle dftMove();

	// virtual void setType() = 0;

	/*********************************************************************
	** Description: setTrajectory()
	** Parameter: Coord tr = trajectory for the object. See move()
	*********************************************************************/
	void setTrajectory(Coord tr);
	// void setThemeBP(vector< vector<int> > &bp);

	void setEnemy(ObjectType enemy);
};

#endif
