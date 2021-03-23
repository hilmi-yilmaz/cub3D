/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:17:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 20:36:07 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>

/* User defined header files */
#include "../cub3d.h"

void    info_init(t_info *info)
{
    int i;

    i = 0;
    info->win_width = UNINITIALIZED;
    info->win_height = UNINITIALIZED;
    info->north_text = NULL;
    info->south_text = NULL;
    info->west_text = NULL;
    info->east_text = NULL;
    info->sprite_text = NULL;
    while (i < RGB_DATA_COUNT)
    {
        *(info->floor_colour + i) = UNINITIALIZED;
        *(info->ceiling_colour + i) = UNINITIALIZED;
        i++;
    }
    info->map.map = NULL;
    info->map.len_element = NULL;
}