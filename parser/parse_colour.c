/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:22:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/21 20:15:39 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int parse_colour(int *colour_array, char *line)
{
    int i;
    int j;
    int check;

    check = check_colour(line);
    if (check == -1)
        return (-1);
    i = skip_chr(line, ' ');
    j = 0;
    while (j < RGB_DATA_COUNT)
    {
        *(colour_array + j) = ft_atoi(line + i);
        i += ft_nblen(*(colour_array + j), 10);
        if (j == RGB_DATA_COUNT - 1)
            break ;
        while (ft_isdigit(*(line + i)) == 0)
            i++;
        j++;
    }
    return (0);
}

int check_colour(char *line)
{
    int i;
    int data_count;

    i = 0;
    data_count = 0;
    while (*(line + i) != '\0')
    {
        if (*(line + i) != ',' && *(line + i) != ' ' && ft_isdigit(*(line + i)) == 0)
        {
            printf("Error\nWrong characters found while parsing colour data.\n");
            return (-1);
        }
        if (ft_isdigit(*(line + i)) != 0 && ft_isdigit(*(line + i + 1)) == 0)
            data_count++;
        i++;
    }
    if (data_count != RGB_DATA_COUNT)
    {
        printf("Error\nFormat of colour data isn't correct. ");
        printf("Give 3 numbers for R, G and B separated by kommas and 1 or more spaces.\n");
        return (-1);
    }
    return (0);
}