#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket == -1)
    {
        printf("Socket creation failed");
    }
    printf("Socket creation success\n");

    struct sockaddr_in server;
    inet_aton("127.0.0.1", &server.sin_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    
    int bindfd = bind(my_socket, (struct sockaddr *)&server, sizeof(server));
    if (bindfd == -1)
    {
        printf("Bind failure");
        return 1;
    }
    printf("Bind success\n");

    listen(my_socket, 3);

    printf("Waiting for connections\n");
    int c = sizeof(struct sockaddr_in);

    struct sockaddr_in client;
    int client_sock = accept(my_socket, (struct sockaddr *)&client, (socklen_t *)&c);
    if (client_sock == -1)
    {
        printf("Accept failed");
        return 1;
    }
    printf("Connection Accepted\n");

    char client_message[2000], messages[2000];
    int recvmsg = recv(client_sock, client_message, 2000, 0);
    if (strcmp(client_message, "file_name") == 0)
       system("ls > res.txt");   
    fflush(stdout);
    
    FILE* ptr = fopen("res.txt", "r");
    char ch;
    char fileList[1000] = "";
    int i =0;
    while (ch != EOF)
    {
        ch = fgetc(ptr);
        fileList[i++]=ch;
    }
    
    char clientFileName[1000] = "";
    int sendto = send(client_sock, fileList, strlen(fileList), 0);
    recvmsg = recv(client_sock, clientFileName, 2000, 0);
    printf("client message: %s\n",clientFileName);
    fflush(stdout);
    ch='1';
    FILE* ptr2 = fopen(clientFileName, "r");
    char fileData[1000] = "";
    i =0;
    while (ch != EOF)
    {
        ch = fgetc(ptr2);
        fileData[i++]=ch;
    } 
    
    sendto = send(client_sock, fileData, strlen(fileData), 0);
    
    return 0 ;
}
