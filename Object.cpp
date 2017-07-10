/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Base class for objects such as the ship, obstacles, bullets, explosions
*********************************************************************/

#include "Object.hpp"

Object::Object(WINDOW * win, vector< vector<ParticleInfo> > * gameboard, Coord start, Coord max) {
	this->win = win;
	this->gameboard = gameboard;
	this->start = start;
	this->max = max;
}

Object::Object() {}
Object::~Object() {}

void Object::testgameboard() {
	// std::cout << (*gameboard)[start.y][start.x].id << std::endl;
	(*gameboard)[start.y][start.x].id = 2;
}