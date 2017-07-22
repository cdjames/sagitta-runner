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
				ThemeType theme) : Object(win, gameboard, start, max, type, theme)
{
}

Ship::Ship() {}
Ship::~Ship() {}