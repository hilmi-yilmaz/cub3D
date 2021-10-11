/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/11 13:14:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

static int	close_file(int fd, char *filename)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
	{
		printf("Error\nSomething went wrong closing \
\"%s\": %s\n", filename, strerror(errno));
		return (-1);
	}
	return (0);
}

int	parse_main(t_parse *parse, char **argv)
{
	int		fd;
	int		parse_return;
	int		check;
	char	**cpy_map;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nSomething went wrong opening \
\"%s\": %s\n", *(argv + 1), strerror(errno));
		return (-1);
	}
	parse_init(parse);
	if (parse_data(fd, parse) || check_data_completeness(parse))
		return (-1);
	cpy_map = copy_map(parse->map);
	if (check_map(cpy_map))
	{
		free_map(cpy_map);
		return (-1);
	}
	free_map(cpy_map);
	if (close_file(fd, argv[1]))
		return (-1);
	return (0);
}
