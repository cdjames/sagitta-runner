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
	initParticles();
}

Object::Object() {}
Object::~Object() {}

void Object::testgameboard() {
	// std::cout << (*gameboard)[start.y][start.x].id << std::endl;
	(*gameboard)[start.y][start.x].id = 2;
}

Particle Object::detectCollision(Particle p) {}

void Object::initParticles() {
	/* do a ship for practice */
	height = 3;
	width = 5;
	type = {SHIP, 1};
	Particle dummyP = { start, BLANK, 7, type, NOHIT }; // color 7 is white
	particles = vector< vector<Particle> >(height, vector<Particle>(width, dummyP));
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			particles[h][w].coords.x = start.x + w;
			particles[h][w].coords.y = start.y + h;
		}
	}
	particles[0][1].symbol = '\\';
	particles[0][1].color = 1; //red
	particles[0][2].symbol = '\\';
	particles[0][2].color = 1; //red
	particles[1][0].symbol = '}';
	particles[1][1].symbol = '=';
	particles[1][2].symbol = 'x';
	particles[1][2].color = 1;
	particles[1][3].symbol = '=';
	particles[1][4].symbol = '>';
	particles[2][1].symbol = '/';
	particles[2][1].color = 1; //red
	particles[2][2].symbol = '/';
	particles[2][2].color = 1; //red
} // may be virtual in the end

void Object::draw() {
	// save color?
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			// change color
			attron(COLOR_PAIR(particles[h][w].color));
			// add character
			mvwaddch(win, particles[h][w].coords.x, particles[h][w].coords.x, particles[h][w].symbol);
		}
	}
	// restore color?
}
void Object::erase() {}
Particle Object::move() {}
// virtual void setType() = 0;
void Object::setTrajectory(Coord tr) {}