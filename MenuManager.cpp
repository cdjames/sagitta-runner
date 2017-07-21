#include "MenuManager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <math.h>

MenuManager::MenuManager() {
	strcpy(playerName, "player");
	xCoord = 13;
	yCoord = 10;
	titleXCoord = 8;
	titleYCoord = 6;
	difficultyLevel = 5;
}


//Clears the ncurses screen assuming the default terminal size. 
void MenuManager::clearScreen() {
	int i;
	int j;
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 80; j++) {
			mvprintw(i, j, " ");
		}
	}
}

/* Manages the high score option in the menu. Displays the contents of highscore.txt. When the user presses
** enter it returns them to the previous settings screen. */
int MenuManager::showScores() {
	clearScreen();
	std::ifstream fileStream;
	fileStream.open("highscore.txt");
	std::string line;
	mvprintw(titleXCoord, titleYCoord, "> Back");
	int i = getch();
	if (!fileStream) {
		mvprintw(titleYCoord - 2, titleXCoord, "There are no high scores yet.");
	}
	else
		while (std::getline(fileStream, line)) {
			const char *s = line.c_str();
			mvprintw(titleYCoord, titleXCoord, s);
			//increment counter and add to x/y
		}
	while (i != 10) {
		i = getch();
	}
	return mainMenu();
}

//Attempts to connect the player with a teammate
int MenuManager::findGame() {
	clearScreen();
	mvprintw(yCoord, xCoord, "Searching for another player...");
	// start 30 second timer
	// press q to quit and return to menu
	// if player found
		// return connect();
	// if time out
		//return 0 and return to menu
}

//Connects the two players
void MenuManager::connect() {
	clearScreen();
	mvprintw(yCoord, xCoord, "Attempting to connect players...");
	//if success return 1 --> start the game
	//else return 0 
}

/* The main function of this class; called in main. Manages the user's options and allows them to access
** submenus. Returns -1 if the user wants to quit the game and 1 if the user wants to play. */
int MenuManager::mainMenu() {
	clearScreen();
	mvprintw(titleYCoord, titleXCoord, "Use up and down to move the cursor and enter to select an option.");
	mvprintw(yCoord, xCoord, ">");
	mvprintw(yCoord, xCoord + 2, "Start Game");
	mvprintw(yCoord + 1, xCoord + 2, "Settings");
	mvprintw(yCoord + 2, xCoord + 2, "View High Scores");
	mvprintw(yCoord + 3, xCoord + 2, "Quit");
	int yMovement = yCoord;
	int i;
	do
	{
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yMovement > 10) {
				mvprintw(yMovement, xCoord, " ");
				yMovement--;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yMovement < 13) {
				mvprintw(yMovement, xCoord, " ");
				yMovement++;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case 10:	// Enter key: "KEY_ENTER" doesn't work. 
			if (yMovement == 10) {
				//play = findGame(); //play the game
				return 1;	// temp until we are able to connect players 
			}

			else if (yMovement == 11) {
				return settingsMenu(); // settings screen
			}

			else if (yMovement == 12) {
				return showScores();
			}

			else if (yMovement == 13) {
				return -1; //quit the game
			}

		}

	} while (i != 10);

	return -1;	//this shouldn't happen
}



/* This is the settings submenu. The player can access third-level submenus or return to the previous menu. */
int MenuManager::settingsMenu() {
	clearScreen();
	mvprintw(titleYCoord, titleXCoord, "Select the setting that you would like to change.");
	mvprintw(yCoord, xCoord, ">");
	mvprintw(yCoord, xCoord + 2, "Difficulty");
	mvprintw(yCoord + 1, xCoord + 2, "Change Player Name");
	mvprintw(yCoord + 2, xCoord + 2, "Back");
	int i;
	int yMovement = yCoord;
	do {
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yMovement > 10) {
				mvprintw(yMovement, xCoord, " ");
				yMovement--;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yMovement < 12) {
				mvprintw(yMovement, xCoord, " ");
				yMovement++;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case 10: // Enter
			if (yMovement == 10) {
				return difficultyScreen();
			}
			else if (yMovement == 11) {
				return playerNameScreen();
			}
			else if (yMovement == 12) {
				return mainMenu();
			}

		}

	} while (i != 10);

	return -1;
}

/* This function allows the player to change their name. I wasn't able to use ncurses to get the string input so I had to use
	fgets. We can change this if it's problematic. 
*/
int MenuManager::playerNameScreen() {
	clearScreen();
	mvprintw(titleYCoord, titleXCoord, "Your current name is %s", playerName);
	mvprintw(yCoord, xCoord, ">");
	mvprintw(yCoord, xCoord + 2, "Change name");
	mvprintw(yCoord + 1, 15, "Go back");
	int yMovement = yCoord;
	int i;
	do {
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yMovement > 10) {
				mvprintw(yMovement, xCoord, " ");
				yMovement--;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yMovement < 11) {
				mvprintw(yMovement, xCoord, " ");
				yMovement++;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case 10: // Enter
			if (yMovement == 10) {
				clearScreen();
				mvprintw(titleYCoord, titleXCoord, "Enter a new name up to 15 characters and press enter.");
				mvprintw(titleYCoord + 2, titleXCoord, "> ");
				refresh();
				char inputName[16];
				inputName[15] == '\0';
				char ch;
				for (int j = 0; j < 15; j++) {
					ch = fgetc(stdin);
					inputName[j] = ch;
					char *tempString = inputName;
					mvprintw(titleYCoord + 2, titleXCoord + 2 + j, &inputName[j]);
					mvprintw(titleYCoord + 2, titleXCoord + 3 + j, "                       ");
					refresh();
					//ch = getch(); --> This doesn't wait for input so I had to use fgetc. 
					// I also tried gets()
					if (ch == 13) {
						inputName[j + 1] = '\0';
						break;
					}
				}
				strcpy(playerName, inputName);
				return playerNameScreen();
			}

			else if (yMovement == 11) {
				return settingsMenu();
			}

			break;
		}

	} while (i != 10);

	return -1;
}

/* Allows the user to select a difficulty. The returned difficult is the xCoord / 5, allowing for a range of 1-10.
** */
int MenuManager::difficultyScreen() {
	clearScreen();
	int tempY = 12;
	int tempX = 31;
	int changed = 0;
	mvprintw(titleYCoord, titleXCoord, "Choose a difficulty by moving left or right and pressing enter.");
	mvprintw(titleYCoord + 1, titleXCoord, "The current difficulty is %d", difficultyLevel);
	mvprintw(tempY, tempX, "^");
	mvprintw(11, 11, "| 1 . 2 . 3 . 4 . 5 . 6 . 7 . 8 . 9 . 10 |");
	int xMovement = tempX;
	do {
		int i = getch();
		switch (i) {
		case KEY_RIGHT:
			if (xMovement < 51) {
				mvprintw(tempY, xMovement, " ");
				xMovement++;
				mvprintw(tempY, xMovement, "^");
			}
			break;

		case KEY_LEFT:
			if (xMovement > 12) {
				mvprintw(tempY, xMovement, " ");
				xMovement--;
				mvprintw(tempY, xMovement, "^");
			}
			break;

		case 10:
			changed = 1;
			break;

		}
	} while (changed == 0);

	difficultyLevel = ceil((xMovement - 8 ) / 4);
	return settingsMenu();
}
