#include "Drawer.hpp"
#include <iostream>
#include <curses.h>

Drawer::Drawer()
{
	gTimeout = DEF_TIMEOUT;
	rowSize = colSize = SIZE = 3;
	currentCell = new int* [winY];
	newCell = new int *[winY];
	for( int i = 0 ; i < winX ; i++ ){
		currentCell[i] = new int[winX];
		newCell[i] = new int[winX];
	}
	startX = startY = xMove = yMove = 0;
	currentState = 1;
}

Drawer::Drawer(int x, int y, int size) // need to change elsewhere
{
	gTimeout = 50;
	rowSize = colSize = SIZE = size;
	currentCell = new int* [winY];
	newCell = new int *[winY];
	for( int i = 0 ; i < winY ; i++ ){
		currentCell[i] = new int[winX];
		newCell[i] = new int[winX];
	}
	startX = x;
	startY = y;
	xMove = yMove = 0;
	currentState = 1;
}

Drawer::~Drawer()
{
	for( int i = 0 ; i < winY ; i++ ){
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
** Put all 0s into new drawer array
*********************************************************************/
void Drawer::clearArray(int** array) 
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
** and check neighbors of each drawer. Rules are: 
1.	If an occupied drawer has zero or one neighbor, it dies of loneliness. 
2.	If an occupied drawer has more than three neighbors, it dies of overcrowding. 
3.	If an empty drawer has exactly three occupied neighbor drawers, there is a birth of a new drawer
to replace the empty drawer. 
4.	Births and deaths are instantaneous and occur at the changes of generation.
*********************************************************************/
void Drawer::countNeighbors() 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			int count = 0;

			/* 	count the neighboring drawers; use <SIZE-1 and >0 to be sure that you
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
			
			/* now copy into new drawer */
			if (count <= 1 || count > 3)
				newCell[i][x] = 0; // kill drawer as if by over/underpopulation
			else if (count == 3)
				newCell[i][x] = 1; // birth new drawer
			else
				newCell[i][x] = currentCell[i][x]; // stay the same
		}	
	}
}

void Drawer::initWindow(int yIn, int xIn)
{
	initscr();					// Start curses mode
	win = newwin(winY, winX, yIn, xIn); // make a new window
	timeout(gTimeout); 				// wait x Ms for user input before going to next getch() call
	noecho(); 					// don't print user input
	curs_set(0);				// make cursor invisible if possible
	printw("Press 'q' to quit.");	// instructions at top of screen
	refresh();					// put the printw on the screen

	/* create a ## x ## "window" */
	// for (int y = 0; y < winY; y++)
	// {
	// 	// for (int x = 0; x < winX; x++)
	// 	// {
	// 		mvwaddch(win, y, winX-1, '-');	// move and add a character to these coords on win
	// 	// }
	// }
	wrefresh(win);	// draw the window
}

void Drawer::startMovement() {
	do
	{
		moveScreenLeft(); // pure virtual; needs to be implemented in child class
		// switch (prefs){
		// 	case 'g':
		// 		myGlider->drawCells();
		// 		break;
		// 	case 'c':
		// 		myGun->drawCells();	
		// 		break;
		// 	default: // 'o' or anything else
		// 		myOsc->drawCells();
		// }
	} while ((input = getch()) != 'q');
}