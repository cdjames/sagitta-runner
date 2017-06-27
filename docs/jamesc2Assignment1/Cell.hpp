/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A base class from which to build Conway cells
*********************************************************************/

#ifndef CELL_HPP
#define CELL_HPP

#include <curses.h>
class Cell
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
	Cell();
	Cell(int x, int y, int size);
	~Cell();
	void initWindow(int y, int x);
};

#endif