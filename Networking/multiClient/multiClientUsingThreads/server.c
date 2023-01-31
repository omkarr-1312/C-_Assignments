#include "wrapper.h"
static int i = 0;

void *doit(void *arg){
	int clientSocket = *(int *)arg;
	char buff[MAXLINE];
	while(1){
		bzero(buff,sizeof(buff));
                //Receive client's message
                Recv(clientSocket,buff,MAXLINE,0);
                printf("\nClient %i : %s\n",i,buff);
		if(strncmp(buff,"bye",3)==0){                                        
			printf("Disconnected from client(%i)\n",clientSocket);
			break;
                }
		Send(clientSocket,buff,MAXLINE,0);
	}
	close(clientSocket);
	return arg;
}



int main(void)
{
	int listenfd,connfd,client_size;
	int opt = 1;
	struct sockaddr_in servaddr,clientaddr;
	char buff[MAXLINE];
	pthread_t tid;

	//Create socket
	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt)) < 0 ){
		perror("setsockopt(SO_REUSEADDR) Error\n");
		close(listenfd);
		exit(EXIT_FAILURE);
	}
	bzero(&servaddr,sizeof(servaddr));
	bzero(&clientaddr,sizeof(clientaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(54321);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind to the set port and IP
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//Listen for clients:
	Listen(listenfd,LISTENQ);

	while(1)
	{
		i++;
		client_size = sizeof(clientaddr);
		//Accept an incoming connection
		connfd = Accept(listenfd,(struct sockaddr*)&clientaddr,&client_size);

		printf("Client connected at IP: %s and port: %i\n",inet_ntop(AF_INET,&clientaddr.sin_addr,buff,sizeof(buff)),ntohs(clientaddr.sin_port));
		//create child thread to process client
		if(pthread_create(&tid,NULL,doit,&connfd)==0){
			pthread_detach(pthread_self());
		}
		else{
			perror("pthread_create() error");
		}
		
	}
	close(listenfd);
	return 0;
}
