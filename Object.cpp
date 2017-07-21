/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
** see header file for more info
*********************************************************************/

#include "Object.hpp"

Object::Object(WINDOW * win, 
				vector< vector<ParticleInfo> > * gameboard, 
				Coord start, Coord max, 
				ObjectType type, 
				ThemeType theme) 
{
	this->win = win;
	this->gameboard = gameboard;
	this->start = start;
	this->max = max;
	trajectory = {0, 0};
	id = 1;
	info = {type, id};
	this->theme = theme;
	blueprint = OBJ_BLPRNTS[type][theme][0];
	enemy = OBSTACLE;
	initParticles();
}

Object::Object() {}
Object::~Object() {}

bool Object::detectCollision(Particle &p, ParticleInfo &pi) {
	if(pi.type == enemy) {
		p.info = pi; // send object info back
		p.collided = GAMEOVER; // set collision info and send back
		return true;
	} else {
		return false;
	}
		
}

void Object::initParticles() {
	/* make a ship for practice */
	numParticles = blueprint.size()-1;
	height = blueprint[0].coords.x;
	width = blueprint[0].coords.y;
	topy = start.y;
	bottomy = start.y + height;
	leftx = start.x;
	rightx = start.x + width;

	for (short i = 1; i <= numParticles; ++i)
	{
		particles.push_back( 
			Particle { 
				blueprint[i],
				info, 
				NOHIT 
			} 
		);
		particles[i-1].core.coords += start; // adjust by the starting coordinates
	}
} // may be virtual in the end

void Object::draw() {
	
	for (int i = 0; i < numParticles; i++)
	{
		_drawParticle(particles[i], info);
	}
}

void Object::clearObject() {
	/* erase from the screen and gameboard */
	erase();
	/* clear all of the particles */
	particles.clear();
}

void Object::erase() {
	/* draw blanks where ship used to be */
	for (int i = 0; i < numParticles; i++)
	{
		_eraseParticle(particles[i]);
	}
	/* clear*/
}

void Object::_eraseParticle(Particle &p) {
	ParticleInfo blankInfo = { NONE, 0 };
	p.core.symbol = ' ';
	_drawParticle(p, blankInfo);
}

Particle Object::move(Coord tr) {
	/* make sure you have info for your object */
	if(!particles.size())
		initParticles(); // create a new object from whatever template you have
		// return DUMMY_PARTICLE; // get out, you have no object

	Particle r_particle = DUMMY_PARTICLE;
	ParticleInfo gb_info;
	Coord new_coords;
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
			/* look for collisions and return result of collision */
			// printw("particles[i].core.coords=%d,%d", particles[i].core.coords.x,  particles[i].core.coords.y);
			new_coords = particles[i].core.coords + trajectory;
			// printw("new_coords.coords=%d,%d", new_coords.x,  new_coords.y);
			/* check gameboard at that location; if obstacle is hit, 
			 add the ParticleInfo to the return particle */
			gb_info = (*gameboard)[new_coords.y+DEF_BUFFER][new_coords.x];
			// printw("gb_info coords=%d,%d", new_coords.x,  new_coords.y+DEF_BUFFER);

			if(detectCollision(r_particle, gb_info)) {
				done = true; // get out of loop, send back r_particle with collision
				r_particle.core.coords = new_coords; // will be used to start explosion
			} else {
				// erase old particle
				// prevParticles[i].core.symbol = ' ';
				// _drawParticle(prevParticles[i], blankInfo);
				_eraseParticle(prevParticles[i]);

				// draw new one
				particles[i].core.coords += trajectory;
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
	x = p.core.coords.x;
	y = p.core.coords.y;
	c = p.core.color;
	// change color
	wattron(win, COLOR_PAIR(c));
	// add character
	mvwaddch(win, y, x, p.core.symbol);
	// turn color off
	wattroff(win, COLOR_PAIR(c));
	// update gameboard
	(*gameboard)[y+DEF_BUFFER][x] = pi;
}

// virtual void setType() = 0;
void Object::setTrajectory(Coord tr) {
	this->trajectory = tr;
	mvprintw(0, 100, " %d, %d  ", tr.x, tr.y);
}

void Object::setEnemy(ObjectType enemy) {
	this->enemy = enemy;
}