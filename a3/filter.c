#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

/**
* This method reads numbers from readfd and 
* and if they are not a multiple of n writes
* it to writefd.
*/
 int filter(int n, int readfd, int writefd) {  
 	int num;
    while (read(readfd, &num, sizeof(int)) > 0) {
 		if (num % n != 0)
 		{
 			if (write(writefd, &num, sizeof(int)) < 0) {
 				perror("write in filter");
 				return 1;
 			}
 		}
    }
 	return 0;
 }