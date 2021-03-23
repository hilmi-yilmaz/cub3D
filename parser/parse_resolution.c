/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/23 11:38:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int parse_resolution(int *win_width, int *win_height, char *line)
{
    int i;
    int check;

    i = 0;
	check = check_resolution(line);
    if (check == -1)
        return (-1);
    i = skip_chr(line, ' ');
    *win_width = ft_atoi(line + i);
    i += ft_nblen(*win_width, 10);
    *win_height = ft_atoi(line + i);
    return (0);
}

int check_resolution(char *line)
{
    int i;
    int data_count;

    i = 0;
    data_count = 0;
    while (*(line + i) != '\0')
    {
        if (ft_isdigit(*(line + i)) == 0 && *(line + i) != ' ')
        {
            printf("Error\nWrong characters found while parsing resolution data.\n");
            return (-1);
        }
        if (ft_isdigit(*(line + i)) != 0 && ft_isdigit(*(line + i + 1)) == 0)
            data_count++;
        i++;
    }
    if (data_count != RESOLUTION_DATA_COUNT)
    {   
        printf("Error\nFormat of resolution isn't correct. Give resolutions as 2 numbers for width and height.\n");
        return (-1);
    }
    return (0);
}