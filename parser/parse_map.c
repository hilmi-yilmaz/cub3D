/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 12:05:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/08/31 17:51:04 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* User defined header files */
#include "../cub3d.h"

int parse_map(int fd, t_parse *parse, char *line)
{
    int     res;
    int     rows;

    res = 1;
    rows = 1;
    while (res > 0)
    {    
        if (rows != 1)
            res = get_next_line(fd, &line);
        if (res == -1) // ------------- Also check for case that res = 0 first time in loop ---------------//
        {
            printf("Error: Something went wrong reading the map.\n");
            return (-1);
        }
        printf("line = %s\n", line);
        if (*line == '\0')
            break ;
        parse->map = create_map(parse, line, rows);
        if (parse->map == NULL)
        {
            free(line);
            return (-1);
        }
        free(line);
        line = NULL;
        rows++;
    }
    // Print the map
    printf("\n");
    print_map(parse);
    printf("\n");
    return (0);
}

char **create_map(t_parse *parse, char *line, int rows)
{
    int i;
    int j;
    char **new_map;

    i = 0;
    j = 0;
    new_map = malloc(sizeof(*new_map) * (rows + 1));
    if (new_map == NULL)
	{
		free_parse(parse);
		return (error_malloc());
	}
	new_map[rows] = NULL;
    i = old_to_new_map(parse, new_map, rows);
    if (i == -1)
		return (NULL);
	new_map[i] = malloc(sizeof(*(*(new_map + i))) * (ft_strlen(line) + 1));
    if (*(new_map + i) == NULL)
	{
		free_map(new_map);
        return (error_malloc());
	}
    ft_strlcpy(new_map[i], line, ft_strlen(line) + 1);
    return (new_map);
}

int old_to_new_map(t_parse *parse, char **new_map, int rows)
{
    int i;

    i = 0;
    while (i < rows - 1)
    {
		new_map[i] = malloc(sizeof(*(*(new_map + i))) * (ft_strlen(parse->map[i]) + 1));
        if (new_map[i] == NULL)
        {
            free_map(new_map);
			free_parse(parse);
			error_malloc();
            return (-1);
        }
        ft_strlcpy(new_map[i], parse->map[i], ft_strlen(parse->map[i]) + 1);
        i++;
    }
    free_map(parse->map);
    return (i);
}
