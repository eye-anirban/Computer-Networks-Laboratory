#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed");
    }
    printf("Socket creation success\n");

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connection failure");
        return 1;
    }

    printf("Connection Success\n");

    char message[1000], server_reply[2000], fileName[100], fileData[2000];
    strcpy(message,"file_name");  
    int sendto = send(sockfd, message, strlen(message), 0);
    int recvmsg = recv(sockfd, server_reply, 2000, 0);
    printf("%s", server_reply);
        
    printf("Enter file name to be received\n");
    scanf("%s",fileName);
    sendto = send(sockfd, fileName, strlen(fileName), 0);
    fflush(stdout);
    
    recvmsg = recv(sockfd, fileData, 2000, 0);
    printf("%s", fileData);
        
    FILE* ptr2 = fopen("recvfile.txt", "w");
    fprintf(ptr2,"%s",fileData);
    fclose(ptr2);
   
    return 0;
}
