/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Main routines Team Sagitta's infinite runner game
*********************************************************************/

#include <iostream>
#include "GameManager.hpp"

void initScreen();
void exitCurses(WINDOW * win);

int main()
{
	srand(std::time(0));
	/* create the blueprints for the objects (might take a second, should only be run once) */
	createAllBlueprints();
	WINDOW * win;
	initScreen();
	GameManager GM = GameManager(win);
	short playerdied = GM.run(); // runs until user presses q or hits an obstacle
	exitCurses(win);

	if(playerdied == 1)
		std::cout << "player hit an obstacle" << std::endl;
	else if (!playerdied) // i.e. 0
		std::cout << "player pressed q to quit" << std::endl;
	else // i.e. -1
		std::cout << "something strange happened in run()" << std::endl;
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