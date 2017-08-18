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
	Ship(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max, ObjectType type, ThemeType theme, unsigned long id, int seed);
	Ship(); // unused
	~Ship(); // unused currently

	/*********************************************************************
	** Description: Ship::move() overrides Object::move() (see * for differences)
	** Parameter: Coord tr = trajectory for the movement. I.e. -1, -1 means
	** move diagonally up.
	**
	** Sets trajectory of object
	** Erases old particle, draws new one, updating particle coords.
	** Recomputes ship boundaries (topy, topx, etc.)
	** Detects collisions
	**
	** Returns: * Particle with collided set to EDGE if edge is encountered;
				Partice with collided set to GAMEOVER if obstacle is encountered;
				Particle with collided set to HIT if bullet hits obstacle
	*********************************************************************/
	virtual Particle move(Coord tr);


};

#endif