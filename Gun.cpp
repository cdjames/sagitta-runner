#include "Gun.hpp"
#include <iostream>
#include <curses.h>

Gun::Gun(): Cell() {}

Gun::Gun(int y, int x, int size): Cell (y, x, size)
{
	initArrays();
}

Gun::~Gun() {}

/*********************************************************************
** Description: 
** Sets up arrays
*********************************************************************/
void Gun::initArrays() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{		// build the blocks and spaceships
			if (   (x == 0 && i == 4) // left block
				|| (x == 0 && i == 5) // 
				|| (x == 1 && i == 4) // 
				|| (x == 1 && i == 5) //
				|| (x == 34 && i == 2) // right block
				|| (x == 34 && i == 3) // 
				|| (x == 35 && i == 2) // 
				|| (x == 35 && i == 3) //
				|| (x == 10 && i == 4) // left ship
				|| (x == 10 && i == 5) // 
				|| (x == 10 && i == 6) // 
				|| (x == 11 && i == 3) // 
				|| (x == 11 && i == 7) // 
				|| (x == 12 && i == 2) // 
				|| (x == 12 && i == 8) // 
				|| (x == 13 && i == 2) // 
				|| (x == 13 && i == 8) // 
				|| (x == 14 && i == 5) // 
				|| (x == 15 && i == 3) // 
				|| (x == 15 && i == 7) // 
				|| (x == 16 && i == 4) // 
				|| (x == 16 && i == 5) // 
				|| (x == 16 && i == 6) // 
				|| (x == 17 && i == 5) // 
				|| (x == 20 && i == 2) // right ship
				|| (x == 20 && i == 3) // 
				|| (x == 20 && i == 4) // 
				|| (x == 21 && i == 2) // 
				|| (x == 21 && i == 3) // 
				|| (x == 21 && i == 4) // 
				|| (x == 22 && i == 1) // 
				|| (x == 22 && i == 5) // 
				|| (x == 24 && i == 0) // 
				|| (x == 24 && i == 1) // 
				|| (x == 24 && i == 5) // 
				|| (x == 24 && i == 6) // 
				)
			{
				currentCell[i][x] = 1;
			}
			else
				currentCell[i][x] = 0;

			// all newCells get 0
			newCell[i][x] = 0;
		}
	}
}

/*********************************************************************
** Description: 
** Iterate through array and put characters on screen
*********************************************************************/
bool Gun::drawCells() 
{
	char ch = '-';
	for (int i = 0; i < SIZE; i++)
	{
		// clear the previous screen
		for (int x = 0; x < SIZE; x++)
			mvwaddch(win, i, x, ch);
	}
	wrefresh(win); // update the window to clear
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{	
			if(currentCell[i][x] == 1)
				ch = '+';
			else
				ch = '-';
			if(i != SIZE-1 && x != SIZE-1)
				mvwaddch(win, (i + startY), (x + startX), ch); // put character on window		
		}
	}

	wrefresh(win); // update the window

	Cell::countNeighbors(); // figure out next generation

	updateCycle(); // copy new cells into 1st generation; clear new array
}

/*********************************************************************
** Description: 
** copy the new cell into the main cell and clear the new cell
*********************************************************************/
void Gun::updateCycle() 
{
	Cell::clearArray(currentCell);

	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
			currentCell[i][x] = newCell[i][x];				
	}

	Cell::clearArray(newCell);
}