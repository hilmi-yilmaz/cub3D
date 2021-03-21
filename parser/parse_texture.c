/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/21 15:30:07 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>

/* User defined header files */
#include "../cub3d.h"

int parse_textures(t_info *info, char *line)
{
    if (*line == 'N')
        fill_texture(&info->north_text, line + LEN_NO);
    else if (*line == 'S' && *(line + 1) == 'O')
        fill_texture(&info->south_text, line + LEN_SO);
    else if (*line == 'W')
        fill_texture(&info->west_text, line + LEN_WE);
    else if (*line == 'E')
        fill_texture(&info->east_text, line + LEN_EA);
    else if (*line == 'S')
        fill_texture(&info->sprite_text, line + LEN_S);
    return (0);
}

int fill_texture(char **texture, char *line)
{
    int i;

    i = skip_chr(line, ' ');
    *texture = ft_strdup(line + i);
    if (*texture == NULL)
        return (-1);
    return (0);
}