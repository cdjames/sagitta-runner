/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Object.hpp"

using std::vector;

class Obstacle : public Object
{
protected:
	
	
public:
	/*********************************************************************
	** Description: Obstacle constructor
	** Inherit win and gameboard from creating class. Passed a start coord 
	** for the object and max coord (dimensions of win)

	** calls initParticles()
	*********************************************************************/
	Obstacle(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme);
	Obstacle(); // unused
	~Obstacle(); // unused currently

};

#endif