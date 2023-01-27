#include "wrapper.h"

int inet_pton_loose(int family,const char *strptr,void *addrptr)
{
	if(family == AF_INET)
	{
		int n  = inet_pton(family,strptr,addrptr);
		printf("n : %d\n",n);
		if(n<0)
		{
			printf("inet_pton error for %s",strptr);
			return -1;
		}
		else if(n==0)
		{
			struct in_addr in_val;
			if(inet_aton(strptr,&in_val))
			{
				bzero(addrptr,sizeof(struct in_addr));
				printf("inet_aton successed .\n");
				return 1;
			}
		}
	}
	else if(family == AF_INET) 
	{
		return -1;
	}
}

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("Usage : ./run <IPaddress>\n");
		exit(1);
	}

	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	int n = inet_pton_loose(AF_INET,argv[1],&servaddr.sin_addr);

	if(n < 0)
	{
		printf("inet_pton_loose error for %s\n%d\n",argv[1],n);
		printf("Error: %d %s\n",errno,strerror(errno));
		exit(1);
	}

	printf("Successfully executed !\n");
	return 0;

}

