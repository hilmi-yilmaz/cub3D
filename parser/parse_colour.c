/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/20 10:57:24 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_colour.h"

static int	error_colour(void)
{
	printf("Error\nFormat of colour data isn't correct.\n");
	printf("Give 3 numbers for R, G and B \
separated by kommas and 1 or more spaces.\n");
	return (-1);
}

static int	loop_wrapper(int *colour_array, char *line, int *i, int *j)
{
	if (*j != 0)
	{
		*i += skip_chr(line + *i, ft_isspace);
		if (line[*i] != ',')
			return (error_colour());
		*i += 1;
	}
	*i += skip_chr(line + *i, ft_isspace);
	if (ft_isdigit(line[*i]) == 0)
		return (error_colour());
	if (colour_array[*j] != UNINIT)
	{
		printf("Error\nDouble colour data.\n");
		return (-1);
	}
	colour_array[*j] = ft_atoi(line + *i);
	if (colour_array[*j] < 0 || colour_array[*j] > 255)
	{
		printf("Error\nR, G, B values should be between 0 and 255.\n");
		return (-1);
	}
	*i += ft_nblen(colour_array[*j], 10);
	return (0);
}

static int	fill_colour(int *colour_array, char *line)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (j < RGB_DATA_COUNT)
	{
		ret = loop_wrapper(colour_array, line, &i, &j);
		if (ret == -1)
			return (-1);
		j++;
	}
	i += skip_chr(line + i, ft_isspace);
	if (line[i] != '\0')
		return (error_colour());
	return (0);
}

int	parse_colour(t_parse *parse, char *line)
{
	int	i;
	int	j;
	int	check;
	int	*selected_arr;

	i = 0;
	j = 0;
	if (*line == 'F')
		selected_arr = parse->floor_colour;
	else
		selected_arr = parse->ceiling_colour;
	line++;
	if (ft_isspace(*line) == 0)
	{
		printf("Error\nNo space between identifier and data for colour.\n");
		return (-1);
	}
	check = fill_colour(selected_arr, line);
	if (check == -1)
		return (-1);
	return (0);
}
