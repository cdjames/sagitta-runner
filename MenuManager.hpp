/* This is the class that manages the menu system. It uses the default stdscr window. 
** GameManager is a friend class so that it can access custom settings that are set by 
** the user. */
#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP
#include "GameManager.hpp"
#include <curses.h>
#include <iostream>
#include <string>
using std::string;
class GameManager;
class MenuManager {
protected:
	int input;
	int yCoord;
	int xCoord;
	int titleYCoord;
	int titleXCoord;
	int difficultyLevel;
	char playerName[16];
	int score;
	int fileExists;
public:
	friend class GameManager;
	MenuManager();
	int findGame();
	void connect();
	int mainMenu();
	int settingsMenu();
	int difficultyScreen();
	int showScores();
	int playerNameScreen(int);
	void clearScreen();
	int gameOver();
	int hsScreen();	
	int play;	
};

#endif
