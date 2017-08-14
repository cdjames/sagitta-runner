/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Main routines Team Sagitta's infinite runner game
*********************************************************************/

#include <iostream>
#include "GameManager.hpp"
#include "MenuManager.hpp"
#include "NetworkManager.hpp"

void initScreen();
void exitCurses(WINDOW * win);
int runGame(WINDOW *);

int main()
{
	WINDOW *win;
	readFromRandFile("vals.cjr", &RAND_NUM_LIST);
	cj_srand(300);
	createAllBlueprints();
        initScreen();
	int play = 1;
	while (play == 1){
		play = runGame(win);
	}	
	exitCurses(win);
	return 0;
}
int runGame(WINDOW *win){
	short playerdied = -1;
	NetworkManager NM = NetworkManager();
	MenuManager MM = MenuManager(&NM); 
	vector<double> timing_info;
	int play = MM.mainMenu(), score = 0;
	if (play == 1){
		NM.setPlayer();
		while(NM.getNumberOfPlayers() < 2) {
			continue; // wait
		}
		int repeat = 0;
		GameManager GM = GameManager(win, &NM);
		GM.updateSettings(MM);	
		MM.updateSettings(GM);
		playerdied = GM.run(&score, &timing_info); // runs until user presses q
		play = MM.gameOver();

	}

	return play;
}

void initScreen() {
	initscr();				// Start curses mode
	cbreak();				/* Line buffering disabled, Pass on everything to me */
	keypad(stdscr, TRUE);	/* I need that nifty F1 */
	// scrollok(stdscr, FALSE);
	timeout(DEF_TIMEOUT); 				// wait x Ms for user input before going to next getch() call
	noecho(); 					// don't print user input
	curs_set(0);				// make cursor invisible if possible
	refresh();					// put the printw on the screen
}

void exitCurses(WINDOW * win) {
	delwin(win);	// delete the window
	endwin();		// End curses mode
}
