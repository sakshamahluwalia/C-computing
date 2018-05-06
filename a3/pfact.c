#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>
#include "filter.h"

/*
* Helper to update the values of f1, f2 and boolean.
*/
void factorcheck(int* boolean, int* number, int* filter_val, int* f1, int* f2) {

    if (*boolean == 0 && (*number) % (*filter_val) == 0){
        *f1 = *filter_val;
        (*boolean)++;
        (*f2) = (*number) / (*filter_val);
    }

}

/**
* Helper to remove duplicate code.
*/
void printisprime(int number, int f1, int f2, int i) {
    printf("%d %d %d\n", number, f1, f2);
    printf("Number of filters = %d\n", i);
}

/**
* Helper to remove duplicate code.
*/
void printisnotprime(int number, int i) {
    printf("%d is not the product of two primes\n", number);
    printf("Number of filters = %d\n", i);
}

/**
* This program implements an algorithm based on the 
* Sieve of Eratosthenes to determine whether a number 
* N can be factored into exactly two primes, and if it 
* can be factored, identifies the values of the two factors.
*/
int main(int argc, char** argv) {
    // check if the user provided only 1 argument.
    if (argc != 2)
    {
        fprintf(stderr, "Usage:\n\tpfact n\n");
        return 1;
    }

    // check if the format of the number is right.
    char *waste;
    int number = strtol(argv[1], &waste, 10);
    if (strlen(waste) != 0)
    {
        fprintf(stderr, "Usage:\n\tpfact n\n");
        return 1;
    }

    if (number == 4)
    {
        printisprime(number, 2, 2, 0);
        return 0;
    }

    int f1 = 0;
    int f2 = 0;
    int index = 1;
    int boolean = 0;
	int filter_val = 2;
    int square_root = (int)(floor(sqrt(number)));

    // an array containing (sqrt(n)) amount of int arrays.
    int mainpipe[square_root + 1][2];

    // create a pipe out of the first element.
    if (pipe(mainpipe[0]) == -1) {
        perror("pipe");
    }

    // intial fork.
    int firstfork = fork();

    // parent
    if (firstfork > 0) {

        // Close the read file descriptor since parent will only write to the pipe.
        if (close(mainpipe[0][0]) < 0) {
            perror("close read in parent");
        }

        // Write every number from 2 to n to pipe.
        for (int i = 2; i <= number; i++)
        {
            if (write(mainpipe[0][1], &i, sizeof(int)) == -1) {
                perror("write to pipe");
            }
        }

        // close the pipe after writing.
        if (close(mainpipe[0][1]) < 0) {
            perror("close write in parent");
        }

        // Wait for child process to finish before terminating.
        int status;
        wait(&status);

    // child
    } else if (firstfork == 0) {

        // close the write end of the orginal pipe.
        if (close(mainpipe[0][1]) < 0) {
            perror("close parent in child");
        }   

        pid_t pids;
        while (filter_val <= square_root) {

            // make a new pipe for a new process.
            if (pipe(mainpipe[index]) < 0) {
                perror("pipe");
            }

            // second fork.
            if ((pids = fork()) < 0) {
                perror("fork");
                abort();
            }

            // child generated from the second fork.
            if (pids == 0) {

                // filter values from the old pipe and write it to the new pipe.
                filter(filter_val, mainpipe[index-1][0], mainpipe[index][1]);

                // close the write end for the new pipe.
                if (close(mainpipe[index][1]) < 0) {
                    perror("close write in parent");
                }

                // close the read end of the old pipe.
                if (close(mainpipe[index - 1][0]) < 0){
                    perror("close here");
                    exit(1);
                }

                exit(index);

            } else if (pids > 0) {

                // check if the filter_val is a factor of number.
                factorcheck(&boolean, &number, &filter_val, &f1, &f2);

                // check if number is the square of filter_val.
                if (number == filter_val * filter_val) {
                    printisprime(number, f1, f2, index);
                    exit(0);
                }

                // update the value of filter_val
                if (read(mainpipe[index][0], &filter_val, sizeof(int)) == -1) {
                    perror("error reading");
                }

                if ((boolean == 1) && ( number % filter_val == 0 && filter_val < square_root)) {
                    printisnotprime(number, index);
                    exit(0);
                }

                // check if the filter_val is a factor of number.
                factorcheck(&boolean, &number, &filter_val, &f1, &f2);

                if (boolean == 1 && f2 == filter_val && f2 >= square_root){
                    printisprime(number, f1, f2, index);
                    exit(0);
                }

            }
            index++;
        }

        if (boolean == 1 &&  f2 >= square_root) {
            if (f2 == f1 * f1) {
                printisprime(number, f1, f2, index-1);
                exit(0);
            }
            printisprime(number, f1, f2, index-1);
            exit(0);
        } else {
            printf("%d is prime\nNumber of filters = %d\n", number, index - 1);
        }

        // error in intial fork.
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}