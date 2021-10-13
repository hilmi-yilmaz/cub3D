/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:02:54 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 13:13:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_free.h"

/* This function frees the textures and map */
void	free_parse(t_parse *parse)
{
	free_textures(parse);
	free_map(parse->map);
}

void	free_textures(t_parse *parse)
{
	free(parse->north_text);
	free(parse->south_text);
	free(parse->west_text);
	free(parse->east_text);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i] != NULL)
		{
			free(map[i]);
			i++;
		}
	}
	free(map);
}

void	*free_2d_str_array_if_fails(char **copy, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(copy[j]);
		j++;
	}
	free(copy);
	return (NULL);
}
