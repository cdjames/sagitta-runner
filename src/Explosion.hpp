/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, bullets, bullets, explosions
*********************************************************************/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Object.hpp"

using std::vector;

class Explosion : public Object
{
protected:
	unsigned short animations_left; //
	
public:
	/*********************************************************************
	** Description: Explosion constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Explosion(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme, unsigned long id, int seed);
	Explosion(); // unused
	~Explosion(); // unused currently

	/*********************************************************************
	** Description: animate()
	** instead of moving, explosions animate
	** the idea is to alternate colors and "states" so it looks like the
	** explosion is rotating.
	**
	** returns a number signifying how many animations it has left
	*********************************************************************/
	unsigned short animate();
};

#endif