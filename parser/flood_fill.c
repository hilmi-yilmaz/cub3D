/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:46:53 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/11 11:50:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* User defined header files */
#include "../cub3d.h"

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

int	flood_fill(int x, int y, char **map, t_recursion_management *rec_man)
{
	if (recursion_management(rec_man, &x, &y, map))
		return (-1);
	if (x < 0 || y < 0 || y >= ft_str_arr_len(map) || \
		x >= ft_strlen(map[y]) || map[y][x] == ' ')
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
