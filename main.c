/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/29 21:14:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_info  info;
	t_img	img;
    int     parse_return;
	int		img_return;

    parse_return = parse_main(&info, argv);
    if (parse_return == -1)
        return (-1);
	img_return = raycaster_main(&img, &info);
	if (parse_return == -1)
        return (-1);

	/* Free all data */
	free_info(&info);
    return (0);
}