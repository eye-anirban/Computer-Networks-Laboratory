#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>

int main()
{

  int sockfd , ret , ret1 , ret2 ;
  char buf1[100];
  
  sockfd = socket( AF_INET , SOCK_DGRAM , 0 );
  if(sockfd == -1)
  {
    printf("Socket creation failed\n");
    exit(1);
  }
  else printf("Socket creation success\n");
  
  struct sockaddr_in my_socket ;
  my_socket.sin_family = AF_INET ;
  my_socket.sin_port = 6800 ;
  my_socket.sin_addr.s_addr = INADDR_ANY ;
  
  ret = bind( sockfd , (const struct sockaddr *)(&my_socket) , sizeof(my_socket) );
  if(ret == -1)
  {
    printf("Bind failure\n");
    exit(1);
  }
  else printf("Bind Success\n") ;
  
  char buf2[100] ;
  memset(buf1 , ' ' , 100 ) ;
  memset(buf2 , ' ' , 100 ) ;
  struct sockaddr_in dest ;
  dest.sin_family = AF_INET ;
  dest.sin_port = 6000 ;
  dest.sin_addr.s_addr = INADDR_ANY ;
  
  do{
  char mess[100] ;

  scanf("%s",mess);
  //memset(buf2 , ' ' , 100 ) ;
  strcpy(buf2,mess);
  
  ret2 = sendto(sockfd , buf2 , strlen(buf2) , 0 , (const struct sockaddr *)(&dest) , sizeof(dest) );
  if(ret2 == -1) 
  {
    printf("Failure in sending the data\n");
    exit(1);
  }
  else {
  printf("Success in sending the data\n");
  }

  struct sockaddr_in src ;
  int len = sizeof(src);
  
  ret1 = recvfrom(sockfd , buf1 , sizeof(buf1) , 0 , (struct sockaddr *)(&src) , (socklen_t*)(&len) );
  if(ret1 == -1) 
  {
    printf("Failure in recieving the data\n");
    exit(1);
  }
  else {
     printf("%s\n",buf1);
     printf("Success in recieving the data\n");
     }
  }while(buf1[0] != 'B' && buf1[1] != 'y' && buf1[2] != 'e');
  return 0;
}

