#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);	
	if(sockfd == -1) printf("Socket Creation Failure\n") ;
	printf("Socket Creation Success\n") ;
	printf("Sockfd = %d\n",sockfd);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(res == -1) printf("Connection Failure\n") ;
	printf("Connection Success\n") ;

	while(1)
	{
		char buff[128] = {0};
		printf("Please Input:");
		fgets(buff,128,stdin);
		if(strncmp(buff,"logout",6) ==0 )
		{
			break;
		}
		send(sockfd,buff,strlen(buff),0);
		memset(buff,0,128);
		recv(sockfd,buff,127,0);
		printf("RecvBuff:%s\n",buff);
		printf("\n");
	}
	close(sockfd);
}
