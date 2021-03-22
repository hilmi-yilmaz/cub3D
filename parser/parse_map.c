/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 12:05:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 18:24:04 by hyilmaz       ########   odam.nl         */
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

/* Prototypes */
void    free_map(t_info *info, int rows);

/* --------------------------------------------------------------------------------------- */
/* KEEP IN MIND THAT IF ONE ALLOCATION FAILS MIDWAY, I HAVE TO FREE ALL ALLOCATIONS BEFORE */
/* --------------------------------------------------------------------------------------- */

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
            printf("Error\nSomething went wrong while reading the map\n");
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
        // printf("\n");
        // print_map(info);
        // printf("\n");
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
    {
        printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
        free(info->map.len_element);
        free_map(info, rows - 1);
        return (NULL);
    }
    while (i < rows - 1)
    {
        *(new_elements_len + i) = *(info->map.len_element + i);
        i++;
    }
    if (rows > 1)
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
        printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
        free(info->map.len_element);
        free_map(info, rows - 1);
        return (NULL);       
    }
    *(new_map + rows) = NULL;
    while (i < rows - 1)
    {
        *(new_map + i) = (int *)malloc(sizeof(int) * info->map.len_element[i]);
        if (*(new_map + i) == NULL)
        {
            printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
            free_new_map(new_map, i);
            free(info->map.len_element);
            return (NULL);
        }
        while (j < *(info->map.len_element + i))
        {
            *(*(new_map + i) + j) = *(*(info->map.map + i) + j);
            j++;
        }
        j = 0;
        i++;
    }
    if (rows > 1)
        free_map(info, rows - 1);
    *(new_map + i) = (int *)malloc(sizeof(int) * info->map.len_element[i]);
    if (*(new_map + i) == NULL)
    {
        printf("Error\nMalloc failed: %s\nFreeing all dynamically allocated memory...", strerror(errno));
        free_new_map(new_map, rows - 1);
        free(info->map.len_element);
        return (NULL);
    }
    j = 0;
    while (*(line + j) != '\0')
    {
        *(*(new_map + i) + j) = *(line + j);
        j++;
    }
    return (new_map);
}

void    free_map(t_info *info, int rows)
{
    int i;

    i = 0;
    while (i < rows)
    {
        free(*(info->map.map + i));
        i++;
    }
    free(info->map.map);
}

void    free_new_map(int **new_map, int rows)
{
    int i;

    i = 0;
    while (i < rows)
    {
        free(*(new_map + i));
        i++;
    }
    free(new_map);
}
