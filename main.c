/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 11:49:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "incl/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (argc != 2)
	{
		printf("Error\nRun as: ./cub3D scene_file.cub\n");
		return (-1);
	}
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
