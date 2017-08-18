/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, bullets, bullets, explosions
*********************************************************************/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "Object.hpp"

using std::vector;

class Bullet : public Object
{
protected:
	
	
public:
	/*********************************************************************
	** Description: Bullet constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Bullet(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme, unsigned long id, int seed);
	Bullet(); // unused
	~Bullet(); // unused currently

};

#endif