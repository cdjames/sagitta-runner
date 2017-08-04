#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <curses.h>
#include <iostream>
#include <string>

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
	void sendCoord();
	Coord getCoord();
	Coord getPosition();
	// vector<Coord> syncPositions();
	// bool sendScore(int score);
	// int getScore();
	// int gameOver(int score);
};

#endif