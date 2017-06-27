#include "Glider.hpp"
#include <iostream>
#include <curses.h>

Glider::Glider(): Cell() {}

Glider::Glider(int y, int x, int size): Cell (y, x, size)
{
	initArrays();
}

Glider::~Glider() {}

/*********************************************************************
** Description: 
** Sets up arrays
*********************************************************************/
void Glider::initArrays() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{		// build the spaceship
			if (   (i == 0 && x == 1) // 0100
				|| (i == 1 && x == 2) // 0010
				|| (i == 2 && x == 0) // 1110
				|| (i == 2 && x == 1) // 0000
				|| (i == 2 && x == 2)
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
bool Glider::drawCells() 
{
	char ch = '-';
	for (int i = 0; i < SIZE; i++)
	{
		// clear the previous cell area
		for (int x = 0; x < SIZE; x++)
			mvwaddch(win, (i + startY + yMove-1), (x + startX + xMove-1), ch);
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
				mvwaddch(win, (i + startY + yMove), (x + startX + xMove), ch); // put character on window		
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
void Glider::updateCycle() 
{
	bool moveX = false;
	bool moveY = false;
	Cell::clearArray(currentCell); // all zeroes

	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if(currentState % 2 == 0) // if 2 or 4, no movement
				currentCell[i][x] = newCell[i][x];
			else if(currentState == 1)
			{
				moveY = true;
				if(newCell[i][x] == 1)
					currentCell[i-1][x] = newCell[i][x];
			}
			else // current state is
			{
				moveX = true;
				if(newCell[i][x] == 1)
					currentCell[i][x-1] = newCell[i][x];
			}		
		}
	}

	/* move the object to the right */
	if(moveX)
		xMove++;
	/* move the object down */	
	else if(moveY)
		yMove++;

	/* determine next state iteration (between 1 and 4) */
	if(currentState < 4)
		currentState++;
	else
		currentState = 1;

	Cell::clearArray(newCell);; // all zeroes
}