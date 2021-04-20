/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:17:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/20 16:25:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>

/* User defined header files */
#include "../cub3d.h"

void    parse_init(t_parse *parse)
{
    int i;

    i = 0;
    parse->win_width = UNINITIALIZED;
    parse->win_height = UNINITIALIZED;
    parse->north_text = NULL;
    parse->south_text = NULL;
    parse->west_text = NULL;
    parse->east_text = NULL;
    parse->sprite_text = NULL;
    while (i < RGB_DATA_COUNT)
    {
        *(parse->floor_colour + i) = UNINITIALIZED;
        *(parse->ceiling_colour + i) = UNINITIALIZED;
        i++;
    }
    parse->map = NULL;
}