#include "wrapper.h"


int main(void)
{
	int listenfd,connfd,client_size;
	int opt = 1;
	struct sockaddr_in servaddr,clientaddr;
	char buff[MAXLINE];
	    pid_t pid;

	//Create socket
	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	/*if(setsockopt( serverSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt)) < 0 ){
		perror("setsockopt(SO_REUSEADDR) Error\n");
		close(serverSock);
		exit(EXIT_FAILURE);
	}*/
	bzero(&servaddr,sizeof(servaddr));
	bzero(&clientaddr,sizeof(clientaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(11111);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind to the set port and IP
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//Listen for clients:
	Listen(listenfd,LISTENQ);
	int i = 0;
	while(1)
	{
		i++;
		client_size = sizeof(clientaddr);
		//Accept an incoming connection
		connfd = Accept(listenfd,(struct sockaddr*)&clientaddr,&client_size);

		printf("Client connected at IP: %s and port: %i\n",inet_ntop(AF_INET,&clientaddr.sin_addr,buff,sizeof(buff)),ntohs(clientaddr.sin_port));

		if((pid = fork()) == 0)
		{
			close(listenfd);

			while(1)
			{
				bzero(buff,sizeof(buff));
				//Receive client's message
				Recv(connfd,buff,MAXLINE,0);
				if(strlen(buff) != 0)
					printf("\nClient %i : %s\n",i,buff);
				if(strncmp("Bye!",buff,4)==0)
				{
					printf("Disconnected from %s:%i\n",inet_ntop(AF_INET,&clientaddr.sin_addr,buff,sizeof(buff)),ntohs(clientaddr.sin_port));
				}
/*				bzero(buff,sizeof(buff));
				//Get input from user
				printf("\nServer: ");
				fgets(buff,MAXLINE,stdin);*/

				//Respond to client
				Send(connfd,buff,MAXLINE,0);
			}
		}
		close(connfd);
	}

	close(connfd);


	printf("Client Says : Bye !!\n");

	return 0;
}
