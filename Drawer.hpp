/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A base class from which to build Conway drawers
*********************************************************************/

#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <curses.h>

const int winX = 80;
const int winY = 30;
const int DEF_TIMEOUT = 50;
const int DEF_MULTIPLIER = 8;
const char ship = '>';
const char blank = ' ';
const char obstacle = '+';

struct Coords
{
	int x, y;
};

typedef struct Coords Coords;

class Drawer
{
protected:
	int SIZE;
	int startX;
	int startY;
	int rowSize;
	int colSize;
	int** currentCell;
	int** newCell;
	int xMove;
	int yMove;
	int currentState;
	int gTimeout;
	int input;
	WINDOW * win;
	Coords user_coords;
	Coords prev_user_coords;
	int fr_multiplier;
	int fr_counter;


	void clearArray(int** array);
	void countNeighbors();
	
public:
	Drawer();
	Drawer(int x, int y, int size);
	~Drawer();
	void initWindow(int y, int x);
	void startMovement();
	virtual void moveScreenLeft() = 0;
	virtual void drawCells() = 0;
};

#endif