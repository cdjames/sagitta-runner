#include "MenuManager.hpp"
//#include "GameManager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <math.h>

MenuManager::MenuManager() {
	strcpy(playerName, "Default Player ");
	xCoord = 13;
	yCoord = 10;
	titleXCoord = 8;
	titleYCoord = 6;
	difficultyLevel = 5;
	score = 0;
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
	std::ifstream fileStream("highscore.txt");
	std::string line;
	mvprintw(titleYCoord - 1, titleXCoord, "|------------------------ High Scores -----------------------|");
	mvprintw(titleYCoord - 4, titleXCoord - 4, "> Go Back");
	int count = 0;
	int i = getch();
	//if (!fileStream) {
	//	mvprintw(titleYCoord, titleXCoord, "There are no high scores yet.");
	//}
	//else{
		while (std::getline(fileStream, line)) {
			mvprintw(titleYCoord + count, titleXCoord, line.c_str());
			count++;
		}
	//}
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
				return playerNameScreen(0);
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
int MenuManager::playerNameScreen(int endScreen) {
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
				char ch;
				int j = 0;
				while (j < 15) {
					ch = fgetc(stdin);
					//Backspace
					if ((ch == 127 || ch == 8) && j > 0) {
						j--;
						playerName[j] = ' ';
						mvprintw(titleYCoord + 2, titleXCoord + 2 + j, "                 ");
						refresh();
					}
					//Enter a character

					else if ((ch == 127 || ch == 8) && j == 0)
						;
					
					else {
						playerName[j] = ch;
						char *tempString = inputName;
						mvprintw(titleYCoord + 2, titleXCoord + 2 + j, &playerName[j]);
						mvprintw(titleYCoord + 2, titleXCoord + 3 + j, "                       ");
						refresh();
						//ch = getch(); --> This doesn't wait for input so I had to use fgetc. 
						// I also tried gets()

						if (ch == 13) {
							while (j < 14) {
								playerName[j] = ' ';
								j++;
							}
							playerName[j] = '\0';
							break;
						}
						j++;
					}
				}
				//strcpy(playerName, inputName);
				if (endScreen == 0)
					return playerNameScreen(0);
				else if (endScreen == 1)
					return hsScreen();
			}

			else if (yMovement == 11) {
				if (endScreen == 0)
					return settingsMenu();
				else if (endScreen == 1)
					return hsScreen();
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

int MenuManager::hsScreen() {
	clearScreen();
	mvprintw(titleYCoord, titleXCoord, "Your score is %d", score);
	mvprintw(titleYCoord + 1, titleXCoord, "Your name is %s", playerName);
	mvprintw(yCoord, xCoord, ">");
	mvprintw(yCoord, xCoord + 2, "Save score using current name");
	mvprintw(yCoord + 1, xCoord + 2, "Change name");
	mvprintw(yCoord + 2, xCoord + 2, "Don't save score");

	int yMovement = yCoord;
	int i;
	do {
		i = getch();
		switch (i) {
		case KEY_UP:
			if (yMovement > yCoord) {
				mvprintw(yMovement, xCoord, " ");
				yMovement--;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case KEY_DOWN:
			if (yMovement < yCoord + 2) {
				mvprintw(yMovement, xCoord, " ");
				yMovement++;
				mvprintw(yMovement, xCoord, ">");
			}
			break;

		case(10):
			if (yMovement == yCoord) {

				int fileExists = 1;
				std::ifstream hsFile("highscore.txt");
				if (!hsFile) {
					fileExists = 0;
				}
				hsFile.close();

				std::ofstream outScore;
				outScore.open("highscore.txt", std::ios::app);

				if (!fileExists) {
					outScore << "PLAYER NAME\t\t\t\t\t\tSCORE" << std::endl;
					fileExists = 1;
				}
				outScore << playerName << "\t\t\t\t\t\t" << score << std::endl;
				return gameOver();
			}

			if (yMovement == yCoord + 1) {
				return playerNameScreen(1);
			}

			if (yMovement == yCoord + 2) {
				return gameOver();
			}

			break;
		}
	} while (i != 10);
	return -1;
}

int MenuManager::gameOver(){
	clearScreen();
	mvprintw(yCoord, xCoord, ">");
	mvprintw(yCoord, xCoord + 2, "Play again");
	mvprintw(yCoord + 1, xCoord + 2, "Return to the main menu");
	mvprintw(yCoord + 2, xCoord + 2, "Record your score");
	mvprintw(yCoord + 3, xCoord + 2, "Quit game");
	
	int yMovement = yCoord;
	int i;
	do {
		i = getch();
		switch(i){
		case KEY_UP:
			if (yMovement > yCoord){
				mvprintw(yMovement, xCoord, " ");
				yMovement--;
				mvprintw(yMovement, xCoord, ">");
			}
			break;
		
		case KEY_DOWN:
			if (yMovement < yCoord + 3){
				mvprintw(yMovement, xCoord, " ");
				yMovement++;
				mvprintw(yMovement, xCoord, ">");
			} 
			break;
			
		case(10):
			if (yMovement == yCoord){
				clearScreen();
				return 1;
				}
			else if (yMovement == yCoord + 1){
				clearScreen();
				return mainMenu();
				}
			else if (yMovement == yCoord + 2){
				clearScreen();
				return hsScreen();
				}
			else if (yMovement == yCoord + 3){
				clearScreen();
				return -1;
				}
		}	
	} while (i != 10);
	return -1;
}

void MenuManager::updateSettings(GameManager GM){
	score = GM.score;
}
