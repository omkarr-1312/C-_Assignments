#include "wrapper.h"
#include<time.h>

int main(void)
{
	int listenfd,connfd,client_size;
	struct sockaddr_in servaddr,clientaddr;
	char buff[MAXLINE];
	

	//Create socket
	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	bzero(&clientaddr,sizeof(clientaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind to the set port and IP
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//Listen for clients:
	Listen(listenfd,LISTENQ);
	
	client_size = sizeof(clientaddr);
	//Accept an incoming connection
	connfd = Accept(listenfd,(struct sockaddr*)&clientaddr,&client_size);
		
	printf("Client connected at IP: %s and port: %i\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		

	while(1)
	{
		bzero(buff,sizeof(buff));
		//Receive client's message
		Recv(connfd,buff,MAXLINE,0);
		printf("\nClient : %s\n",buff);
		
		bzero(buff,sizeof(buff));
		//Get input from user
		printf("\nServer: ");
		fgets(buff,MAXLINE,stdin);

		//Respond to client 
		Send(connfd,buff,MAXLINE,0);

		if(strncmp("Bye!",buff,4) == 0)
		{
			break;
		}
	}
	
	close(connfd);
	close(listenfd);

	printf("Client Says : Bye !!\n");

	return 0;
}
