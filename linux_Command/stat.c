#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[])
{
	struct stat sb;

	if (lstat(argv[1], &sb) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	switch (sb.st_mode & S_IFMT) {
		case S_IFDIR:  printf("directory\n");              
			       break;
		case S_IFREG:  printf("regular file\n");            
			       break;
	}

	printf("Last file modification:   %s", ctime(&sb.st_mtime));

	exit(EXIT_SUCCESS);
}

