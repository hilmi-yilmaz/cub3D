/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/20 11:47:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int parse_colour(int *colour_array, char *line)
{
    int i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	if (*line != ' ')
	{
		printf("Error\nNo space between identifier and data for colour.\n");
		return (-1);
	}
	check = fill_colour(colour_array, line);
	if (check == -1)
		return (-1);
	return (0);
}

int	fill_colour(int *colour_array, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < RGB_DATA_COUNT)
	{
		if (j != 0)
		{
			i += skip_chr(line + i, ' ');
			//printf("line + i = %s\n", line + i);
			if (line[i] != ',')
				return (error_colour());
			i++;
		}
		i += skip_chr(line + i, ' ');
		if (ft_isdigit(line[i]) == 0)
			return (error_colour());
		if (colour_array[j] != UNINIT)
		{
			printf("Error\nDouble colour data.\n");
			return (-1);
		}
		colour_array[j] = ft_atoi(line + i);
		i += ft_nblen(colour_array[j], 10);
		j++;
	}
	i += skip_chr(line + i, ' ');
	if (line[i] != '\0')
        return (error_colour());
	return (0);
}