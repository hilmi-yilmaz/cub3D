/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_data_completeness.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 11:54:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 11:51:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "check_data_completeness.h"

static void	texture_completeness(t_parse *parse, int *error)
{
	if (parse->north_text == NULL || parse->south_text == NULL || \
		parse->west_text == NULL || parse->east_text == NULL)
	{
		if (*error != -1)
			printf("Error\n");
		printf("Missing texture data. \
Make sure to add NO, SO, WE and EA textures.\n");
		*error = -1;
	}
}

static void	colour_completeness(t_parse *parse, int *error)
{
	int	i;

	i = 0;
	while (i < RGB_DATA_COUNT)
	{
		if (*(parse->floor_colour + i) == UNINIT || \
			*(parse->ceiling_colour + i) == UNINIT)
		{
			if (*error != -1)
				printf("Error\n");
			printf("Missing floor/ceiling data.\n");
			*error = -1;
			break ;
		}
		i++;
	}
}

/* This function checks whether the data file was complete (no missing data) */
int	check_data_completeness(t_parse *parse)
{
	int	error;

	error = 0;
	texture_completeness(parse, &error);
	colour_completeness(parse, &error);
	if (parse->map == NULL)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing map data.\n");
		error = -1;
	}
	return (error);
}