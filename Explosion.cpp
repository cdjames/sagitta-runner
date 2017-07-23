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
				ThemeType theme, unsigned long id) : Object(win, gameboard, start, max, type, theme, id)
{
	info = {type, id};
	animations_left = 10;
}

Explosion::Explosion() {}
Explosion::~Explosion() {}

unsigned short Explosion::animate() {
	prevParticles = particles;
	if(animations_left%2 == 0) {
		blueprint = OBJ_BLPRNTS[info.type][1][0];
	} else {
		blueprint = OBJ_BLPRNTS[info.type][0][0];
	}

	particles.clear();
	initParticles();

	for (int i = 0; i < numParticles; i++)
	{
		if(i < numParticles-1)
			particles[i].core.color = particles[i+1].core.color;
		else
			particles[i].core.color = particles[0].core.color;
				
		_eraseParticle(prevParticles[i]);
		_drawParticle(particles[i], info);
	}

	return --animations_left;
}