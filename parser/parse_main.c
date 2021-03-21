/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/21 20:22:51 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h> // for NULL
#include <fcntl.h> // for open
#include <stdio.h> // for printf, perror
#include <unistd.h> // for read, write, close
#include <stdlib.h> //for malloc, free, exit
#include <string.h> //strerror

/* User defined header files */
#include "../cub3d.h"

int parse_main(t_info *info, char **argv)
{
    int     fd;
    int     parse_return;
    int     close_return;

    fd = open(*(argv + 1), O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nSomething went wrong opening \"%s\"\n", *(argv + 1));
        perror(NULL);
        exit(1);
    }
    info_init(info);
    parse_return = parse_data(fd, info);
    if (parse_return == -1)
    {
        free_info(info);
        return (-1);
    }
    print_info(info);
    free_info(info);
    close_return = close(fd);
    if (close_return == -1)
    {
        printf("Error closing %s\n", *(argv + 1));
        exit (1);
    }
    return (0);
}