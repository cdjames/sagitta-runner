/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
** see header file for more info
*********************************************************************/

#include "Obstacle.hpp"

Obstacle::Obstacle(WINDOW * win, 
				vector< vector<ParticleInfo> > * gameboard, 
				Coord start, Coord max, 
				ObjectType type, 
				ThemeType theme) : Object(win, gameboard, start, max, type, theme)
{
}

Obstacle::Obstacle() {}
Obstacle::~Obstacle() {}