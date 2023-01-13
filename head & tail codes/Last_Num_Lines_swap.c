#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 256

char ** lastnumlines(FILE * inputfp, unsigned int num)
{
	char** tailbuf = calloc(num,sizeof(char *));

	for(unsigned int i = 0; i < num;i++)
	{
		tailbuf[i] = calloc(SIZE,sizeof(char));
	}

	unsigned int iCount = 0;

	while(fgets(tailbuf[iCount%num],SIZE,inputfp) != NULL)
	{
	 	iCount++;
	}

	if(num > iCount)
	{
		num = iCount;
	}

	char* tempbuf;
	unsigned int iLength = iCount % num,iStart = 0,iDiff,iMove;
	iDiff = num - iLength;

	for(unsigned int i = iDiff; i > 0; i--,iStart++,iLength++)
	{
		iMove = iLength;
		for(unsigned int j = iStart; j != iMove; iMove--)
		{
			tempbuf = tailbuf[iMove];
			tailbuf[iMove] = tailbuf[iMove-1];
			tailbuf[iMove-1] = tempbuf;
	  	}
	}

	return tailbuf;

}

int main(void)
{
	unsigned int num;
	FILE * fp = fopen("fileDemo.txt", "r");

	if(fp == NULL)
	{
		printf("File not opened!!\n");
		exit(1);
	}

	printf("Enter the number of lines : ");
	scanf("%d",&num);

	if(num > 100 || num <= 0)
	{
		printf("Invalid input !\n");
		fclose(fp);
		exit(1);
	}


	char ** lastlines = lastnumlines(fp, num);


	for (unsigned int i = 0; i < num; i++)
	{
		if (lastlines[i] != NULL)
		{
			printf("%s", lastlines[i]);
		}
	}


	fclose(fp);

	for (unsigned int i = 0; i < num; i++)
	{
		free(lastlines[i]);
	}


	free(lastlines);

	return 0;
}
