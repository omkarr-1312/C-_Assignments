#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/errno.h>

#define MAXLINE 4096
#define LISTENQ 1

int Socket(int family,int type,int protocol)
{
	int n = socket(family,type,protocol);

	if(n == -1)
	{
		fprintf(stderr,"socket error with error no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}

	return n;
}

void Bind(int sockfd,const struct sockaddr* address, socklen_t address_len)
{
	if((bind(sockfd,address,address_len)) == -1)
	{
		fprintf(stderr,"Bind error with error no. : %d\n",errno);
		perror("Error Desc : \n");
		exit(1);
	}
}


void Listen(int sockfd,int backlog)
{
	if((listen(sockfd,backlog)) == -1)
	{
		fprintf(stderr,"Listen error with error no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}

int Accept(int sockfd,struct sockaddr* restrict_address,socklen_t *restrict_address_len)
{	
	int n = accept(sockfd,restrict_address,restrict_address_len);
	if(n == -1)
	{
		fprintf(stderr,"Accept error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}

	return n;
}

void Connect(int sockfd,struct sockaddr* address,socklen_t address_len)
{
	if((connect(sockfd,address,address_len)) == -1)
	{
		fprintf(stderr,"Connect error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}

void Write(int sockfd,const void *buf,size_t nbyte)
{
	if((write(sockfd,buf,nbyte)) == -1)
	{
		fprintf(stderr,"Write error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}

void Read(int sockfd,void *buf,size_t nbyte)
{
	if((read(sockfd,buf,nbyte)) == -1)
	{
		fprintf(stderr,"Read error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}

void Send(int sockfd,const void *buf,size_t length,int flags)
{
	if((send(sockfd,buf,length,flags)) == -1)
	{
		fprintf(stderr,"Send  error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}

void Recv(int sockfd,void *buf,size_t length,int flags)
{
	if((recv(sockfd,buf,length,flags)) == -1)
	{
		fprintf(stderr,"Recv error with erron no. : %d\n",errno);
		perror("Error Desc: \n");
		exit(1);
	}
}


