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

int main()
{
	/* prepare pseudo-random sequence */
	readFromRandFile("vals.cjr", &RAND_NUM_LIST);
	cj_srand(300); // number must be <= CJ_RAND_MAX; modulo that value in case of using times for example
	/* create the blueprints for the objects (might take a second, should only be run once) */
	createAllBlueprints();
	WINDOW * win;
	initScreen();
	short playerdied = -1;
	MenuManager MM = MenuManager(); 
	int play = MM.mainMenu(),
		score = 0;
	vector<double> timing_info;
	NetworkManager NM = NetworkManager();
	// def_prog_mode(); // get out of curses mode
	// endwin();
	std::cout << "waiting for another player..." << std::endl;
	while(NM.getNumberOfPlayers() < 2) {
		continue; // wait
	}
	// reset_prog_mode(); // re-enter curses mode
	while (play == 1){
		GameManager GM = GameManager(win, &NM);
		GM.updateSettings(MM);	
		playerdied = GM.run(&score, &timing_info); // runs until user presses q
		play = MM.gameOver();
		MM.clearScreen();
	}
	
	exitCurses(win);

	if(timing_info.size() == 3) {
		std::cout << "avg,max,min" << std::endl;
		std::cout << timing_info[0] << "," << timing_info[1] << "," << timing_info[2] << std::endl;
	}
	std::cout << "final score is " << score << std::endl;
	// if(playerdied == 1)
	// 	std::cout << "player hit an obstacle" << std::endl;
	// else if (!playerdied) // i.e. 0
	// 	std::cout << "player pressed q to quit" << std::endl;
	// else // i.e. -1
	// 	std::cout << "something strange happened in run()" << std::endl;
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
	refresh();					// put the printw on the screen
}

void exitCurses(WINDOW * win) {
	delwin(win);	// delete the window
	endwin();		// End curses mode
}
