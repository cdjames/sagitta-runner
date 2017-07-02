#include "Oscillator.hpp"
// #include "Cell.hpp"
#include <iostream>
#include <curses.h>

Oscillator::Oscillator(): Drawer() {}

Oscillator::Oscillator(int y, int x, int size): Drawer (y, x, size)
{
	initArrays();
}

Oscillator::~Oscillator() {}

/*********************************************************************
** Description: 
** Sets up arrays
*********************************************************************/
void Oscillator::initArrays() 
{
	for (int i = 0; i < WINY; i++)
	{
		for (int x = 0; x < WINX; x++)
		{
			if (x == WINX-1)
				currentCell[i][x] = 1;
			// else if (x == user_coords.x && i == user_coords.y)
			// 	currentCell[i][x] = 2;
			else
				currentCell[i][x] = 0;

			newCell[i][x] = 0;
		}
	}
}

/*********************************************************************
** Description: 
** Iterate through array and put characters on screen
*********************************************************************/
void Oscillator::drawCells() 
{
	char ch;
	for (int i = 0; i < WINY; i++)
	{
		for (int x = 0; x < WINX; x++)
		{
			if(currentCell[i][x] == 0) {
				ch = BLANK;
			}
			// else if(currentCell[i][x] == 2) {
			// 	ch = SHIP;
			// }
			else {
				ch = OBSTACLE;
			}

			mvwaddch(win, i+startY, x+startX, ch); // put character on window		
		}
	}

	wrefresh(win); // update the window

	// Drawer::countNeighbors(); // figure out next generation

	// updateCycle(); // copy new cells into 1st generation; clear new array
}

/*********************************************************************
** Description: 
** Move whatever is on the right to the left
*********************************************************************/
void Oscillator::moveScreenLeft() 
{
	char ch;
	for (int y = 0; y < WINY; y++)
	{
		for (int x = 0; x < WINX; x++)
		{
			// if at window edge, make some obstacles
			if(x != WINX-1) {
				currentCell[y][x] = currentCell[y][x+1];
			}
			// otherwise just draw a column of - signs in the last column
			else
				currentCell[y][x] = 0;

			switch(currentCell[y][x]) {
				case 0:
				ch = BLANK;
				break;
				case 1:
				ch = OBSTACLE;
				break;
			}
			mvwaddch(win, y, x, ch); // put character on window		
		}
	}

	wrefresh(win); // update the window

}

/*********************************************************************
** Description: 
** copy the new cell into the main cell and clear the new cell
*********************************************************************/
void Oscillator::updateCycle() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			currentCell[i][x] = newCell[i][x];
		}
	}
			
	Drawer::clearArray(newCell);
}