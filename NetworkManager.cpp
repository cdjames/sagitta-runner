#include "NetworkManager.hpp"
#include "SagittaTypes.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

NetworkManager::NetworkManager() {
	client_socket = 0;

	player = connectPlayer(); // Connects player to the server. Assigns player #.
}

int NetworkManager::connectPlayer() {
	// Creates clientside socket to connect to game server.
	// Returns 1 if first player to connect. Returns 2 if second player to connect.

	struct sockaddr_in serv_addr;
	int clientReady = 1; // Send to server to indicate client ready.
	int num, playerNumber; // Returned from server to indicate player number. 1 or 2.

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}
  
	memset(&serv_addr, '0', sizeof(serv_addr));
  
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\nConnection Failed \n");
		return -1;
	}
	send(client_socket, &clientReady, sizeof(clientReady), 0);
	playerNumber = recv(client_socket, &num, sizeof(num), 0);
	int player = ntohl(num);

    // printf("This client is player %d\n", player);

    return player;
}

int NetworkManager::getPlayerNumber() {
	return player;
}

int NetworkManager::getNumberOfPlayers() {
	char msg[512] = "getNumPlayers";
	int readval, num;
	send(client_socket, &msg, sizeof(msg), 0);
	readval = recv(client_socket, &num, sizeof(num), 0);
	num = ntohl(num);
	return num;
}

void NetworkManager::sendCoord(Coord coord, int type) {

	char msg[512] = "sendCoord";
	int readval;
	int converted_number;
	//First send str to indicate to server what to return.
	send(client_socket, &msg, sizeof(msg), 0);
	memset(&msg, '0', sizeof(msg));
	readval = recv(client_socket, msg, sizeof(msg), 0);
	if(strcmp(msg, "confirmed") == 0) {
		send(client_socket, &coord, sizeof(coord), 0);
		memset(&msg, '0', sizeof(msg));
		readval = recv(client_socket, msg, sizeof(msg), 0);
		if(strcmp(msg, "confirmed") == 0) {
			converted_number = htonl(type);
            send(client_socket, &converted_number, sizeof(int), 0);
		}
	}
}

Coord NetworkManager::getCoord() {
	// Returns the "master" coordinates for type ship or bullet.
	char msg[512] = "getCoord";
	int valread;
	struct Coord shipCoord;
	//First send str to indicate to server what to return.
	send(client_socket, &msg, sizeof(msg), 0);
	valread = recv(client_socket, &shipCoord, sizeof(shipCoord), 0);

	return shipCoord;
}

Coord NetworkManager::getPosition() {
	// Returns the "master" coordinates for type ship or bullet.
	char msg[512] = "getPosition";
	int valread;
	struct Coord shipCoord;
	//First send str to indicate to server what to return.
	send(client_socket, &msg, sizeof(msg), 0);
	valread = recv(client_socket, &shipCoord, sizeof(shipCoord), 0);

	return shipCoord;
}

int NetworkManager::getScore() {
	int readval, score;
	char msg[512] = "getScore";
	send(client_socket, &msg, sizeof(msg), 0);
	readval = recv(client_socket, &score, sizeof(score), 0);
	score = ntohl(score);

	return score;
}

void NetworkManager::setScore(int score) {
	char msg[512] = "setScore";
	int valread, converted_number;
	send(client_socket, &msg, sizeof(msg), 0);
	memset(&msg, '0', sizeof(msg));
	valread = recv(client_socket, &msg, sizeof(msg), 0);
	if(strcmp(msg, "confirmed") == 0) {
		converted_number = htonl(score);
        send(client_socket, &converted_number, sizeof(int), 0);
	}
}

void NetworkManager::gameOver(int score) {
	char msg[512] = "gameOver";
	send(client_socket, &msg, sizeof(msg), 0);

}

