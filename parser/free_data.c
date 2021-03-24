/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 16:02:54 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/24 20:38:28 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

/* This function frees the textures and map */
void    free_info(t_info *info)
{
	free_textures(info);
	free_map(info->map.map);
	free(info->map.len_element);
}

void	free_textures(t_info *info)
{
    free(info->north_text);
    free(info->south_text);
    free(info->west_text);
    free(info->east_text);
    free(info->sprite_text);
}

void	free_map(int **map)
{
	int	i;

	i = 0;
    if (map != NULL)
    {
        while (*(map + i) != NULL)
        {
            free(*(map + i));
            i++;
        }
    }
    free(map);
}

void	free_len_elements(t_map map)
{
	free(map.len_element);
}