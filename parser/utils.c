/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:23:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 16:19:20 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void    print_info(t_info *info)
{
    printf("win_width = |%d|\n", info->win_width);
    printf("win_height = |%d|\n", info->win_height);
    printf("north_texture = |%s|\n", info->north_text);
    printf("south_texture = |%s|\n", info->south_text);
    printf("west_texture = |%s|\n", info->west_text);
    printf("east_texture = |%s|\n", info->east_text);
    printf("sprite_texture = |%s|\n", info->sprite_text);
    printf("Floor colour = |%d,%d,%d|\n", info->floor_colour[0], info->floor_colour[1], info->floor_colour[2]);
    printf("Ceiling colour = |%d,%d,%d|\n", info->ceiling_colour[0], info->ceiling_colour[1], info->ceiling_colour[2]);
}

void    print_map(t_info *info)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*(info->map.map + i) != NULL)
    {
        while (j < info->map.len_element[i])
        {
            printf("%c", *(*(info->map.map + i) + j));
            j++;
        }
        //printf("     %d", info->map.len_element[i]);
        printf("\n");
        j = 0;
        i++;
    }
}

int skip_chr(char *str, int c)
{
    int i;

    i = 0;
    while (*(str + i) == c)
        i++;
    return (i);
}

void    free_info(t_info *info)
{
    int i;

    i = 0;
    free(info->north_text);
    free(info->south_text);
    free(info->west_text);
    free(info->east_text);
    free(info->sprite_text);
    while (*(info->map.map + i) != NULL)
    {
        free(*(info->map.map + i));
        i++;
    }
    free(info->map.map);
    free(info->map.len_element);
}

void    free_and_exit(t_info *info)
{
    free_info(info);
    exit(1);
}