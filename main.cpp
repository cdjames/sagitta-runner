/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Main routines Team Sagitta's infinite runner game
*********************************************************************/
#include <unistd.h>
#include <iostream>
#include "GameManager.hpp"
#include "MenuManager.hpp"
#include "NetworkManager.hpp"

void initScreen();
void exitCurses(WINDOW * win);
int runGame(WINDOW *win, vector<double> * timing_info, IPParams * ip_info);

int main(int argc, char const *argv[])
{
	/* determine input */
	IPParams ip_info = {"", -1};
	if(argc == 3) {
		ip_info.ip = argv[1];
		ip_info.port = atoi(argv[2]);
	}

	WINDOW *win;
	/* some setup */
	readFromRandFile("vals.cjr", &rand_num_list); // set up random functions
	createAllBlueprints();						  // set up blueprints that objects use
    initScreen();

	int play = 1;
	vector<double> timing_info; // to store and display timing info if enabled
	
	/* play until user chooses to quit */
	while (play == 1){
		#ifdef TIMING
		timing_info.clear();
		play = runGame(win, &timing_info, &ip_info);
		#else
		play = runGame(win, NULL, &ip_info);
		#endif
	}	
	exitCurses(win);

	#ifdef TIMING
	if(timing_info.size() == 3) {
		std::cout << "avg,max,min" << std::endl;
		std::cout << timing_info[0] << "," << timing_info[1] << "," << timing_info[2] << std::endl;
	}
	#endif

	return 0;
}

int runGame(WINDOW *win, vector<double> * timing_info, IPParams * ip_info){
	std::string ip;
	int port;
	short playerdied = -1;
	NetworkManager NM = NetworkManager();
	if(ip_info->port > 0 && ip_info->ip.compare("") != 0)
		NM.setConnParams(*ip_info);
	MenuManager MM = MenuManager(&NM); 
	int play = MM.mainMenu(), score = 0, seed = -1;
	while (play == 1 || play == 2){
		int connectSuccess = NM.setPlayer();
		if (connectSuccess == -1)
			return MM.errorScreen();	
		NM.setDifficulty(MM.getDifficulty());
		/* get the seed; time now + 2 seconds */
		while((seed = NM.getSeed()) == -1) {
			continue; // wait
		}
		cj_srand(seed); // called once per game
		GameManager GM = GameManager(win, &NM);
		GM.updateSettings(NM.getDifficulty() / 2);	
		playerdied = GM.run(timing_info); // runs until user presses q
		MM.updateSettings(GM);
		play = MM.gameOver();
		if (play == 1)
			play = MM.mainMenu();	
		if (play == 2)
			MM.findGame();	
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
