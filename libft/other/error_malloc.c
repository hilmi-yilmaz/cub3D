#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void	*error_malloc(unsigned int bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
	{
		printf("Error: %s\n", strerror(errno));
		return (NULL);
	}
	return (ptr);
}
