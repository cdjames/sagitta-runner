#include "Cell.hpp"
#include <iostream>
#include <curses.h>

Cell::Cell()
{
	rowSize = colSize = SIZE = 3;
	currentCell = new int* [SIZE];
	newCell = new int *[SIZE];
	for( int i = 0 ; i < SIZE ; i++ ){
		currentCell[i] = new int[SIZE];
		newCell[i] = new int[SIZE];
	}
	startX = startY = xMove = yMove = 0;
	currentState = 1;
}

Cell::Cell(int x, int y, int size) // need to change elsewhere
{
	rowSize = colSize = SIZE = size;
	currentCell = new int* [SIZE];
	newCell = new int *[SIZE];
	for( int i = 0 ; i < SIZE ; i++ ){
		currentCell[i] = new int[SIZE];
		newCell[i] = new int[SIZE];
	}
	startX = x;
	startY = y;
	xMove = yMove = 0;
	currentState = 1;
}

Cell::~Cell()
{
	for( int i = 0 ; i < SIZE ; i++ ){
		delete [] currentCell[i];
		delete [] newCell[i];
		currentCell[i] = 0;
		newCell[i] = 0;
	}
	delete [] currentCell;
	delete [] newCell;
	currentCell = 0;
	newCell = 0;
	delwin(win);	// delete the window
	endwin();		// End curses mode
}

/*********************************************************************
** Description: 
** Put all 0s into new cell array
*********************************************************************/
void Cell::clearArray(int** array) 
{
	// int size = currentCell.size();
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			array[i][x] = 0;
		}
	}
}

/*********************************************************************
** Description: 
** This is the main algorithm. Loop through both dimensions of array
** and check neighbors of each cell. Rules are: 
1.	If an occupied cell has zero or one neighbor, it dies of loneliness. 
2.	If an occupied cell has more than three neighbors, it dies of overcrowding. 
3.	If an empty cell has exactly three occupied neighbor cells, there is a birth of a new cell
to replace the empty cell. 
4.	Births and deaths are instantaneous and occur at the changes of generation.
*********************************************************************/
void Cell::countNeighbors() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			int count = 0;

			/* 	count the neighboring cells; use <SIZE-1 and >0 to be sure that you
			 *	don't try to count outside the bounds of the array. Examples shown 
			 *	in the case that SIZE == 3 */
			if(i < SIZE-1) { // count when i is 0 or 1 (or bottom edge case)
				if( x < SIZE-1) // count when x is 0 or 1
					count += currentCell[i+1][x+1];

				if (x > 0) // count when x is 1 or 2
					count += currentCell[i+1][x-1];
				
				count += currentCell[i+1][x]; // safe to count
			}

			if (i > 0) // count when i is 1 or 2 (or top edge case)
			{
				if( x < SIZE-1) // count when x is 0 or 1
					count += currentCell[i-1][x+1];
				if (x > 0) // count when x is 1 or 2
					count += currentCell[i-1][x-1];

				count += currentCell[i-1][x]; // safe to count
			}

			/* safe to count when no matter i */
			if(x < SIZE-1) // and x is 0 or 1 (or right edge case)
				count += currentCell[i][x+1];

			if (x > 0) // and x is 1 or 2 (or left edge case)
				count += currentCell[i][x-1];
			
			/* now copy into new cell */
			if (count <= 1 || count > 3)
				newCell[i][x] = 0; // kill cell as if by over/underpopulation
			else if (count == 3)
				newCell[i][x] = 1; // birth new cell
			else
				newCell[i][x] = currentCell[i][x]; // stay the same
		}	
	}
}

void Cell::initWindow(int yIn, int xIn)
{
	initscr();					// Start curses mode
	win = newwin(20, 40, yIn, xIn); // make a new window
	timeout(250); 				// wait x Ms for user input before going to next getch() call
	noecho(); 					// don't print user input
	curs_set(0);				// make cursor invisible if possible
	printw("Press 'q' to quit.");	// instructions at top of screen
	refresh();					// put the printw on the screen

	/* create a 40 x 20 "window" */
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			mvwaddch(win, y, x, '-');	// move and add a character to these coords on win
		}
	}
	wrefresh(win);	// draw the window
}