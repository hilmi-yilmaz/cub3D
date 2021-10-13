/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 13:13:25 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	copy = error_malloc(sizeof(*copy) * (ft_str_arr_len(map) + 1));
	if (copy == NULL)
		return (NULL);
	while (map[i] != NULL)
	{
		copy[i] = error_malloc(sizeof(*copy[i]) * (ft_strlen(map[i]) + 1));
		if (copy[i] == NULL)
			return (free_2d_str_array_if_fails(copy, i));
		ft_strlcpy(copy[i], map[i], ft_strlen(map[i]) + 1);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	find_player_location(int *x, int *y, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
