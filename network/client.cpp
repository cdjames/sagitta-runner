#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#define PORT 8888
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char end[1024] = {0};
    std::string response;
    int num, numPlayers;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //Return from server the number of players connected to game.
    numPlayers = recv(sock, &num, sizeof(num), 0);
    if(num == 2) {
        printf("Sorry, two players already in game.\n");
    }
    else {
        printf("Play game? Type Y.");
        getline (std::cin, response);
        if(response.compare("Y") == 0) {
            send(sock, response.c_str(), strlen(response.c_str()), 0);
        }
        else {
            printf("User typed N, closing socket connection.\n");
            //CLOSE SOCKET CONNECTION?
        }

    }
    numPlayers = recv(sock, &num, sizeof(num), 0);
    printf("numPlayers = %d\n", num); 
    return 0;
}