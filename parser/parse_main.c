/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/20 10:53:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_main.h"

static int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		printf("Error\nSomething went wrong opening \
\"%s\": %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

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

static int	check_cub_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len <= 4 || (file[len - 1] != 'b' || file[len - 2] != 'u' || \
		file[len - 3] != 'c' || file[len - 4] != '.'))
	{
		printf("Error\nScene file has no extension .cub\n");
		return (-1);
	}
	return (0);
}

int	parse_main(t_parse *parse, char **argv)
{
	int		fd;
	char	**cpy_map;

	if (check_cub_extension(argv[1]))
		return (-1);
	fd = open_file(argv[1]);
	if (fd == -1)
		return (-2);
	parse_init(parse);
	if (parse_data(fd, parse) || check_data_completeness(parse))
		return (-1);
	cpy_map = copy_map(parse->map);
	if (cpy_map == NULL)
		return (-1);
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
