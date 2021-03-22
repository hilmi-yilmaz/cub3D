/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:20:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 18:09:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int parse_data(int fd, t_info *info)
{
    int     res;
    int     return_val;
    char    *line;

    res = 1;
    line = NULL;
    while (res > 0)
    {
        res = get_next_line(fd, &line);
        if (*line == 'R')
            return_val = parse_resolution(&info->win_width, &info->win_height, line + 1);
        else if (*line == 'N' || (*line == 'S' && *(line + 1) == 'O') || \
                *line == 'W' || *line == 'E' || *line == 'S')
            return_val = parse_textures(info, line);
        else if (*line == 'F')
            return_val = parse_colour(info->floor_colour, line + LEN_F);
        else if (*line == 'C')
            return_val = parse_colour(info->ceiling_colour, line + LEN_C);
        else if (*line == '\0')
           ;
        else if (*line == '0' || *line == '1' || *line == '2' || *line == 'N' || \
                *line == 'S' || *line == 'E' || *line == 'W' || *line == ' ')
        {
            return_val = parse_map(fd, info, line);
            if (return_val == -1)
                return (-1);
            return (0);
        }
        else
        {
            printf("Error\nWrong type identifier in scene file or wrong element in map.\n");
            return_val = -1;
        }
        free(line);
        line = NULL;
        if (return_val == -1)
            return (-1);
    }
    return (0);
}