#include <stdio.h>
#include <stdlib.h>
// TODO: Implement populate_array
// int populate_array(int sin, int *sin_array);
// int check_sin(int *sin_array);

// TODO: Implement check_sin
/* 
 * Return 0 (true) iff the given sin_array is a valid SIN.
 */
int check_sin(int *sin_array) {
	int tocheck[9] = {1,2,1,2,1,2,1,2,1};
	int finale[9];
	int sum;
	int issin = 0;
	int count;
	for (int i = 0; i < 9; ++i)
	{
		count = 0;
		sum = sin_array[i] * tocheck[i];
		if (sum <= 9)
		{
			finale[i] = sum;
		} else {
			while (sum > 0) {
				count += sum % 10;
				sum /= 10;
				// printf("%d,%d\n", sum, count);
			}
			finale[i] = count;
			// printf("%d, %d, %d\n", sin_array[i], tocheck[i], finale[i]);
		}
		// printf("%d, %d, %d\n", sin_array[i], tocheck[i], finale[i]);
		issin += finale[i];
		// printf("%d\n", finale[i]);
		// printf("%d\n", issin);
	}
	// for (int i = 0; i < 9; ++i)
	// {
	// 	printf("%d, %d\n", sin_array[i], finale[i]);
	// 	issin += finale[i];
	// }
	// printf("%d\n", issin);
	if (issin % 10 == 0)
	{
		return 0;
	}
	return 1;
}

/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
	// the size of the array can be calculated by sin % 10
	int copy = sin;
	int size = 0;
	while (copy != 0) {
		copy /= 10;
		size++;
	}
	copy = sin;
	// printf("%d\n", size);
	if (size == 9) {
		for (int i = 0; i < 9; ++i)
		{	
			// printf("%d\n", copy);
			if (copy != 0)
			{
				sin = copy % 10;
				copy /= 10;
				sin_array[i] = sin;
			}
		}
	}
    return 0;
}

