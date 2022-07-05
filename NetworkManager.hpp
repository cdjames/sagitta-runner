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
	string ip;
	int port;

public:
	void setDifficulty(int);
	int getDifficulty();
	int setPlayer();
	NetworkManager(); //
	int connectPlayer(); //
	int getPlayerNumber(); //
	int getNumberOfPlayers(); //
	void sendCoord(int, int);
	int getCoord(int);
	Coord getPosition();
	int getScore(bool);
	void setScore(int, bool);
	void gameOver();
	int getSeed();
	void setConnParams(IPParams ip_info);
};

#endif
