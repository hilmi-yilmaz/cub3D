#include <stddef.h>

int	ft_str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i) != NULL)
		i++;
	return (i);
}
