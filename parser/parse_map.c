/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 12:05:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/03 18:48:22 by hyilmaz       ########   odam.nl         */
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

int parse_map(int fd, t_info *info, char *line)
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
            printf("Error\nSomething went wrong reading the map\n");
            return (-1);
        }
        info->map.len_element = create_len(info, line, rows);
        if (info->map.len_element == NULL)
        {
            free(line);
            return (-1);
        }
        info->map.map = create_map(info, line, rows);
        if (info->map.map == NULL)
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
    print_map(info);
    printf("\n");
    return (0);
}

int *create_len(t_info *info, char *line, int rows)
{
    int i;
    int *new_elements_len;

    i = 0;
    new_elements_len = (int *)malloc(sizeof(int) * rows);
    if (new_elements_len == NULL)
        return (error_malloc());
    while (i < rows - 1)
    {
        *(new_elements_len + i) = *(info->map.len_element + i);
        i++;
    }
    free(info->map.len_element);
    *(new_elements_len + i) = ft_strlen(line);
    return (new_elements_len);
}

int **create_map(t_info *info, char *line, int rows)
{
    int i;
    int j;
    int **new_map;

    i = 0;
    j = 0;
    new_map = (int **)malloc(sizeof(int *) * (rows + 1));
    if (new_map == NULL)
	{
		free_info(info);
		return (error_malloc());
	}
	*(new_map + rows) = NULL;
    i = old_to_new_map(info, new_map, rows);
    if (i == -1)
		return (NULL);
	*(new_map + i) = (int *)malloc(sizeof(int) * info->map.len_element[i]);
    if (*(new_map + i) == NULL)
	{
		free_map(new_map);
        return (error_malloc());
	}
	j = 0;
    while (*(line + j) != '\0')
    {
        *(*(new_map + i) + j) = *(line + j);
        j++;
    }
    return (new_map);
}

int old_to_new_map(t_info *info, int **new_map, int rows)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < rows - 1)
    {
		*(new_map + i) = (int *)malloc(sizeof(int) * info->map.len_element[i]);
        if (*(new_map + i) == NULL)
        {
            free_map(new_map);
			free_info(info);
			error_malloc();
            return (-1);
        }
        while (j < *(info->map.len_element + i))
        {
            *(*(new_map + i) + j) = *(*(info->map.map + i) + j);
            j++;
        }
        j = 0;
        i++;
    }
    free_map(info->map.map);
    return (i);
}
