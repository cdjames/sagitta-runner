/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#ifndef SHIP_HPP
#define SHIP_HPP

#include "Object.hpp"

using std::vector;

class Ship : public Object
{
protected:
	
	
public:
	/*********************************************************************
	** Description: Ship constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Ship(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme);
	Ship(); // unused
	~Ship(); // unused currently

};

#endif