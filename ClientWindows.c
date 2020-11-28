#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")//library? idk windows wierd

int main()
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[128], server_reply[2000], ip[16];
    int recv_size;

    //get ip of server
    printf("Input ip of server: ");
    gets(ip);

    //initializing
    /*
        WSAStartup() is a function to load library(like i said, windows is wierd)
        MAKEWORD combines bytes? idk WSAStartup() takes wierd parameters
        &wsa is a pointer to a variable of type WSADATA, which stores info about 
    */
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("startup failed.");
        return -1;
    }

    //create socket
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("socket creation failed");
        return -1;
    }

    //setup address
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = inet_addr(ip);

    //connect to server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("connection error");
        return -1;
    }

    printf("connected");

    //get message to send
    puts("Input message: ");
    gets(message);

    //send message
    if(send(sock, message, sizeof(message), 0) < 0)
    {
        printf("sending message failed");
        return -1;
    }

    //print recieved message
    if(recv_size = (recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        printf("error recieving data\n");
    }
    server_reply[recv_size] = '\0';
    puts(server_reply);
    return 0;
}