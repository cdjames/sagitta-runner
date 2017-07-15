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
	WINDOW * win;
	initScreen();

	// MenuManager MM = MenuManager(win); -> Inherit from GameManager. Set up window
	// Pass settings as parameter to GM 
	// Use arrow keys to move up and down. Model after run() in GM. Only allow y trajectory; ignore x
	// mvprintw(y, x, "Option 1: ..."); to print the options
	// getyx(WINDOW *win,int y,int x) or just keep track of y movement to get the current y position 
	// if getch() == KEY_UP and cursorPosition == valid option line -> go to next screen
	// put the above in a loop. When the user chooses exit or play, break the loop and continue.

	GameManager GM = GameManager(win); 
	GM.run(); // runs until user presses q
	// while (getch() != 'q'){
	// 	continue;
	// }
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