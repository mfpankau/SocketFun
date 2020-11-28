#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sock = 0, valread, port;
    struct sockaddr_in serv_addr;
    char message[1024];
    char buffer[1024] = {0};

    char serverAddress[16];
    //get server IP
    printf("Input ip of server: ");
    gets(serverAddress);

    //get server port
    printf("Input port of server: ");
    scanf("%d", &port);

    //create socket descriptor
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket connection error\n");
        return -1;
    }
    //set up address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0)
    {
        printf("Address invalid!\n");
        return -1;
    }
    //connect to socket
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connection failed.\n");
        return -1;
    }
    printf("connected to server\n");
    
    //recieve
    valread = read( sock , buffer, 1023); 
    printf("%s\n",buffer ); 
    
    //send
    fgets(&message, 1023, stdin);
    send(sock , message , strlen(message) , 0 ); 
    printf("message sent\n"); 
    
    

    return 0;
}