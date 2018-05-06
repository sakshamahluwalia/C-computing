#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char *input, char *given) {
	// printf("%s input\n", input);
	int count = 0;
	if (input[0] == 'd')
	{
		return 1;
	}
	for (int i = 1; i < 10; i++)
	{
		if (given[count] != '-')
		{
			if (given[count] != input[i])
			{
				return 1;
			}
		}
		count++;
	}
	// printf("%s input\n", input);
	return 0;
}


int main(int argc, char** argv) {
	char waste[31];
	char *forstrtol;
	char input[31];
	int inputsize;
	int Bool = 0;
	int primaryindex   = 0;
	int secondaryindex = 0;
	int sizeteller     = 1;
	int finalcount     = 0;
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE: count_large size [permissions]\n");
        return 1;
    }
    int size = strtol(argv[1], &forstrtol, 10);
    scanf("%s", waste);
    scanf("%s", waste);
    while (scanf("%s", input) != EOF) {
    	Bool = 0;
    	// printf("%s, %d\n", input, primaryindex);
    	if (argc == 3)
    	{
			if (primaryindex % 9 == 0)
	    	{    	
				Bool = check_permissions(input, argv[2]);
				// printf("%s, %d bool\n", input, Bool);
	    	}
	    	if (Bool)
			{
				primaryindex--;
				// printf("%s\n", input);
				for (int i = 0; i < 8; ++i)
				{
					scanf("%s", waste);
					// printf("%s \n", waste);
				}
			}
			if (isdigit(*input))
			{
				// printf("%s\n", input);
				if (secondaryindex == sizeteller)
				{
	 				inputsize = strtol(input, &forstrtol, 10);
	 				// printf("%d %d\n", inputsize, size);
	 				if (inputsize > size)
	 				{
	 					finalcount++;
	 				}
					sizeteller  += 4;
					// printf("%s %d\n", input, secondaryindex);
				}
				secondaryindex++;
				// printf("%s %d %d\n", input, secondaryindex, secondaryindex == sizeteller);
			}
	    	// printf("%s %d\n", input, primaryindex);
	    	primaryindex++;
    	} else {
			if (primaryindex % 9 == 0)
	    	{    	
    			if (input[0] == 'd')
	    		{
	    			Bool = 1;
	    		}		
	    		// printf("%s, %d bool\n", input, Bool);
	    	}
	    	if (Bool)
			{
				primaryindex--;
				// printf("%s\n", input);
				for (int i = 0; i < 8; ++i)
				{
					scanf("%s", waste);
					// printf("%s \n", waste);
				}
			}
			if (isdigit(*input))
			{
				// printf("%s\n", input);
				if (secondaryindex == sizeteller)
				{
	 				inputsize = strtol(input, &forstrtol, 10);
	 				// printf("%d %d\n", inputsize, size);
	 				// printf("%s\n", input);
	 				if (inputsize > size)
	 				{
	 					finalcount++;
	 				}
					sizeteller  += 4;
					// printf("%s %d\n", input, secondaryindex);
				}
				secondaryindex++;
				// printf("%s %d %d\n", input, secondaryindex, secondaryindex == sizeteller);
			}
	    	// printf("%s %d\n", input, primaryindex);
	    	primaryindex++;
    	}
    }
    printf("%d\n", finalcount);
    return 0;
}
