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
				ThemeType theme, unsigned long id, int seed) : Object(win, gameboard, start, max, type, theme, id, seed)
{
	enemy = SHIP;
	enemy2 = BULLET;
}

Obstacle::Obstacle() {}
Obstacle::~Obstacle() {}
void Obstacle::setEnemy2(ObjectType enemy2) {
	this->enemy2 = enemy2;
}

bool Obstacle::detectCollision(Particle &p, ParticleInfo &pi) {
	if(pi.type == enemy) {
		p.info = pi; // send object info back
		p.collided = GAMEOVER; // set collision info and send back

		return true;
	} else if (pi.type == enemy2) { 
		p.info = pi;
		p.collided = HIT; // hit by a bullet
	} else {
		return false;
	}	
}