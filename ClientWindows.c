#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")//library? idk windows wierd

int main()
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[128], server_reply[2000], ip[16];
    int recv_size, port;

    //get ip of server
    printf("Input ip of server: ");
    gets(ip);
    ip[16] = '\0';

    //get port
    printf("Input server port: ");
    scanf("%d", &port);

    //get message to send
    puts("Input message: ");
    gets(message);

    //initializing
    /*
        WSAStartup() is a function to load library(like i said, windows is wierd)
        MAKEWORD combines bytes? idk WSAStartup() takes wierd parameters
        &wsa is a pointer to a variable of type WSADATA, which stores info about 
    */
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("startup failed.\n");
        return -1;
    }
    puts("startup succeeded...\n");
    //create socket
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("socket creation failed\n");
        return -1;
    }
    puts("socket created...\n");
    //setup address
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    //connect to server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("connection error\n");
        return -1;
    }

    printf("connected\n");

    //send message
    if(send(sock, message, sizeof(message), 0) < 0)
    {
        printf("sending message failed\n");
        return -1;
    }
    puts("message sent\n");
    //print recieved message
    if(recv_size = (recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        printf("error recieving data\n");
    }
    printf("%s\n", server_reply);
    return 0;
}