/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/08/31 16:33:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_data	data;
    int     parse_return;
	int		img_return;
	
	parse_return = parse_main(&data.parse, argv);
    if (parse_return == -1)
        return (-1);
	//print_parse(&data.parse);
	printf("\n--------------------------------------------------------------------------------------\n\n");
	img_return = raycaster_main(&data);
	if (parse_return == -1)
        return (-1);

	/* Free all data */
	free_parse(&data.parse);
    return (0);
}