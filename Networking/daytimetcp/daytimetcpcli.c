#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/errno.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		printf("usage: ./run <IPaddress>\n");
	}

	sockfd = socket(AF_INET,SOCK_STREAM,0); 	
	if(sockfd == -1)
	{
		fprintf(stderr,"Socket error: %d\n",errno);
		perror("Error Desc : ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	const char *ip = inet_ntoa(servaddr.sin_addr);
	printf("Connect to %s\n",ip);

/*	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s",argv[1]);
		exit(1);
	}*/

//	printf("%d %p\n",sockfd,&servaddr);
	int num;

	if((num = connect(sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr))) < 0)
	{
		printf("Connection error! sockfd :%d  %d %ld !\n",sockfd,num,sizeof(servaddr));
		perror("Error: ");
		exit(1);
	}
	
	int counter  = 0;
	while((n = read(sockfd, recvline , MAXLINE)) > 0)
	{
		recvline[n] = 0;   /* null terminate */
		if(fputs(recvline,stdout) == EOF)
		{
			perror("fputs error : ");
			exit(1);
		}
		counter++;

	}

	printf("counter : %d\n",counter);

	if(n < 0)
	{
		printf("read error");
		exit(1);
	}
	printf("\nSuccefully excuted !\n");
	close(sockfd);
}

