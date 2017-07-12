/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#include "Object.hpp"

Object::Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max) {
	this->win = win;
	this->gameboard = gameboard;
	this->start = start;
	this->max = max;
	initParticles();
}

Object::Object() {}
Object::~Object() {}

void Object::testgameboard() {
	// std::cout << (*gameboard)[start.y][start.x].id << std::endl;
	(*gameboard)[start.y][start.x].id = 2;
}

Particle Object::detectCollision(Particle p) {}

void Object::initParticles() {
	/* do a ship for practice */
	id = 1;
	numParticles = 9;
	height = 3;
	width = 5;
	info = {SHIP, id};
	// Particle dummyP = { start, BLANK, 7, type, NOHIT }; // color 7 is white

	particles.push_back( Particle { Coord{start.x+1, start.y+0}, '\\', 1, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+2, start.y+0}, '\\', 1, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+0, start.y+1}, '}', 7, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+1, start.y+1}, '=', 7, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+2, start.y+1}, 'x', 1, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+3, start.y+1}, '=', 7, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+4, start.y+1}, '>', 7, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+1, start.y+2}, '/', 1, info, NOHIT } );
	particles.push_back( Particle { Coord{start.x+2, start.y+2}, '/', 1, info, NOHIT } );

} // may be virtual in the end

void Object::draw() {
	int x, y, c;
	for (int i = 0; i < numParticles; i++)
	{
		// save some info for convenience
		x = particles[i].coords.x;
		y = particles[i].coords.y;
		c = particles[i].color;
		// change color
		wattron(win, COLOR_PAIR(c));
		// add character
		mvwaddch(win, y, x, particles[i].symbol);
		// turn color off
		wattroff(win, COLOR_PAIR(c));
		// update gameboard
		(*gameboard)[y+DEF_BUFFER][x] = info; // add DEF_BUFFER as actual window dimensions start here
	}
}
void Object::erase() {}
Particle Object::move() {}
// virtual void setType() = 0;
void Object::setTrajectory(Coord tr) {}