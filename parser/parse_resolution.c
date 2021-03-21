/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 15:21:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/21 16:27:00 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* User defined header files */
#include "../cub3d.h"

int parse_resolution(int *win_width, int *win_height, char *line)
{
    int i;
    int check;

    check = check_resolution(line);
    if (check == -1)
        return (-1);
    i = 0;
    while (*(line + i) != '\0')
    {
        if (*(line + i) != ' ' && ft_isdigit(*(line + i)) == 0)
            return (-1);
        i++;
    }
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
            return (-1);
        if (ft_isdigit(*(line + i)) != 0 && ft_isdigit(*(line + i + 1)) == 0)
            data_count++;
        i++;
    }
    if (data_count != RESOLUTION_DATA_COUNT)
        return (-1);
    return (0);
}