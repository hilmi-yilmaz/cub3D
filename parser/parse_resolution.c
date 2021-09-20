/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/20 12:43:55 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int parse_resolution(int *win_width, int *win_height, char *line)
{
    int i;
    int ret;

	if (*line != ' ')
	{
		printf("Error: No space between identifier and data for resolution.\n");
		return (-1);
	}
	ret = check_resolution(line);
    if (ret == -1)
        return (-1);
    i = skip_chr(line, ' ');
    *win_width = ft_atoi(line + i);
    i += ft_nblen(*win_width, 10);
    *win_height = ft_atoi(line + i);
    return (0);
}