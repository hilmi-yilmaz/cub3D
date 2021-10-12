/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 19:12:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ret = parse_main(&data.parse, argv);
	if (ret == -1)
	{
		free_parse(&data.parse);
		return (-1);
	}
	ret = raycaster_main(&data);
	if (ret == -1)
	{
		free_all(&data);
		return (-1);
	}
	free_all(&data);
	return (0);
}
