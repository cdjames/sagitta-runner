/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
** see header file for more info
*********************************************************************/

#include "Explosion.hpp"

Explosion::Explosion(WINDOW * win, 
				vector< vector<ParticleInfo> > * gameboard, 
				Coord start, Coord max, 
				ObjectType type, 
				ThemeType theme, unsigned long id, int seed) : Object(win, gameboard, start, max, type, theme, id, seed)
{
	info = {type, id};
	animations_left = 6;
}

Explosion::Explosion() {}
Explosion::~Explosion() {}

unsigned short Explosion::animate() {
	prevParticles = particles;
	if(animations_left%2 == 0) {
		blueprint = OBJ_BLPRNTS[info.type][theme][0];
	} else {
		blueprint = OBJ_BLPRNTS[info.type][theme][1];
	}

	particles.clear();
	initParticles();

	for (int i = 0; i < numParticles; i++)
	{
		// particles[i].core.color = particles[cj_rand()%(numParticles-1)].core.color;
		// particles[i].core.color = particles[i].core.color;
	
		_eraseParticle(prevParticles[i]);
		_drawParticle(particles[i], info);
	}

	return --animations_left;
}