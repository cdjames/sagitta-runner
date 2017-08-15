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
	setTrajectory(Coord{1,0});
}

Bullet::Bullet() {}
Bullet::~Bullet() {}

// virtual bool Bullet::detectCollision(Particle &p, ParticleInfo &pi) {
// 	// mvprintw(0, 70, "type=%d", pi.type);
// 	if(pi.type == enemy) {
// 		p.info = pi; // send object info back
// 		p.collided = GAMEOVER; // set collision info and send back
// 		// std::cout << "detected collision" << std::cout;
// 		// mvprintw(0, 70, "type=%d", p.info.type);
// 		return true;
// 	} else {
// 		return false;
// 	}
		
// }