#include "Oscillator.hpp"
// #include "Cell.hpp"
#include <iostream>
#include <curses.h>

Oscillator::Oscillator(): Cell() {}

Oscillator::Oscillator(int y, int x, int size): Cell (y, x, size)
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
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (i == SIZE/2)
				currentCell[i][x] = 1;
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
bool Oscillator::drawCells() 
{
	char ch;
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if(currentCell[i][x] == 0)
				ch = '-';
			else
				ch = '+';
			mvwaddch(win, i+startY, x+startX, ch); // put character on window		
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
void Oscillator::updateCycle() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			currentCell[i][x] = newCell[i][x];
		}
	}
			
	Cell::clearArray(newCell);
}