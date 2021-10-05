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
	if (data->images.mlx.mlx_ptr == NULL)
		return (-1);
	data->images.mlx.win_ptr = mlx_new_window(data->images.mlx.mlx_ptr, \
											  data->parse.win_width, \
											  data->parse.win_height, \
											  "cub3d");
	if (data->images.mlx.win_ptr == NULL)
		return (-1);
	data->images.main.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, \
											  data->parse.win_width, \
											  data->parse.win_height);
	if (data->images.main.img_ptr == NULL)
		return (-1);
	data->images.main.img_addr = mlx_get_data_addr(data->images.main.img_ptr, \
												   &data->images.main.bits_per_pixel, \
												   &data->images.main.line_size, \
												   &data->images.main.endian);
	if (data->images.main.img_addr == NULL)
		return (-1);
	if (!load_all_xpm_images(&data->images, &data->parse))
		return (FALSE);
	return (TRUE);
}

int	raycaster_main(t_data *data)
{
	int	ret;

	raycaster_init(data);
	ret = set_mlx(data);
	if (ret == FALSE)
		return (FALSE);
	set_start_location(&data->player, data->parse.map);
	mlx_hook(data->images.mlx.win_ptr, KeyPress, KeyPressMask, keypress_hook, data);
	mlx_hook(data->images.mlx.win_ptr, KeyRelease, KeyReleaseMask, keyrelease_hook, data);
	if (__linux__)
		mlx_hook(data->images.mlx.win_ptr, ClientMessage, NoEventMask, close_window, data);
	else
		mlx_hook(data->images.mlx.win_ptr, DestroyNotify, StructureNotifyMask, close_window, data);
	mlx_loop_hook(data->images.mlx.mlx_ptr, gameplay, data); 
	mlx_loop(data->images.mlx.mlx_ptr);
	return (0);
}
