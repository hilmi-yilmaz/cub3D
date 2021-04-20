/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/19 13:00:58 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_info  info;
	t_img	img;
	t_map	map;
    int     parse_return;
	int		img_return;

    printf("sizeof(t_info) = %lu\n", sizeof(t_info));
	printf("sizeof(win_width) = %lu\n", sizeof(info.win_width));
	printf("sizeof(north_text) = %lu\n", sizeof(info.north_text));
	printf("sizeof(t_map) = %lu\n", sizeof(t_map));
	return (0);
	
	parse_return = parse_main(&info, argv);
    if (parse_return == -1)
        return (-1);
	printf("\n--------------------------------------------------------------------------------------\n\n");
	img_return = raycaster_main(&img, &info);
	if (parse_return == -1)
        return (-1);

	/* Free all data */
	free_info(&info);
    return (0);
}