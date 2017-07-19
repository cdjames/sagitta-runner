// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#define PORT 8081
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    char end[1024] = {0};
    std::string name;

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
    while(1) {

        printf("Play game? Y or N ->");
        // cin.ignore()
        getline (std::cin,name);
        if(name.compare("Y") == 0) {
            send(sock, name.c_str(), strlen(name.c_str()), 0);
            recv( sock , end, 1024, 0);
            if(strcmp(end, "end") == 0) {
                return 0;
            }
        }
        else {
            printf("Play game? Y or N ->");
            // cin.ignore()
            getline (std::cin,name);
        }
        
        // send(sock , hello , strlen(hello) , 0 );
        // printf("Hello message sent\n");
        // valread = recv( sock , buffer, 1024, 0);
        // printf("%s\n",buffer );
    }
    
    return 0;
}