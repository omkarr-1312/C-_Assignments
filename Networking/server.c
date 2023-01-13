#include "wrapper.h"
#include<time.h>

int main(void)
{
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	//Create socket
	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind to the set port and IP
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//Listen for clients:
	Listen(listenfd,LISTENQ);

	while(1)
	{
		//Accept an incoming connection
		connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
		ticks= time(NULL);
		snprintf(buff,sizeof(buff),"%s",ctime(&ticks));

		//Respond to client 
		write(connfd,buff,MAXLINE);

		close(connfd);
	}
	
	close(listenfd);

	return 0;
}
