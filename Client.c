#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* message = "hi, is this working?";
    char buffer[1024] = {0};

    char serverAddress[16];
    //get server IP
    printf("Input ip of server: ");
    gets(serverAddress);


    //create socket descriptor
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket connection error");
        return -1;
    }
    //set up address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0)
    {
        printf("Address invalid!");
        return -1;
    }
    //connect to socket
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connection failed.");
        return -1;
    }
    //send and recieve
    send(sock , message , strlen(message) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
}