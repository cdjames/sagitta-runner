/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
** see header file for more info
*********************************************************************/

#include "Bullet.hpp"

Bullet::Bullet(WINDOW * win, 
				vector< vector<ParticleInfo> > * gameboard, 
				Coord start, Coord max, 
				ObjectType type, 
				ThemeType theme, unsigned long id) : Object(win, gameboard, start, max, type, theme, id)
{
	info = {type, id};
}

Bullet::Bullet() {}
Bullet::~Bullet() {}