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

  int sockfd , ret , ret1 , ret2 , client_size ;
  char buffer[100] , server_message[100] , client_message[100] ;
  
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));
    
  sockfd = socket( AF_INET , SOCK_STREAM , 0 );
  if(sockfd == -1)
  {
    printf("Socket creation failed\n");
    exit(1);
  }
  else printf("Socket creation success\n");
  
  struct sockaddr_in my_socket , client_addr ;
  my_socket.sin_family = AF_INET ;
  my_socket.sin_port = htons(5000) ;
  my_socket.sin_addr.s_addr = htonl(INADDR_ANY) ;

  ret = bind( sockfd , (const struct sockaddr *)(&my_socket) , sizeof(my_socket) );
  if(ret == -1)
  {
    printf("Bind failure\n");
    exit(1);
  }
  else printf("Bind Success\n") ;

  ret1 = listen(sockfd, 5);
  if(ret1 == -1)
  {
     printf("Listen failure\n");
     return -1;
  }
  else printf("Listen success\n"); 
  
  for(int i=0 ; i<5 ; i++)
  {
  client_size = sizeof(client_addr);
  ret2 = accept(sockfd, (struct sockaddr*)&client_addr, &client_size);
  
  if(ret2 == -1)
  {
    printf("Unable to accept message\n");
    exit(1);
  }
  else 
  {
   printf("Accepting message successfully\n") ;
   printf("Client connected at IP address: %s and Port number: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

  }
   int n,i=0;

   while(1)
      {
       
	n = recv(ret2, (char *)buffer, 100 , 0);
        
	buffer[n] = '\0';
    	
    	printf("Message from client: %s\n", buffer);
	if(strcmp(buffer, "exit") == 0)
	{
	    	send(ret2, "exit", strlen("exit"), 0);
		close(ret2);
    		return 0;
    	}
   
	printf("Enter a respose to be sent to client:");
	scanf("%s", server_message);
    	    
    	send(ret2, server_message, strlen(server_message), 0);
    	
      }
  }
  close(sockfd);
  
  return 0;
  }
