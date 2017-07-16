#include "MenuManager.hpp"
#include <fstream>
#include <iostream>
#include <string>

MenuManager::MenuManager() {
	input = ' ';

}


//Clears the ncurses screen assuming the default terminal size. 
void clearScreen() {
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
void MenuManager::showScores() {
	clearScreen();
	yCoord = 6;
	xCoord = 8;
	std::ifstream fileStream;
	fileStream.open("highscore.txt");
	std::string line;
	mvprintw(xCoord, yCoord, "> Back");
	int i = getch();
	if (!fileStream) {
		mvprintw(yCoord - 2, xCoord, "There are no high scores yet.");
	}
	else
		while (std::getline(fileStream, line)) {
			const char *s = line.c_str();
			mvprintw(yCoord, xCoord, s);
			xCoord++;
			yCoord++;
		}
	while (i != 10) {
		i = getch();
	}
	mainMenu();
}

/* The main function of this class; called in main. Manages the user's options and allows them to access
** submenus. Returns -1 if the user wants to quit the game and 1 if the user wants to play. */
int MenuManager::mainMenu() {
	clearScreen();
	yCoord = 10;
	xCoord = 13;
	mvprintw(6, 8, "Use up and down to move the cursor and enter to select an option.");
	mvprintw(yCoord, 13, ">");
	mvprintw(10, xCoord + 2, "Start Game");
	mvprintw(11, xCoord + 2, "Settings");
	mvprintw(12, xCoord + 2, "View High Scores");
	mvprintw(13, xCoord + 2, "Quit");

	int i;
	do
	{
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yCoord > 10) {
				mvprintw(yCoord, xCoord, " ");
				yCoord--;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yCoord < 13) {
				mvprintw(yCoord, xCoord, " ");
				yCoord++;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case 10:	// Enter key: "KEY_ENTER" doesn't work. 
			if (yCoord == 10) {
				play = 1; //play the game
			}

			else if (yCoord == 11) {
				settingsMenu(); // settings screen
			}

			else if (yCoord == 12) {
				showScores();
			}

			else if (yCoord == 13) {
				play = -1; //quit the game
			}

			break;
		}

	} while (i != 10);

	return play;
}



/* This is the settings submenu. The player can access third-level submenus or return to the previous menu. */
int MenuManager::settingsMenu() {
	clearScreen();
	yCoord = 10;
	xCoord = 13;
	mvprintw(6, 8, "Select the setting that you would like to change.");
	mvprintw(yCoord, 13, ">");
	mvprintw(10, xCoord + 2, "Difficulty");
	mvprintw(11, xCoord + 2, "Change Player Name");
	mvprintw(12, xCoord + 2, "Setting 3");
	mvprintw(13, xCoord + 2, "Back");
	int choice = 0; //stores the user's menu choice
	int i;
	do {
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yCoord > 10) {
				mvprintw(yCoord, xCoord, " ");
				yCoord--;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yCoord < 13) {
				mvprintw(yCoord, xCoord, " ");
				yCoord++;
				mvprintw(yCoord, xCoord, ">");
			}
			break;

		case 10: // Enter
			if (yCoord == 10) {
				choice = 1;
				difficultyScreen();
			}
			else if (yCoord == 11) {
				choice = 2;
				//playerNameScreen();
			}
			else if (yCoord == 12) {
				choice = 3;
				//Setting3Screen();
			}
			else if (yCoord == 13) {
				choice = 4;
				mainMenu();
			}

			break;

		default:
			break;
		}

	} while (i != 10);
}

/* Allows the user to select a difficulty. The returned difficult is the xCoord / 5, allowing for a range of 1-10.
** */
int MenuManager::difficultyScreen() {
	clearScreen();
	yCoord = 11;
	xCoord = 31;
	int changed = 0;
	mvprintw(6, 8, "Choose a difficulty by moving left or right and pressing enter.");
	mvprintw(yCoord, xCoord, "^");
	mvprintw(10, 11, "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |");
	int choice = 0; //stores the user's menu choice
	do {
		int i = getch();
		switch (i) {
		case KEY_RIGHT:
			if (xCoord < 51) {
				mvprintw(yCoord, xCoord, " ");
				xCoord++;
				mvprintw(yCoord, xCoord, "^");
			}
			break;

		case KEY_LEFT:
			if (xCoord > 12) {
				mvprintw(yCoord, xCoord, " ");
				xCoord--;
				mvprintw(yCoord, xCoord, "^");
			}
			break;

		case 10:
			changed = 1;
			break;

		}
	} while (changed == 0);
	difficultyLevel = xCoord / 5;
	settingsMenu();
}