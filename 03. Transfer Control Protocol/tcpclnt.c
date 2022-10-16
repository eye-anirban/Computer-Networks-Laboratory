#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

int main()
{

  int sockfd , ret , ret1 , ret2 ;
  char buffer[100] , server_message[100] , client_message[100] ;
  
  memset(server_message,'\0',sizeof(server_message));
  memset(client_message,'\0',sizeof(client_message));
  
  sockfd = socket( AF_INET , SOCK_STREAM , 0 );
  if(sockfd == -1)
  {
    printf("Socket creation failed\n");
    exit(1);
  }
  else printf("Socket creation success\n");
  
  struct sockaddr_in my_socket ;
  my_socket.sin_family = AF_INET ;
  my_socket.sin_port = htons(5000) ;
  //my_socket.sin_addr.s_addr = INADDR_ANY ;
  my_socket.sin_addr.s_addr = inet_addr("127.0.0.1") ;
  
  ret = connect(sockfd, (struct sockaddr*)(&my_socket), sizeof(my_socket)) ;
  if(ret == -1)
  {
    printf("Connection failed\n");
    exit(1);
  }
  else printf("Connection success\n");
  
  int n;
  int len ;
  while(1)
   {
      printf("Enter message to be sent to the server: ");
      scanf("%s", client_message);
      ret1 = send(sockfd, client_message, strlen(client_message), 0 );    
      if(ret1 == -1) printf("Failure in sending message\n") ;	
    
      ret2 = recv(sockfd, (char *)buffer, 100 , 0);
	 
      buffer[ret2] = '\0';
      printf("Response from the Server: %s\n",buffer);
	if(strcmp(buffer, "exit") == 0)
    	{
    		send(sockfd, "exit", strlen("exit"), 0 );
    		close(sockfd);
    		return 0;
    	}
   }

    close(sockfd);
    return 0 ;   
}  
