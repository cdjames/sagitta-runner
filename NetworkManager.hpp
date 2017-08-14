#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <curses.h>
#include <iostream>
#include <string>
#include "SagittaTypes.hpp"

using std::string;

class NetworkManager {
private:
	// int xCoor;
	// int yCoor;
	// int score;
	// int bullets;
	int gameReadyBool; // gameReadyBool = 1 when two players connect to server.
	int player; //1 = player1, 2 = player2.
	int client_socket;

public:
	void setPlayer();
	NetworkManager(); //
	int connectPlayer(); //
	int getPlayerNumber(); //
	int getNumberOfPlayers(); //
	void sendCoord(int, int);
	int getCoord(int);
	Coord getPosition();
	int getScore();
	void setScore(int);
	void gameOver(int);
};

#endif
