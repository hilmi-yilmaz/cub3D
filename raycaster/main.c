/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

static int	set_mlx(t_data *data)
{
	data->images.mlx.mlx_ptr = mlx_init();
	data->images.mlx.mlx_ptr = NULL;
	if (data->images.mlx.mlx_ptr == NULL)
		return (-1);
	data->images.mlx.win_ptr = mlx_new_window(data->images.mlx.mlx_ptr, \
											  data->parse.win_width, \
											  data->parse.win_height, \
											  "cub3d");
	if (data->images.mlx.win_ptr == NULL)
		return (-2);
	data->images.main.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, \
											  data->parse.win_width, \
											  data->parse.win_height);
	if (data->images.main.img_ptr == NULL)
		return (-3);
	data->images.main.img_addr = mlx_get_data_addr(\
										data->images.main.img_ptr, \
										&data->images.main.bits_per_pixel, \
										&data->images.main.line_size, \
										&data->images.main.endian);
	if (data->images.main.img_addr == NULL)
		return (-4);
	if (load_all_xpm_images(&data->images, &data->parse))
		return (-5);
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
		return (-2);
	set_start_location(&data->player, data->parse.map);
	mlx_hook(data->images.mlx.win_ptr, KeyPress, KeyPressMask, \
			keypress_hook, data);
	mlx_hook(data->images.mlx.win_ptr, KeyRelease, KeyReleaseMask, \
			keyrelease_hook, data);
	if (__linux__)
		mlx_hook(data->images.mlx.win_ptr, ClientMessage, NoEventMask, \
				close_window, data);
	else
		mlx_hook(data->images.mlx.win_ptr, DestroyNotify, StructureNotifyMask, \
				close_window, data);
	mlx_loop_hook(data->images.mlx.mlx_ptr, gameplay, data);
	mlx_loop(data->images.mlx.mlx_ptr);
	return (0);
}
