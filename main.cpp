/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Main routines Team Sagitta's infinite runner game
*********************************************************************/

#include <iostream>
#include "GameManager.hpp"

void initScreen();
void exitCurses(WINDOW * win);
void initObjects();

int main()
{
	/* create the blueprints for the objects (might take a second) */
	createShipBlueprints();
	WINDOW * win;
	initScreen();
	// initObjects();
	GameManager GM = GameManager(win);
	GM.run(); // runs until user presses q
	exitCurses(win);
	return 0;
}

void initScreen() {
	initscr();				// Start curses mode
	cbreak();				/* Line buffering disabled, Pass on everything to me */
	keypad(stdscr, TRUE);	/* I need that nifty F1 */
	// scrollok(stdscr, FALSE);
	timeout(DEF_TIMEOUT); 				// wait x Ms for user input before going to next getch() call
	noecho(); 					// don't print user input
	curs_set(0);				// make cursor invisible if possible
	printw("Press 'q' to quit.");	// instructions at top of screen
	refresh();					// put the printw on the screen
}

void exitCurses(WINDOW * win) {
	delwin(win);	// delete the window
	endwin();		// End curses mode
}

void initObjects() {
	createShipBlueprints();
}