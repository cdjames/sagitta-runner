#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <curses.h>
#include <iostream>
#include <string>
<<<<<<< HEAD
=======
#include "SagittaTypes.hpp"
>>>>>>> b1ecfa4d4b10b1dce51239783a80b57981d6cab7

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
	NetworkManager();
	int connectPlayer();
	int getPlayerNumber();
<<<<<<< HEAD
	int sendCoord(int);
	// Coord getCoord(short type);
	// Coord getPosition(short ship_or_bullet);
	// vector<Coord> syncPositions();
	// bool sendScore(int score);
	// int getScore();
	// int gameOver(int score);
};

#endif
=======
	int getNumberOfPlayers();
	void sendCoord(int, int);
	int getCoord(int);
	Coord getPosition();
	int getScore();
	void setScore(int);
	void gameOver(int);
};

#endif
>>>>>>> b1ecfa4d4b10b1dce51239783a80b57981d6cab7
