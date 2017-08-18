#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/select.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
#include <iostream>
#include "SagittaTypes.hpp"
#include <fstream>


    
#define TRUE   1 
#define FALSE  0 
#define PORT 30123 
#define MAX_CLIENTS 2
#define HS_FNAME "server_highscore.txt"
// #define DEBUG 1 // comment out to turn off debug statements

// void setUpServer(int*, int[], int*, int*, struct sockaddr_in *);
// int connectPlayers(int*, int[], int*, int*, struct sockaddr_in *);

struct gameState {
    struct Coord shipCoord;
    int score;
    int bullets;
    int difficulty;
    int numPlayers;
    int player1command;
    int player2command;
};

void initGameState(struct gameState &state) {
    state.shipCoord.x = 0;
    state.shipCoord.y = 0;
    state.score = 10;
    state.bullets = 5;
    state.difficulty = 0;
    state.player1command = 0;
    state.player2command = 0;
}

void readScore(int * highscore) {
    std::ifstream infile; 
    infile.open(HS_FNAME); 
    infile >> (*highscore);
    infile.close();
}

void addScoreToFile(int currentScore) {
    char filecurrentHS[10];
    int currentHS;
    std::ifstream infile; 
    // infile >> currentHS;
    readScore(&currentHS);
    infile.open(HS_FNAME); 
    // currentHS = atoi(filecurrentHS);
    //If this (state.score) is a new high score.
    if(currentHS < currentScore) {
        infile.close();
        std::ofstream outfile;
        outfile.open(HS_FNAME);
        outfile << currentScore;
        outfile.close();
    }
    //If this (state.score) isn't a new high score
    else {
        infile.close();
    }
}

// void acceptRequests(int &master_socket, int &addrlen, struct sockaddr_in &address, int client_socket[], struct gameState &state) {
int acceptRequests(int client_socket[], struct gameState &state) {
    int valread, sd;
    int buffer;
    int i;
    int seed = -1;
    int seed_sz = sizeof(seed);
    int p, playernum, move;
    bool reset_seed = false;
    fd_set readfds;
    char command[512] = {0};
    struct Coord recvCoord;
    struct CommStruct commStruct;
    int game_over = 0;
    bool done[2] = {false, false};

    for(int i = 0; i < 2; i++) {
        // valread = recv(client_socket[i], &command, sizeof(command), 0);
        if(!done[i])
            valread = recv(client_socket[i], &commStruct, sizeof(commStruct), 0);
        #ifdef DEBUG
        printf("%s\n", commStruct.cmd);
        #endif
	
    	//receive the difficulty
        if(strcmp(commStruct.cmd, "SC") == 0) {
            // int move;
            // valread = recv(client_socket[i], &commStruct, sizeof(commStruct), 0);
            playernum = commStruct.player;
            move = commStruct.move;
            #ifdef DEBUG
            printf("move received from client: %d from player: %d\n", move, playernum);
            #endif

            if(playernum == 1) {
                state.player1command = move;
            }
            if(playernum == 2) {
                state.player2command = move;
            }
            
        }
        // if(strcmp(command, "getCoord") == 0) {
        else if(strcmp(commStruct.cmd, "GC") == 0) {
            // int move;
            p = commStruct.player;
            if(p == 1) {
                move = state.player2command;
                commStruct.move = move;
                send(client_socket[i], &commStruct, sizeof(commStruct), 0);
            }
            if(p == 2) {
                move = state.player1command;
                commStruct.move = move;
                send(client_socket[i], &commStruct, sizeof(commStruct), 0);
            }
        }
        else if(strcmp(commStruct.cmd, "SE") == 0) {
            // valread = recv(client_socket[i], &commStruct, sizeof(commStruct), 0);
            if(state.numPlayers == 2) {
                if(seed == -1) // only create seed once per game
                    seed = time(0) + 2;
            }

            send(client_socket[i], &seed, seed_sz, 0); // send -1 unless you have 2 players
        }
        else if (strcmp(commStruct.cmd, "UD") == 0){
            state.difficulty += commStruct.difficulty;      
        }

        //get the difficulty
        else if (strcmp(commStruct.cmd, "GD") == 0){
            commStruct.difficulty = state.difficulty;
            send(client_socket[i], &commStruct, sizeof(commStruct), 0);
        }

        else if(strcmp(commStruct.cmd, "GNP") == 0){
            // valread = recv(client_socket[i], &commStruct, sizeof(commStruct), 0);
            commStruct.numPlayers  = state.numPlayers;
            send(client_socket[i], &commStruct, sizeof(commStruct), 0);
        }
        // if(strcmp(command, "sendCoord") == 0) {
        //getPosition
        else if(strcmp(commStruct.cmd, "GP") == 0) {
            struct Coord c = state.shipCoord;
            commStruct.shipCoord = c;
            send(client_socket[i], &commStruct, sizeof(commStruct), 0);
        }
        //getScore == get high score
        else if(strcmp(commStruct.cmd, "GS") == 0) {
            int hs;
            hs = state.score;
            /* only attempt to retrieve score from file if known to be higher by client */
            if(commStruct.move == 1) // repurposing move to be a high score flag here
                readScore(&hs);
            struct CommStruct cs;
            cs.score = hs; // may be sending a high score or this state's score depending on the above
            send(client_socket[i], &cs, sizeof(cs), 0);
        }
        //ss
        else if(strcmp(commStruct.cmd, "SS") == 0) {
            int score, readval;
            /* attempt to save only the higher score if there was a difference */
            if(commStruct.score > state.score)
                state.score = commStruct.score;
            /* only attempt to add score to file if known to be higher by client */
            if(commStruct.move == 1) // repurposing move to be a high score flag here
                addScoreToFile(state.score);
            // printf("score = %d\n", state.score);
        }
         //gameOver
        else if(strcmp(commStruct.cmd, "GO") == 0) {
            printf("The game is over.\n");
            printf("Disconnecting client %d.\n", i+1);
            done[i] = true;
            close(client_socket[i]);
            // close(client_socket[1]);
            seed = -1; // reset the seed for the next game
            game_over++;
        }

        if(game_over == 2)
            return 1;
        // memset(&command, '0', sizeof(command));
    }
    return 0;
}

void setUpServer(int &master_socket, int &addrlen, struct sockaddr_in &address, int port) {
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
    address.sin_port = htons( port );  
        
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", port);  
        
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
    int port = PORT;

    /* look for custom port */
    if(argc == 2) {
        port = atoi(argv[1]);
        if(port < 1) {
            printf("Please use a valid port number. Yours was '%d'\n", port);
            exit(1);
        }
    }

    // Sets up socket/server connections.
    setUpServer(master_socket, addrlen, address, port);
    //Connects 2 players. Once two players connected, exits function.
    while(1) {
        connectPlayers(master_socket, addrlen, address, client_socket);
    }

    return 0;
} 
