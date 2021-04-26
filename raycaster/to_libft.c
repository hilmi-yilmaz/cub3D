/* Standard library header files */
#include <stddef.h>

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
		i++;
	return (i);
}