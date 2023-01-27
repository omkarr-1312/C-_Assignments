/* Implementation of ls command in C */

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main(int argc,char **argv)
{
	//char dirname[10];
	DIR *p;
	struct dirent *d;
	//printf("Enter directory name : ");
	//scanf("%s",dirname);
	p=opendir(argv[1]);
	if(p==NULL){
  		perror("Cannot find directory");
  		exit(0);
  	}
	while(d=readdir(p)){
  		printf("%s  ",d->d_name);
	}

	printf("\n");
}
