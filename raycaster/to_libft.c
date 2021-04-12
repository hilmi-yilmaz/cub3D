/* Standard library header files */
#include <stddef.h>

int		ft_arrlen(int **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
		i++;
	return (i);
}