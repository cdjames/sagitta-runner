/* This is the class that manages the menu system. It uses the default stdscr window. 
** GameManager is a friend class so that it can access custom settings that are set by 
** the user. */

#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP
#include <curses.h>
#include <iostream>

class MenuManager {
private:
	int input;
	int yCoord;
	int xCoord;
	int play;

public:
	MenuManager();
	int mainMenu();
	int settingsMenu();
	int difficultyScreen();
	void showScores();

	int difficultyLevel;
};

#endif