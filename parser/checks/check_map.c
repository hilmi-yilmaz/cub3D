/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:06:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/09 11:53:04 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "check_map.h"

/*
**
** Returns 0 if all went oke, if map invalid, sets rec_man->error = 1.
**
 */

static int	recursion_management(t_recursion_management *rec_man, \
								int *x, int *y, char **map)
{
	if (rec_man->max_stack_reached == 1)
	{
		return (-1);
	}
	if (rec_man->i == STACK_MAX)
	{
		rec_man->max_stack_reached = 1;
		rec_man->i = 0;
		return (-1);
	}
	if (rec_man->i == 0 && rec_man->total_recursions != 0)
	{
		*x = rec_man->save_x;
		*y = rec_man->save_y;
		map[*y][*x] = '0';
	}
	rec_man->total_recursions++;
	rec_man->i++;
	return (0);
}

static int	flood_fill(int x, int y, char **map, \
						t_recursion_management *rec_man)
{
	if (recursion_management(rec_man, &x, &y, map))
		return (-1);
	if (x < 0 || y < 0 || y >= ft_str_arr_len(map) || \
		x >= (int)ft_strlen(map[y]) || ft_isspace(map[y][x]) != 0)
	{
		rec_man->error = 1;
		return (1);
	}
	else if (map[y][x] == '1')
		return (0);
	else if (map[y][x] == '0')
	{
		rec_man->save_x = x;
		rec_man->save_y = y;
	}
	map[y][x] = '1';
	return (flood_fill(x + 1, y, map, rec_man) + \
			flood_fill(x - 1, y, map, rec_man) + \
			flood_fill(x, y + 1, map, rec_man) + \
			flood_fill(x, y - 1, map, rec_man) + \
			flood_fill(x - 1, y + 1, map, rec_man) + \
			flood_fill(x + 1, y + 1, map, rec_man) + \
			flood_fill(x - 1, y - 1, map, rec_man) + \
			flood_fill(x + 1, y - 1, map, rec_man));
}

static int	managed_flood_fill(int player_x, int player_y, char **map, \
						t_recursion_management *rec_man)
{
	int	ret;

	ret = -1;
	while (ret != 0)
	{
		ret = flood_fill(player_x, player_y, map, rec_man);
		rec_man->max_stack_reached = 0;
		if (rec_man->error == 1)
			break ;
	}
	return (ret);
}

static int	check_wrong_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && \
				map[i][j] != 'W' && map[i][j] != 'E' && \
				map[i][j] != '1' && map[i][j] != '0' && \
				ft_isspace(map[i][j]) == 0)
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_map(char **map)
{
	int						ret;
	int						player_x;
	int						player_y;
	t_recursion_management	rec_man;

	player_x = -1;
	player_y = -1;
	if (find_player_location(&player_x, &player_y, map))
	{
		printf("Error\nUse 1 player in the game.\n");
		return (-1);
	}
	if (check_wrong_chars(map))
	{
		printf("Error\nWrong elements found in the map.\n");
		return (-1);
	}
	recursion_management_init(&rec_man);
	ret = managed_flood_fill(player_x, player_y, map, &rec_man);
	if (rec_man.error == 1)
	{
		printf("Error\nMap is invalid. \
Make sure the map is surrounded by walls.\n");
		return (-1);
	}
	return (ret);
}
