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
	for (int i = 0; i < winY; i++)
	{
		for (int x = 0; x < winX; x++)
		{
			if (x == winX-1)
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

	Drawer::countNeighbors(); // figure out next generation

	updateCycle(); // copy new cells into 1st generation; clear new array
}

/*********************************************************************
** Description: 
** Move whatever is on the right to the left
*********************************************************************/
bool Oscillator::moveScreenLeft() 
{
	char ch;
	for (int y = 0; y < winY; y++)
	{
		for (int x = 0; x < winX; x++)
		{
			if(x != winX-1) {
				if (currentCell[y][x+1] == 0){
					ch = '-';
					currentCell[y][x] = currentCell[y][x+1];
					currentCell[y][x+1] = 1;
				} else {
					ch = '+';
				}
			}
			else
				ch = '+';
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