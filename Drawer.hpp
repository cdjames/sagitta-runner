/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A base class from which to build Conway drawers
*********************************************************************/

#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <curses.h>
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
	WINDOW * win;

	void clearArray(int** array);
	void countNeighbors();
	
public:
	Drawer();
	Drawer(int x, int y, int size);
	~Drawer();
	void initWindow(int y, int x);
};

#endif