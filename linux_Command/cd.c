#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char **argv)
{
    char s[100];
    //Printing the current working directory
    printf("%s\n",getcwd(s,100));
    //Changing the current working directory to the previous directory
    //chdir(argv[1]);
    if(chdir(argv[1]) == -1){
	printf("No such directory \n");
	exit(0);
    }	
    //Printing the now current working directory
    printf("%s\n",getcwd(s,100));
    return 0;
}
