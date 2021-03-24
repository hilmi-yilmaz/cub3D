/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/23 14:06:57 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

int parse_textures(t_info *info, char *line)
{
    int res;

	if (*line == 'N')
        res = fill_texture(&info->north_text, line + LEN_NO, "North");
    else if (*line == 'S' && *(line + 1) == 'O')
        res = fill_texture(&info->south_text, line + LEN_SO, "South");
    else if (*line == 'W')
        res = fill_texture(&info->west_text, line + LEN_WE, "West");
    else if (*line == 'E')
        res = fill_texture(&info->east_text, line + LEN_EA, "East");
    else if (*line == 'S')
        res = fill_texture(&info->sprite_text, line + LEN_S, "Sprite");
    if (res == -1)
        return (-1);
    return (0);
}

int fill_texture(char **texture, char *line, char *text_id)
{
    int i;

    if (*line != ' ')
	{
		printf("Error\nNo space between identifier and data for %s texture.\n", text_id);
		return (-1);
	}
	i = skip_chr(line, ' ');
    *texture = ft_strdup(line + i); /* XXXXXXXXXX If a lot of spaces after texture, memory is allocated --> fix XXXXXXXXXX */
    if (*texture == NULL)
	{
		printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
        return (-1);
	}
	return (0);
}