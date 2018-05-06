#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ptree.h"


int main(int argc, char **argv) {
	if (argc != 2 || argc != 4) {
		struct TreeNode *root = NULL;
		if (argc == 4) 
		{
			if (strcmp(argv[1], "-d") != 0) 
			{
				fprintf(stderr, "Usage:\tptree [-d N] PID\n");
				return 1;
			} else {
			    generate_ptree(&root, strtol(argv[3], NULL, 10));
				print_ptree(root, strtol(argv[2], NULL, 10));
			}

		} else {
		    printf("%d", generate_ptree(&root, strtol(argv[1], NULL, 10)));
			print_ptree(root, 0);
		}
		return 0;
	} else {
		return 1;
	}
}