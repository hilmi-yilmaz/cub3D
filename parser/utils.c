/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/20 11:53:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

void    find_player_location(int *x, int *y, char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
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

/*
**
** Returns 0 if all went oke, if map invalid, sets rec_man->error = 1.
**
 */

int flood_fill(int x, int y, char **map, t_recursion_management *rec_man)
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
        x = rec_man->save_x;
        y = rec_man->save_y;
        map[y][x] = '0';
    }
    rec_man->total_recursions++;
    rec_man->i++;
    if (x < 0 || y < 0 || y >= ft_arrlen(map) || x >= ft_strlen(map[y]) || map[y][x] == ' ')
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
    return (flood_fill(x + 1, y, map, rec_man) + flood_fill(x - 1, y, map, rec_man) + flood_fill(x, y + 1, map, rec_man) +  flood_fill(x, y - 1, map, rec_man));
}

int skip_chr(char *str, int c)
{
    int i;

    i = 0;
    while (*(str + i) == c)
        i++;
    return (i);
}
