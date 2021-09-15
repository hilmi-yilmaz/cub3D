/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/15 14:45:53 by hyilmaz       ########   odam.nl         */
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

int check_map(char **map)
{
    int ret;
    int player_x;
    int player_y;
    t_recursion_management rec_man;

    player_x = -1;
    player_y = -1;
    find_player_location(&player_x, &player_y, map);
    if (player_x == -1 && player_y == -1)
    {
        printf("Error\nNo player in the map. Put a N, S, E, W character in the map.\n");
        return (-1);
    }
    recursion_management_init(&rec_man);
    ret = -1;
    while (ret != 0)
    {
        ret = flood_fill(player_x, player_y, map, &rec_man);
        rec_man.max_stack_reached = 0;
        if (rec_man.error == 1)
            break ;
    }
    printf("total recursions = %d\n", rec_man.total_recursions);
    if (rec_man.error == 1)
    {
        printf("Error\nMap is invalid. Make sure the map is surrounded by walls.\n");
        return (-1);
    }
    return (ret);

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

void    *error_malloc(void)
{
    printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
    return (NULL);
}
