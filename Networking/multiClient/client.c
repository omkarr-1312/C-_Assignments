#include"wrapper.h"

int main(int argc,char** argv)
{
	int sockfd;
	char buff[MAXLINE+1];
	struct sockaddr_in servaddr;
	int n;

	if(argc != 2)
	{
		printf("Usage : ./runcl <IPaddress>\n");
	}

	//create socket:
	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	
	//set port and IP the same as server-side:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(11111);
	//servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	n = inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	if(n <= 0)
	{
		printf("Input Error ! IP address not valid !\n");
		exit(1);
	}

	
	Connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
		
	while(1)
	{	
		bzero(buff,sizeof(buff));
		//Get input from user
		printf("\nClient : ");
		fgets(buff,MAXLINE,stdin);

		//Send message to server
		Send(sockfd,buff,MAXLINE,0);
		
		bzero(buff,sizeof(buff));
		//Receive the server's response:
		Recv(sockfd,buff,MAXLINE,0);
		printf("\nServer: %s\n",buff);

		if(strncmp("Bye!",buff,4)==0)
		{
			break;
		}
	}
	
	//Close the socket
	close(sockfd);

	printf("Bye Bye ... !!\n");

	return 0;
}

