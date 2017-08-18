/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
** see header file for more info
*********************************************************************/

#include "Ship.hpp"

Ship::Ship(WINDOW * win, 
				vector< vector<ParticleInfo> > * gameboard, 
				Coord start, Coord max, 
				ObjectType type, 
				ThemeType theme, unsigned long id, int seed) : Object(win, gameboard, start, max, type, theme, id, seed)
{
	info = {type, 1};
}

Ship::Ship() : Object() {}
Ship::~Ship() {}

Particle Ship::move(Coord tr) {
	/* make sure you have info for your object */
	if(!particles.size())
		initParticles(); // create a new object from whatever template you have
		// return DUMMY_PARTICLE; // get out, you have no object

	Particle r_particle = DUMMY_PARTICLE;
	ParticleInfo gb_info;
	ParticleInfo cur_gb_info;
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
		// int m = 1;
		while(!done)
		{	
			/* look for collisions and return result of collision */
			// printw("particles[i].core.coords=%d,%d", particles[i].core.coords.x,  particles[i].core.coords.y);
			new_coords = particles[i].core.coords + trajectory;
			// printw("new_coords.coords=%d,%d", new_coords.x,  new_coords.y);
			/* check gameboard at that location; if obstacle is hit, 
			 add the ParticleInfo to the return particle */
			// cur_gb_info = (*gameboard)[particles[i].core.coords.y+DEF_BUFFER][particles[i].core.coords.x+DEF_BUFFER];
			gb_info = (*gameboard)[new_coords.y+DEF_BUFFER][new_coords.x+DEF_BUFFER];
			// mvprintw(m++, 100, "gbinfo type=%d ", cur_gb_info.type);

			if(detectCollision(r_particle, gb_info)) {
				done = true; // get out of loop, send back r_particle with collision
				r_particle.core.coords = new_coords; // will be used to start explosion
			} else {
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