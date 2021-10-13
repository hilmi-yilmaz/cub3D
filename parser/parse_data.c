/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:20:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 17:30:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_data.h"

/*
**  return 1 acts as a flag that the reading of the cub file is done
 */
static int	decision(int fd, t_parse *parse, char **line)
{
	int	r;

	r = 0;
	if ((*(*line) == 'N') || (*(*line) == 'S') || (*(*line) == 'W') \
			|| (*(*line) == 'E'))
		r = parse_textures(parse, *line);
	else if (*(*line) == 'F' || *(*line) == 'C')
		r = parse_colour(parse, *line);
	else if (*(*line) == '0' || *(*line) == '1' || *(*line) == ' ')
	{
		if (parse_map(fd, parse, line))
			return (-1);
		return (1);
	}
	else
	{
		if (*(*line) != '\0')
		{
			printf("Error\nWrong type identifier in scene file: %s\n", *line);
			r = -1;
		}
	}
	return (r);
}

/*
** ret = 1 when done reading
 */
static int	decision_wrapper(int fd, t_parse *parse, char **line)
{
	int	ret;

	ret = decision(fd, parse, line);
	if (ret == 1)
		return (0);
	if (ret == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (ret == 0)
		free(*line);
	return (ret);
}

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
		ret = decision_wrapper(fd, parse, &line);
		if (ret == -1)
		{
			return (-1);
		}
		line = NULL;
		count++;
	}
	return (0);
}
