/* Standard library header files */
#include <stdio.h>
#include <string.h> //strerror
#include <errno.h> //errno

/* User defined header files */
#include "../cub3d.h"

int	error_colour(void)
{
	printf("Error\nFormat of colour data isn't correct.\n");
	printf("Give 3 numbers for R, G and B separated by kommas and 1 or more spaces.\n");
	return (-1);
}

// void    *error_malloc(void)
// {
//     printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
//     return (NULL);
// }