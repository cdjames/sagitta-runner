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
				ThemeType theme, unsigned long id) 
{
	this->win = win;
	this->gameboard = gameboard;
	this->start = start;
	this->max = max;
	this->gbMax = Coord {max.x + (DEF_BUFFER*2), max.y + (DEF_BUFFER*2)};
	trajectory = {0, 0};
	this->theme = theme;
	info = {type, id};
	int numbps = OBJ_BLPRNTS[type][theme].size();
	blueprint = OBJ_BLPRNTS[type][theme][rand()%numbps];
	enemy = OBSTACLE;
	initParticles();
	setTrajectory(Coord {-1, 0}); // by default move left (for obstacles)
}

Object::Object() {}
Object::~Object() {}

Coord Object::getFront() {
	return particles[front].core.coords;
}

unsigned long Object::getId() {
	return this->info.id;
}

bool Object::detectCollision(Particle &p, ParticleInfo &pi) {
	// mvprintw(0, 70, "type=%d", pi.type);
	if(pi.type == enemy) {
		p.info = pi; // send object info back
		p.collided = GAMEOVER; // set collision info and send back
		// std::cout << "detected collision" << std::cout;
		// mvprintw(0, 70, "type=%d", p.info.type);
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
	points = MAX_OBS_POINTS - (width+height);
	penalty = height;
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
	front = blueprint[0].color;
	// std::cout << "object is type " << (int)info.type << " and id " << (int)info.id << std::endl;
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
	unsigned short onScreen = 0; // incremented if any particle in object is drawn
	/* make sure you have info for your object */
	// mvprintw(2, 90, "gbMax=%d,%d", gbMax.x,  gbMax.y);
	// mvprintw(3, 90, "gb_info coords=%d,%d", particles[0].core.coords.x+DEF_BUFFER,  particles[0].core.coords.y+DEF_BUFFER);
	Particle r_particle = DUMMY_PARTICLE;

	if(!particles.size())
		return r_particle; // get out, you have no object

	ParticleInfo gb_info;
	Coord new_coords;
	setTrajectory(tr);

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
		// printw("particles[i].core.coords=%d,%d", particles[i].core.coords.x,  particles[i].core.coords.y);
		new_coords = particles[i].core.coords + trajectory;
		if(info.type == BULLET)
		mvprintw(0, 100, " ");
		// printw("new_coords.coords=%d,%d", new_coords.x,  new_coords.y);
		
		/* check to see if we're still on the screen */
		if (_inBounds(new_coords)) {
			/* we're still on the screen, so increment onScreen and handle movement */
			onScreen++;

			/* get info about particle at new location on gameboard */
			gb_info = (*gameboard)[new_coords.y+DEF_BUFFER][new_coords.x+DEF_BUFFER];
			

			/* check gameboard at that location; if obstacle is hit, 
			 add the ParticleInfo to the return particle */
			if(detectCollision(r_particle, gb_info)) {
				done = true; // get out of loop, send back r_particle with collision
				r_particle.core.coords = new_coords; // will be used to start explosion
			} else {
				// erase old particle
				_eraseParticle(prevParticles[i]);

				/* draw new one 
					If none are drawn during the whole loop, onScreen flag will be zero */
				particles[i].core.coords += trajectory;
				_drawParticle(particles[i], info);

				// set collided type
				r_particle.collided = ALIVE;
			}
		}
		/* else object is not drawn because it has gone past the screen */
		else {
			/* but still need to update coords and erase old particle */
			_eraseParticle(prevParticles[i]);
			particles[i].core.coords += trajectory;
		}

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

	if(!onScreen) {
		r_particle.collided = DESTROY;
	} else {
		/* if we're still on the screen, recompute boundaries of ship */
		topy += tr.y;
		bottomy += tr.y;
		leftx += tr.x;
		rightx += tr.x;
	}

	return r_particle;
}

Particle Object::dftMove() {
	return move(trajectory);
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
	(*gameboard)[y+DEF_BUFFER][x+DEF_BUFFER] = pi;
}

/*********************************************************************
** Description: _checkBounds()
** Look at 
*********************************************************************/
bool Object::_inBounds(Coord nc) {
	if(nc.y >= 0 &&
		nc.y < max.y &&
		nc.x >= 0 &&
		nc.x < max.x)
		return true;
	else
		return false;
}

// virtual void setType() = 0;
void Object::setTrajectory(Coord tr) {
	this->trajectory = tr;

}

void Object::setEnemy(ObjectType enemy) {
	this->enemy = enemy;
}