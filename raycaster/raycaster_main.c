/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:14:08 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:11:05 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_main.h"

static int	set_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
		return (-1);
	data->mlx.mlx_ptr_flag = 1;
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, \
									data->parse.win_width, \
									data->parse.win_height, "cub3d");
	if (data->mlx.win_ptr == NULL)
		return (-1);
	data->mlx.win_ptr_flag = 1;
	data->main.img_ptr = mlx_new_image(data->mlx.mlx_ptr, \
									data->parse.win_width, \
									data->parse.win_height);
	if (data->main.img_ptr == NULL)
		return (-1);
	data->main.img_ptr_flag = 1;
	data->main.img_addr = mlx_get_data_addr(data->main.img_ptr, \
									&data->main.bits_per_pixel, \
									&data->main.line_size, &data->main.endian);
	if (data->main.img_addr == NULL)
		return (-1);
	data->main.img_addr_flag = 1;
	if (load_all_xpm_images(data))
		return (-1);
	return (0);
}

static void	set_start_location(t_player *player, char **map)
{
	int	x;
	int	y;

	find_player_location(&x, &y, map);
	if (map[y][x] == 'N')
		player->angle = 0.5 * PI;
	else if (map[y][x] == 'W')
		player->angle = 1 * PI;
	else if (map[y][x] == 'S')
		player->angle = 1.5 * PI;
	else
		player->angle = 0 * PI;
	player->x = (x + 0.5) * UNIT;
	player->y = (y + 0.5) * UNIT;
}

int	raycaster_main(t_data *data)
{
	int	ret;

	ret = raycaster_init(data);
	if (ret == -1)
		return (-1);
	ret = set_mlx(data);
	if (ret == -1)
		return (-1);
	set_start_location(&data->player, data->parse.map);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, \
			keypress_hook, data);
	mlx_hook(data->mlx.win_ptr, KeyRelease, KeyReleaseMask, \
			keyrelease_hook, data);
	if (__LINUX__ == 1)
		mlx_hook(data->mlx.win_ptr, ClientMessage, NoEventMask, \
				close_window, data);
	else
		mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, \
				close_window, data);
	mlx_loop_hook(data->mlx.mlx_ptr, gameplay, data);
	mlx_loop(data->mlx.mlx_ptr);
	return (0);
}
