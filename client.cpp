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
    int sock = 0;
    struct sockaddr_in serv_addr;
    int clientReady = 1; // Send to server to indicate client ready.
    int num, playerNumber; // Returned from server to indicate player number. 1 or 2.
    char buffer[1024] = {0};

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
    send(sock, &clientReady, sizeof(clientReady), 0);
    playerNumber = recv(sock, &num, sizeof(num), 0);
    int player = ntohl(num);

    printf("This client is player %d\n", player);

    char input[512] = {0};
    while(1) {
        printf("Enter: ");
        scanf("%s", input);
        send(sock, &input, sizeof(input), 0);
    }
    
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> b1ecfa4d4b10b1dce51239783a80b57981d6cab7
