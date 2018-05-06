#include <stdio.h>
#include <stdlib.h>

int populate_array(int, int *);
int check_sin(int *);


int main(int argc, char **argv) {
    // TODO: Verify that command line arguments are valid.
    if (!(argc < 1 || argc > 1)) {
	    fprintf(stderr, "USAGE: validate_sin size [permissions]\n");
	    return 1;
    }
    char *tempstr;
    int sin = strtol(argv[1], &tempstr, 10);
    // printf("%d\n", sin);
	int ar[9];
	populate_array(sin, ar);
	// for (int i = 0; i < 9; ++i)
	// {
	// 	printf("%d\n", ar[i]);
	// }
	if 	(!check_sin(ar)) {
		printf("Valid SIN");
	} else {
		printf("Invalid SIN");
	}
    // TODO: Parse arguments and then call the two helpers in sin_helpers.c
    // to verify the SIN given as a command line argument.
  
    return 0;
}
