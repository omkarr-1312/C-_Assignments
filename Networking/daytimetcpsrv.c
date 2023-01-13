#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

#define MAXLINE 4096 

int main(void)
{
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd == -1)
	{
		perror("Socket error : ");
		exit(1);
	}
	printf("Socket established !\n");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999); //daytime server
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
//	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	const char *ip = inet_ntoa(servaddr.sin_addr);
	printf("Server host : %s\n",ip);
	
	//Bind to the set port and IP
	int n = bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(n < 0)		
	{
		printf(" n: %d listenfd: %d \n",n,listenfd);
		perror("Binding error : ");
		exit(1);
	}
	printf("Binding established \n");
	
	//Listen for clients :
	if(listen(listenfd,1) < 0)
	{
		perror("Listening error: ");
		exit(1);
	}

	printf("Listening established !\n");

	while(1)
	{	
		//Accept an incoming connection
		connfd = accept(listenfd,(struct sockaddr*) NULL,NULL);
		if(connfd < 0)
		{
			perror("Error in accepting client_addr : ");
			exit(1);
		}

		printf("Client socket accepted !\n");

		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%s",ctime(&ticks));
		//Respond to client
		write(connfd,buff,MAXLINE);

	/*	for(int i = 0; i < strlen(buff); i++)
		{
			write(connfd,&buff[i],1);
		}*/

		if(close(connfd) < 0)
		{
			perror("closing error : ");
			exit(1);
		}
	}
	close(listenfd);

}

