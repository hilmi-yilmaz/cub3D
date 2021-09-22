/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/09/22 12:35:06 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h> // for NULL
#include <fcntl.h> // for open
#include <stdio.h> // for printf, perror
#include <unistd.h> // for read, write, close
#include <stdlib.h> //for malloc, free, exit
#include <string.h> //strerror
#include <errno.h> //errno

/* User defined header files */
#include "../cub3d.h"

int parse_main(t_parse *parse, char **argv)
{
    int     fd;
    int     parse_return;
	int		check;
    int     close_return;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error\n%s (%s)\n", argv[1], strerror(errno));
        return (-1);
    }
    parse_init(parse);
    parse_return = parse_data(fd, parse);
    if (parse_return == -1)
        return (-1);
	check = check_data_completeness(parse);
	if (check == -1)
		return (-1);
    print_parse(parse);
    char **cpy_map = copy_map(parse->map);
	check = check_map(cpy_map);
    free_map(cpy_map);
	if (check == -1)
		return (-1);
    close_return = close(fd);
    if (close_return == -1)
    {
        printf("Error\nSomething went wrong closing \"%s\": %s\n", *(argv + 1), strerror(errno));
		return (-1);
    }
    return (0);
}