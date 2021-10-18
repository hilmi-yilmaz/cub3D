/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 09:39:52 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_texture.h"

static int	fill_texture(char **texture, char *line, char *text_id)
{
	int	i;

	if (ft_isspace(*line) == 0)
	{
		printf("Error\nNo space between identifier and data for %s texture.\n", \
				text_id);
		return (-1);
	}
	i = skip_chr(line, ft_isspace);
	if (*texture != NULL)
	{
		printf("Error\nDouble %s texture data.\n", text_id);
		return (-1);
	}
	*texture = ft_strdup(line + i);
	if (*texture == NULL)
	{
		printf("Error\n%s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int	parse_textures(t_parse *parse, char *line)
{
	int	ret;

	ret = 0;
	if (*line == 'N' && line[1] == 'O')
		ret = fill_texture(&parse->north_text, line + 2, "North");
	else if (*line == 'S' && line[1] == 'O')
		ret = fill_texture(&parse->south_text, line + 2, "South");
	else if (*line == 'W' && line[1] == 'E')
		ret = fill_texture(&parse->west_text, line + 2, "West");
	else if (*line == 'E' && line[1] == 'A')
		ret = fill_texture(&parse->east_text, line + 2, "East");
	if (ret == -1)
		return (-1);
	return (0);
}
