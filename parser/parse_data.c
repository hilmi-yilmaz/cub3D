/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:20:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/10 13:28:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int	parse_data(int fd, t_parse *parse)
{
	int		res;
	int		ret;
	int		count;
	char	*line;

    res = 1;
	ret = 0;
	count = 0;
    line = NULL;
    while (res > 0)
    {
        res = get_next_line(fd, &line);
		if (res == 0 && count == 0 && *line == '\0')
		{
			printf("Error\nThe scene file is empty.\n");
			free(line);
			return (-1);
		}
        ret = decision(fd, parse, line);
        if (ret == 1)
            return (0);
        if (ret == -1)
        {
            free(line);
            line = NULL;
            return (-1);
        }
        if (ret != 1)
            free(line);
        line = NULL;
		count++;
    }
    return (0);
}

int decision(int fd, t_parse *parse, char *line)
{
    int ret;

    if (*line == 'R')
            ret = parse_resolution(&parse->win_width, &parse->win_height, line + LEN_R); /* No allocation in parse_resolution */
    else if ((*line == 'N' && *(line + 1) == 'O') || (*line == 'S' && *(line + 1) == 'O') || (*line == 'W' && *(line + 1) == 'E') || (*line == 'E' && *(line + 1) == 'A'))
        ret = parse_textures(parse, line); /* Allocation happens */
    else if (*line == 'F')
        ret = parse_colour(parse->floor_colour, line + LEN_F); /* No allocation */
    else if (*line == 'C')
        ret = parse_colour(parse->ceiling_colour, line + LEN_C); /* No allocation */
    else if (*line == '0' || *line == '1' ||  *line == ' ')
    {
        ret = parse_map(fd, parse, line); /* Allocation happens */
        if (ret == -1)
            return (-1);
        return (1); // 1 acts as a flag that the reading of the cub file is done
    }
    else
    {
        if (*line != '\0')
            printf("Error\nWrong type identifier in scene file or wrong starting element in map:\n%s\n", line);
		ret = -1;
    }
    if (ret == -1)
        return (-1);
    return (0);
}
