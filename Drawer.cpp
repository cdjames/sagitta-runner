#include "Drawer.hpp"
#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <ctime>

Drawer::Drawer()
{
	srand(std::time(0)); // seed random generator
	gTimeout = DEF_TIMEOUT;
	rowSize = colSize = SIZE = 3;
	currentCell = new int* [WINY];
	newCell = new int *[WINY];
	for( int i = 0 ; i < WINX ; i++ ){
		currentCell[i] = new int[WINX];
		newCell[i] = new int[WINX];
	}
	// explosion = new int* [3];
	// for( int i = 0 ; i < 3 ; i++ ){
	// 	explosion[i] = new int[3];
	// }
	startX = startY = xMove = yMove = 0;
	currentState = 1;
	user_coords.x = WINX/10;
	user_coords.y = WINY/2;
	input = ' ';
	fr_multiplier = DEF_MULTIPLIER;
	fr_counter = fr_counter_2 = 0;
	doGameOver = FALSE;
}

Drawer::Drawer(int x, int y, int size) // need to change elsewhere
{
	srand(std::time(0)); // seed random generator
	gTimeout = DEF_TIMEOUT;
	rowSize = colSize = SIZE = size;
	currentCell = new int* [WINY];
	newCell = new int *[WINY];
	for( int i = 0 ; i < WINY ; i++ ){
		currentCell[i] = new int[WINX];
		newCell[i] = new int[WINX];
	}
	startX = x;
	startY = y;
	xMove = yMove = 0;
	currentState = 1;
	user_coords.x = WINX/10;
	user_coords.y = WINY/2;
	input = ' ';
	fr_multiplier = DEF_MULTIPLIER;
	fr_counter = fr_counter_2 = 0;
	doGameOver = FALSE;
}

Drawer::~Drawer()
{
	for( int i = 0 ; i < WINY ; i++ ){
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
	initscr();				// Start curses mode
	cbreak();				/* Line buffering disabled, Pass on everything to me */
	keypad(stdscr, TRUE);	/* I need that nifty F1 */
	win = newwin(WINY, WINX, yIn, xIn); // make a new window
	keypad(win, TRUE);
	timeout(gTimeout); 				// wait x Ms for user input before going to next getch() call
	noecho(); 					// don't print user input
	curs_set(0);				// make cursor invisible if possible
	printw("Press 'q' to quit.");	// instructions at top of screen
	refresh();					// put the printw on the screen

	/* create a ## x ## "window" */
	// for (int y = 0; y < WINY; y++)
	// {
	// 	// for (int x = 0; x < WINX; x++)
	// 	// {
	// 		mvwaddch(win, y, WINX-1, '-');	// move and add a character to these coords on win
	// 	// }
	// }
	wrefresh(win);	// draw the window
}

void Drawer::startMovement() {
	drawCells(); // pure virtual; needs to be implemented in child class
	mvwaddch(win, user_coords.y, user_coords.x, SHIP); // draw the ship
	do
	{
		// save the previous user coordinates
		prev_user_coords = user_coords;
		/* determine background framerate (gTimeout * fr_multiplier) and update background
			as necessary 
		*/
		if(fr_counter == fr_multiplier) {
			moveScreenLeft(); // pure virtual; needs to be implemented in child class
			fr_counter = 0;
		} else {
			fr_counter++;
		}

		/* the idea here is to update the user_coords variable, "move" the ship there,
			then draw a blank where it used to be, finally refreshing the window */
		switch (input){
			case KEY_UP:
				mvprintw(0, 24, "pressed up     ");
				// refresh();
				if(user_coords.y > 0)
					user_coords.y--;
				break;
			case KEY_DOWN:
				mvprintw(0, 24, "pressed down   ");
				// refresh();
				if(user_coords.y < WINY-1)
					user_coords.y++;
				break;
			case KEY_LEFT:
				mvprintw(0, 24, "pressed left   ");
				// refresh();
				if(user_coords.x > 0)
					user_coords.x--;
				break;
			case KEY_RIGHT:
				mvprintw(0, 24, "pressed right  ");
				// refresh();
				if(user_coords.x < WINX-1)
					user_coords.x++;
				break;
			default: 
				mvprintw(0, 24, "pressed nothing");
				break;
		}
		
		
		// erase the old ship
		mvwaddch(win, prev_user_coords.y, prev_user_coords.x, BLANK);
		// move the ship
		if(currentCell[user_coords.y][user_coords.x] != 0 || currentCell[prev_user_coords.y][prev_user_coords.x] != 0) {
			wrefresh(win);
			doGameOver = TRUE;
			break; // get out of loop, game is over
		}
		else {
			mvwaddch(win, user_coords.y, user_coords.x, SHIP);
		}
		wrefresh(win);

	} while ((input = getch()) != 'q');

	if(doGameOver)
		doExplosion();
}

void Drawer::doExplosion() {
	int adder[3] = {-1, 0, 1};
	mvprintw(0, 24, "game over      ");
	refresh();
	fr_multiplier -= 2;
	
	while ((input = getch()) != 'q'){
		if(fr_counter_2 == fr_multiplier) {
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if( ((1 + rand()) % 5) == 0)
						mvwaddch(win, user_coords.y+adder[y], user_coords.x+adder[x], EXPLOSION);
					else
						mvwaddch(win, user_coords.y+adder[y], user_coords.x+adder[x], BLANK);
				}
			}
			wrefresh(win);
			fr_counter_2 = 0;
		} else {
			fr_counter_2++;
		}

	}
}