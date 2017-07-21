/* This is the class that manages the menu system. It uses the default stdscr window. 
** GameManager is a friend class so that it can access custom settings that are set by 
** the user. */
#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP
#include <curses.h>
#include <iostream>
#include <string>

using std::string;

class MenuManager {
private:
	int input;
	int yCoord;
	int xCoord;
	int titleYCoord;
	int titleXCoord;
	int play;

public:
	MenuManager();
	int findGame();
	void connect();
	int mainMenu();
	int settingsMenu();
	int difficultyScreen();
	int showScores();
	int difficultyLevel;
	int playerNameScreen();
	void clearScreen();
	char playerName[16];
};

#endif