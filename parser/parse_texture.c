/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/13 15:47:39 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

int parse_textures(t_parse *parse, char *line)
{
    int ret;

	if (*line == 'N')
        ret = fill_texture(&parse->north_text, line + LEN_NO, "North");
    else if (*line == 'S')
        ret = fill_texture(&parse->south_text, line + LEN_SO, "South");
    else if (*line == 'W')
        ret = fill_texture(&parse->west_text, line + LEN_WE, "West");
    else if (*line == 'E')
        ret = fill_texture(&parse->east_text, line + LEN_EA, "East");
    if (ret == -1)
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
    if (*texture != NULL)
    {
        printf("Error\nDouble %s texture data.\n", text_id);
        return (-1);
    }
    *texture = ft_strdup(line + i); /* XXXXXXXXXX If a lot of spaces after texture, memory is allocated --> fix XXXXXXXXXX */
    if (*texture == NULL)
	{
		printf("Error\n%s\n", strerror(errno));
        return (-1);
	}
	return (0);
}