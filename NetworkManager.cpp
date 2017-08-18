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


NetworkManager::NetworkManager() {
	client_socket = 0;
	ip = DEF_IP;
	port = DEF_PORT;
//	player = connectPlayer(); // Connects player to the server. Assigns player #.
}

int NetworkManager::setPlayer(){
	player = connectPlayer();
	return player;
}

void NetworkManager::setDifficulty(int diff){
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "UD");
	commStruct.difficulty = diff;
	send(client_socket, &commStruct, sizeof(commStruct), 0);
}
		
int NetworkManager::getDifficulty(){
	int readval;
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "GD");
	commStruct.player = player;
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &commStruct, sizeof(commStruct), 0);
	return commStruct.difficulty;
}

void NetworkManager::setConnParams(IPParams ip_info) {
	this->ip = ip_info.ip;
	this->port = ip_info.port;
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
	serv_addr.sin_port = htons(port);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
//		printf("\nConnection Failed \n");
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

//GNP
int NetworkManager::getNumberOfPlayers() {
	// memset(&commStruct, '\0', sizeof(commStruct));
	int readval;
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "GNP");
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &commStruct, sizeof(commStruct), 0);
	return commStruct.numPlayers;
}

//SC
void NetworkManager::sendCoord(int command, int player) {
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "SC");
	commStruct.move = command;
	commStruct.player = player;
	send(client_socket, &commStruct, sizeof(commStruct), 0);
}

//Add player number parameter
//if player 1, return last input from player 2.
//if player 2, return last input from player 1.
//int NetworkManager::getCoord(playerNum) {

//GC
int NetworkManager::getCoord(int playerNum) {
	int readval;
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "GC");
	commStruct.player = playerNum;
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &commStruct, sizeof(commStruct), 0);
	return commStruct.move;
}
//GP
Coord NetworkManager::getPosition() {
	// Returns the "master" coordinates for type ship or bullet.
	int readval;
	struct Coord shipCoord;
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "GP");
	
	//First send str to indicate to server what to return.
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &commStruct, sizeof(commStruct), 0);

	return commStruct.shipCoord;
}
//GS
int NetworkManager::getScore(bool high) {
	int readval, score;
	struct CommStruct commStruct;
	commStruct.move = 0;
	if (high)
		commStruct.move = 1; // use as a flag in server
	strcpy(commStruct.cmd, "GS");
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &commStruct, sizeof(commStruct), 0);
	return commStruct.score;
}

//SS
void NetworkManager::setScore(int score, bool high) {
	struct CommStruct commStruct;
	commStruct.move = 0;
	if (high)
		commStruct.move = 1; // use as a flag in server
	strcpy(commStruct.cmd, "SS");
	
	commStruct.score = score;
	send(client_socket, &commStruct, sizeof(commStruct), 0);
}

//gameOver
void NetworkManager::gameOver() {
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "GO");
	send(client_socket, &commStruct, sizeof(commStruct), 0);
}

int NetworkManager::getSeed() {
	int readval, seed;
	struct CommStruct commStruct;
	strcpy(commStruct.cmd, "SE");
	send(client_socket, &commStruct, sizeof(commStruct), 0);
	readval = recv(client_socket, &seed, sizeof(seed), 0);
	return seed;
}

