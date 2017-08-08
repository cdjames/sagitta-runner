#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
#include <iostream>
#include "SagittaTypes.hpp"

    
#define TRUE   1 
#define FALSE  0 
#define PORT 8888 
#define MAX_CLIENTS 2

// void setUpServer(int*, int[], int*, int*, struct sockaddr_in *);
// int connectPlayers(int*, int[], int*, int*, struct sockaddr_in *);

struct gameState {
    struct Coord shipCoord;
    int score;
    int bullets;
    int difficulty;
    int numPlayers;
};

void initGameState(struct gameState &state) {
    state.shipCoord.x = 0;
    state.shipCoord.y = 0;
    state.score = 0;
    state.bullets = 5;
    state.difficulty = 1;
}

// void acceptRequests(int &master_socket, int &addrlen, struct sockaddr_in &address, int client_socket[], struct gameState &state) {
int acceptRequests(int client_socket[], struct gameState &state) {
    int valread, sd;
    int buffer;
    int i;
    fd_set readfds;
    char command[512] = {0};
    struct Coord recvCoord;

    for(int i = 0; i < 2; i++) {
        valread = recv(client_socket[i], &command, sizeof(command), 0);

        if(strcmp(command, "getNumPlayers") == 0) {
            int currentNumPlayers = state.numPlayers;
            int converted_number = htonl(currentNumPlayers);
            send(client_socket[i], &converted_number, sizeof(int), 0);
        }
        if(strcmp(command, "sendCoord") == 0) {
            char confirmation[512] = "confirmed";
            int move; // either up, down, left, right, space.
            int readval;
            int type;
            int playernum;
            send(client_socket[i], &confirmation, sizeof(confirmation), 0);
            valread = recv(client_socket[i], &type, sizeof(type), 0);
            move = ntohl(type);
            send(client_socket[i], &confirmation, sizeof(confirmation), 0);
            valread = recv(client_socket[i], &playernum, sizeof(playernum), 0);
            playernum = ntohl(playernum);
            printf("move recived from client: %d from player: %d\n", move, playernum);
        }
        if(strcmp(command, "getPosition") == 0) {
            // handle getCoord
            struct Coord c = state.shipCoord;
            send(client_socket[i], &c, sizeof(c), 0);
        }

        if(strcmp(command, "getScore") == 0) {
            int converted_number;
            converted_number = htonl(state.score);
            send(client_socket[i], &converted_number, sizeof(converted_number), 0);
        }

        if(strcmp(command, "setScore") == 0) {
            char confirmation[512] = "confirmed";
            int score, readval;
            send(client_socket[i], &confirmation, sizeof(confirmation), 0);
            readval = recv(client_socket[i], &score, sizeof(score), 0);
            score = ntohl(score);
            state.score = score;
        }
        if(strcmp(command, "gameOver") == 0) {
            printf("The game is over.\n");
            printf("Disconnecting both clients.\n");
            close(client_socket[0]);
            close(client_socket[1]);
            return 1;
        }
        memset(&command, '0', sizeof(command));
    }
    return 0;
}

void setUpServer(int &master_socket, int &addrlen, struct sockaddr_in &address) {
	int opt = TRUE;

    //master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
    
    //master socket to allow multiple connections.
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    } 
    
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
        
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
        
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 2) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
        
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
}

int connectPlayers(int &master_socket, int &addrlen, struct sockaddr_in &address, int client_socket[]) {
    int numPlayers = 0;
    int max_sd, activity, new_socket, clientReady;
    int acceptReqBool = 0;

    // Game state variables
    struct gameState state;

	//set of socket descriptors 
    fd_set readfds;  

	while(TRUE)  
	{  
        //clear the socket set 
		FD_ZERO(&readfds);  
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
           
        //wait for an activity on one of the sockets
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
            
        //If something happened on the master socket.. then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
            client_socket[numPlayers] = new_socket;

            //inform user of socket number - used in send and receive commands
            clientReady = recv(new_socket, &clientReady, sizeof(clientReady), 0);
            numPlayers++; 
            state.numPlayers = numPlayers;
        	int converted_number = htonl(numPlayers);
        	send(new_socket, &converted_number, sizeof(int), 0);

            if(numPlayers == 2) {
                break;
            }
        }    
    }  
    printf("We have 2 players now.\n");
    initGameState(state);
    while(acceptReqBool == 0) {
        acceptReqBool = acceptRequests(client_socket, state);
    }
    return 0;
}

int main(int argc , char *argv[]) {  
	int master_socket;
	struct sockaddr_in address; 
    int addrlen; 
    int client_socket[2];

    // Sets up socket/server connections.
	setUpServer(master_socket, addrlen, address);
	//Connects 2 players. Once two players connected, exits function.
	while(1) {
        connectPlayers(master_socket, addrlen, address, client_socket);
    }

    return 0;
}  