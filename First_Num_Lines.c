#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 256

char** firstnumlines(FILE * inputfp, unsigned int num)
{
	char** headbuf = calloc(num,sizeof(char *));

	unsigned int iCount = 0;
	
	for(unsigned int i = 0;i < num;i++)
	{
	       headbuf[i] = calloc(SIZE,sizeof(char));
	}
	
	 while(!feof(inputfp))
	 {
	 	fgets(headbuf[iCount],SIZE,inputfp);
	 	
	 	iCount++;
	 	if(iCount == num)
	 	{
	 		break;
	 	}	
	 }

	return headbuf; 	
}

int main(void)
{
	unsigned int num;
	FILE * fp = fopen("fileDemo.txt", "r");
	
	if(fp == NULL)
	{
		printf("file could not be opened !\n");
	}
	
	printf("Enter the number of lines : ");
	scanf("%d",&num);

	if(num > 100 || num <= 0)
	{
		printf("Invalid input !\n");
		fclose(fp);
		exit(1);
	}

	
	char** firstlines = firstnumlines(fp, num);

	for (unsigned int i = 0; i < num; i++) 
	{
		if (firstlines[i] != NULL) 
		{
			printf("%s", firstlines[i]);
		}
	}

	
	fclose(fp);
	
	for (unsigned int i = 0; i < num; i++) 
	{
		free(firstlines[i]);
		firstlines[i] = NULL;
	}
	
	
	free(firstlines);
	firstlines = NULL;
	
	return 0;
	
}
