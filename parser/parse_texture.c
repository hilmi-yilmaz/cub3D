/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 17:58:32 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>

/* User defined header files */
#include "../cub3d.h"

int parse_textures(t_info *info, char *line)
{
    int res;

    if (*line == 'N')
        res = fill_texture(&info->north_text, line + LEN_NO);
    else if (*line == 'S' && *(line + 1) == 'O')
        res = fill_texture(&info->south_text, line + LEN_SO);
    else if (*line == 'W')
        res = fill_texture(&info->west_text, line + LEN_WE);
    else if (*line == 'E')
        res = fill_texture(&info->east_text, line + LEN_EA);
    else if (*line == 'S')
        res = fill_texture(&info->sprite_text, line + LEN_S);
    if (res == -1)
        return (-1);
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