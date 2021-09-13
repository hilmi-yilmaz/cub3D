/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/13 17:47:42 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

void    print_parse(t_parse *parse)
{
    printf("win_width = |%d|\n", parse->win_width);
    printf("win_height = |%d|\n", parse->win_height);
    printf("north_texture = |%s|\n", parse->north_text);
    printf("south_texture = |%s|\n", parse->south_text);
    printf("west_texture = |%s|\n", parse->west_text);
    printf("east_texture = |%s|\n", parse->east_text);
    printf("Floor colour = |%d,%d,%d|\n", parse->floor_colour[0], parse->floor_colour[1], parse->floor_colour[2]);
    printf("Ceiling colour = |%d,%d,%d|\n", parse->ceiling_colour[0], parse->ceiling_colour[1], parse->ceiling_colour[2]);
}

void    print_map(t_parse *parse)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*(parse->map + i) != NULL)
    {
        printf("|");
        while (parse->map[i][j] != '\0')
        {
            printf("%c", *(*(parse->map + i) + j));
            j++;
        }
        //printf("     %d", parse->map_len[i]);
        printf("\n");
        j = 0;
        i++;
    }
}

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
			if (map[i][j] != '0' && map[i][j] != '1')
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

int check_map(char **map)
{
    int ret;
    int player_x;
    int player_y;

    find_player_location(&player_x, &player_y, map);
    printf("player_x = %d\n", player_x);
    printf("player_y = %d\n", player_y);

    ret = flood_fill(player_x, player_y, map);
    printf("ret = %d", ret);
    return (ret);

}

int flood_fill(int x, int y, char **map)
{
    printf("map[%d][%d] = %c\n", y, x, map[y][x]);
    if (x < 0 || x >= ft_strlen(map[y]) || y < 0 || y >= ft_arrlen(map) || map[y][x] == ' ')
    {
        printf("x or y out of bounds or space\n");
        return (1);
    }
    else if (map[y][x] == '1')
    {
        printf("Found a wall\n");
        return (0);
    }
    map[x][y] = '1';
    return (flood_fill(x + 1, y, map) + flood_fill(x - 1, y, map) + flood_fill(x, y + 1, map) +  flood_fill(x, y - 1, map));
}

int skip_chr(char *str, int c)
{
    int i;

    i = 0;
    while (*(str + i) == c)
        i++;
    return (i);
}

void    *error_malloc(void)
{
    printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
    return (NULL);
}
