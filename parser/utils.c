/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/13 14:04:17 by hyilmaz       ########   odam.nl         */
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

// int check_map(char **map)
// {
//     // Using the flood_fill approach

// }

// int flood_fill(int x, int y, char **map)
// {
//     if (x < 0 || x > ft_strlen(map[y]) || y < 0 || y > ft_arrlen(map))
//         return (0);
//     else if (map[x][y] == '1')
//         return (1);
//     return (flood_fill(x + 1, y) + flood_fill(x - 1, y) + flood_fill(x, y + 1), flood_fill(x, y - 1));
// }

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
