/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:06:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_resolution.h"

static int	check_resolution(char *line)
{
	int	i;
	int	data_count;

	i = 0;
	data_count = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ')
		{
			printf("Error\nWrong characters in resolution data.\n");
			return (-1);
		}
		if (ft_isdigit(line[i]) != 0 && ft_isdigit(line[i + 1]) == 0)
			data_count++;
		i++;
	}
	if (data_count != RESOLUTION_DATA_COUNT)
	{
		printf("Error\nFormat of resolution isn't correct. \
Give resolutions as 2 numbers for width and height.\n");
		return (-1);
	}
	return (0);
}

int	parse_resolution(int *win_width, int *win_height, char *line)
{
	int	i;
	int	ret;

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
