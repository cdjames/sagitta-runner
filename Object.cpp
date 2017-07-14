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
	trajectory = {0, 0};
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
	topy = start.y;
	bottomy = start.y + height;
	leftx = start.x;
	rightx = start.x + width;
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
	
	for (int i = 0; i < numParticles; i++)
	{
		// save some info for convenience
		// x = particles[i].coords.x;
		// y = particles[i].coords.y;
		// c = particles[i].color;
		// // change color
		// wattron(win, COLOR_PAIR(c));
		// // add character
		// mvwaddch(win, y, x, particles[i].symbol);
		// // turn color off
		// wattroff(win, COLOR_PAIR(c));
		// // update gameboard
		// (*gameboard)[y+DEF_BUFFER][x] = info; // add DEF_BUFFER as actual window dimensions start here
		_drawParticle(particles[i], info);
	}
}

void Object::erase() {}
Particle Object::move(Coord tr) {
	Particle r_particle = DUMMY_PARTICLE;
	setTrajectory(tr);
	/* look for collisions and return result of collision (or later 
		return "dummy" particle after the move) */
	/* if no collisions with other objects, check for boundaries */
	if( !(topy + tr.y < 0
	   || bottomy + tr.y > max.y 
	   || leftx + tr.x < 0
	   || rightx + tr.x > max.x) ) {
		// move if not against boundaries
		ParticleInfo blankInfo = { NONE, 0 };
		prevParticles = particles;

		/* need to start at first particle if moving left and up
			otherwise start at last particle */
		int i, psize, incdec;
		if (tr.y < 0 || tr.x < 0) { // moving left or up
			i = 0;
			psize = particles.size();
			incdec = 1;
		} else {
			i = particles.size()-1;
			psize = 0;
			incdec = -1;
		}
		bool done = false;
		/* loop, erasing previous particle and drawing new one in one pass */
		while(!done)
		{	
			// erase old particle
			prevParticles[i].symbol = ' ';
			_drawParticle(prevParticles[i], blankInfo);

			// draw new one
			particles[i].coords += trajectory;
			_drawParticle(particles[i], info);

			// increment/decrement and get out of loop
			i += incdec;
			if (tr.y < 0 || tr.x < 0) {
				if (i == psize)
					done = true;
			} else {
				if (i < psize)
					done = true;
			}
		}

		/* recompute boundaries of ship */
		topy += tr.y;
		bottomy += tr.y;
		leftx += tr.x;
		rightx += tr.x;
	} else {
		// hit an edge, so set the collision type in return particle
		r_particle.collided = EDGE;
	}

	return r_particle;
}

void Object::_drawParticle(Particle &p, ParticleInfo pi) {
	int x, y, c;
	// p->coords += this->trajectory;
	x = p.coords.x;
	y = p.coords.y;
	c = p.color;
	// change color
	wattron(win, COLOR_PAIR(c));
	// add character
	mvwaddch(win, y, x, p.symbol);
	// turn color off
	wattroff(win, COLOR_PAIR(c));
	// update gameboard
	(*gameboard)[y+DEF_BUFFER][x] = pi;
}
// virtual void setType() = 0;
void Object::setTrajectory(Coord tr) {
	this->trajectory = tr;
}