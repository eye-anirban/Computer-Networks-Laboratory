#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/time.h>

#define MAXFD 10	

void fds_add(int fds[],int fd)
{
	int i=0;
	for(;i<MAXFD;++i)
	{
		if(fds[i]==-1)
		{
	          fds[i]=fd;
		  break;
		}
	}
}

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1) printf("Socket Creation Failure\n") ;
	printf("Socket Creation Success\n") ;
	printf("Sockfd = %d\n",sockfd);
    
	struct sockaddr_in saddr,caddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(6000);
	saddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(res == -1) printf("Bind Failure\n") ;
	printf("Bind Success\n") ;

	listen(sockfd,5);

    fd_set fdset;

    int fds[MAXFD];
    int i=0;
    for(;i<MAXFD;++i)
    {
	  	fds[i]=-1;
    }

    fds_add(fds,sockfd);

	while(1)
    {
		FD_ZERO(&fdset);

		int maxfd=-1;
		int i=0;

		for(;i<MAXFD;i++)
		{
			if(fds[i]==-1)
			{
				continue;
			}

			FD_SET(fds[i],&fdset);

			if(fds[i]>maxfd)
			{
				maxfd=fds[i];
			}
		}

		struct timeval tv={5,0};	

		int n=select(maxfd+1,&fdset,NULL,NULL,&tv);
		if(n==-1)	
		{
			printf("Select Error\n");
		}
		else if(n==0)
		{
			printf("Time Out\n");
		}
		else
		{
			for(i=0;i<MAXFD;++i)
			{
				if(fds[i]==-1)	
				{
					continue;
				}
				if(FD_ISSET(fds[i],&fdset))
				{
					if(fds[i]==sockfd)
					{
						struct sockaddr_in caddr;
						int len=sizeof(caddr);

						int c=accept(sockfd,(struct sockaddr *)&caddr,&len);
						if(c<0)
						{
							continue;
						}
					
						printf("Accept c=%d\n",c);
						fds_add(fds,c);
					}
					else   
					{
						char buff[128]={0};
						int res=recv(fds[i],buff,127,0);
						if(res<=0)
						{
							close(fds[i]);
							fds[i]=-1;
							printf("One client is over ! \n");
						}
						else
						{
							printf("recv(%d)=%s\n",fds[i],buff);
							printf("Please input:");
							fgets(buff,128,stdin);
							send(fds[i],buff,sizeof(buff),0);
						}
					}
				}
			}
		}
	}
}
