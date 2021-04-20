/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/20 14:23:16 by hyilmaz       ########   odam.nl         */
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

    fd = open(*(argv + 1), O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nSomething went wrong opening \"%s\": %s\n", *(argv + 1), strerror(errno));
        exit(1);
    }
    parse_init(parse);
    parse_return = parse_data(fd, parse);
    if (parse_return == -1)
    {
        //free_parse(parse);
        return (-1);
    }
	check = check_data_completeness(parse);
	if (check == -1)
	{
		free_parse(parse);
		return (-1);
	}
    print_parse(parse);
    //free_parse(parse);
    close_return = close(fd);
    if (close_return == -1)
    {
        printf("Error\nSomething went wrong closing \"%s\": %s\n", *(argv + 1), strerror(errno));
		//Free all data
        exit (1);
    }
    return (0);
}

/* This function checks whether the data file was complete (no missing data) */
int	check_data_completeness(t_parse *parse)
{
	int i;
	int	error;

	i = 0;
	error = 0;
	if (parse->win_width == UNINITIALIZED || parse->win_height == UNINITIALIZED)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing resolution data.\n");
		error = -1;
	}
	if (parse->north_text == NULL || parse->south_text == NULL || \
		parse->west_text == NULL || parse->east_text == NULL || \
		parse->sprite_text == NULL)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing texture data.\n");
		error = -1;
	}
    while (i < RGB_DATA_COUNT)
    {
        if (*(parse->floor_colour + i) == UNINITIALIZED || \
			*(parse->ceiling_colour + i) == UNINITIALIZED)
		{
			if (error != -1)
				printf("Error\n");
			printf("Missing floor/ceiling data.\n");
			error = -1;
			break ;
		}
        i++;
    }
	if (parse->map == NULL)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing map data.\n");
		error = -1;
	}
	return (error);
}