/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/11 10:06:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int		parse_return;
	int		raycaster_return;

	parse_return = parse_main(&data.parse, argv);
	if (parse_return == -1)
	{
		free_parse(&data.parse);
		return (-1);
	}
	raycaster_return = raycaster_main(&data);
	if (raycaster_return == -1)
	{
		free_parse(&data.parse);
		free_player(&data.player);
		return (-1);
	}
	else if (raycaster_return == -2)
	{
		free_all(&data);
		return (-1);
	}
	free_all(&data);
	return (0);
}
