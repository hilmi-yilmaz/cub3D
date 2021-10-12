/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 12:05:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:04:38 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* User defined header files */
#include "parse_map.h"

static int	old_to_new_map(t_parse *parse, char **new_map, int rows)
{
	int	i;

	i = 0;
	while (i < rows - 1)
	{
		new_map[i] = error_malloc(sizeof(*new_map[i]) * \
								(ft_strlen(parse->map[i]) + 1));
		if (new_map[i] == NULL)
		{
			free_map(new_map);
			free_parse(parse);
			return (-1);
		}
		ft_strlcpy(new_map[i], parse->map[i], ft_strlen(parse->map[i]) + 1);
		i++;
	}
	free_map(parse->map);
	return (i);
}

static char	**create_map(t_parse *parse, char *line, int rows)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = error_malloc(sizeof(*new_map) * (rows + 1));
	if (new_map == NULL)
	{
		free_parse(parse);
		return (NULL);
	}
	new_map[rows] = NULL;
	i = old_to_new_map(parse, new_map, rows);
	if (i == -1)
		return (NULL);
	new_map[i] = error_malloc(sizeof(*new_map[i]) * (ft_strlen(line) + 1));
	if (new_map[i] == NULL)
	{
		free_map(new_map);
		return (NULL);
	}
	ft_strlcpy(new_map[i], line, ft_strlen(line) + 1);
	return (new_map);
}

static void	free_and_null(char *line)
{
	free(line);
	line = NULL;
}

static int	loop_wrapper(int fd, t_parse *parse, char *line, int rows)
{
	int res;

	res = 1;
	if (rows != 1)
		res = get_next_line(fd, &line);
	if (res == -1)
	{
		printf("Error\nSomething went wrong reading the map.\n");
		return (-1);
	}
	if (*line == '\0')
	{
		free_and_null(line);
		return (0);
	}
	parse->map = create_map(parse, line, rows);
	//parse->map = NULL;
	if (parse->map == NULL)
	{
		//free_and_null(line);
		return (-1);
	}
	free_and_null(line);
	return (res);
}

int	parse_map(int fd, t_parse *parse, char *line)
{
	int	res;
	int	rows;

	res = 1;
	rows = 1;
	while (res > 0)
	{
		// if (rows != 1)
		// 	res = get_next_line(fd, &line);
		// if (res == -1)
		// {
		// 	printf("Error\nSomething went wrong reading the map.\n");
		// 	return (-1);
		// }
		// if (*line == '\0')
		// {
		// 	free_and_null(line);
		// 	break ;
		// }
		// parse->map = create_map(parse, line, rows);
		// if (parse->map == NULL)
		// {
		// 	free_and_null(line);
		// 	return (-1);
		// }
		// free_and_null(line);
		res = loop_wrapper(fd, parse, line, rows);
		if (res == -2)
			break ;
		else if (res == -1)
			return (-1);
		else if (res == 0)
			break ;
		rows++;
	}
	return (0);
}
