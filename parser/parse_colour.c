/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/20 12:58:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>

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
			if (*(line + i) != ',')
				return (error_colour());
			i++;
		}
		i += skip_chr(line + i, ' ');
		if (ft_isdigit(*(line + i)) == 0)
			return (error_colour());
		*(colour_array + j) = ft_atoi(line + i);
		i += ft_nblen(*(colour_array + j), 10);	
		j++;
	}
	i += skip_chr(line + i, ' ');
	if (*(line + i) != '\0')
        return (error_colour());
	return (0);
}

int	error_colour(void)
{
	printf("Error\nFormat of colour data isn't correct.\n");
	printf("Give 3 numbers for R, G and B separated by kommas and 1 or more spaces.\n");
	return (-1);
}