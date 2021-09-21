/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

#define SCALE_X 0.5
#define SCALE_Y 0.5

void	basic_horizontal_image(t_img *img)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (j < img->height)
	{
		while (i < img->width)
		{
			if (i == 0)
				my_pixel_put(img, i, j, argb_to_hex(0, 255, 0, 0));
			else if (i == 1)
				my_pixel_put(img, i, j, argb_to_hex(0, 0, 255, 0));
			else if (i == 2)
				my_pixel_put(img, i, j, argb_to_hex(0, 0, 0, 255));
			i++;
		}
		i = 0;
		j++;
	}
}

int raycaster_main(t_data *data)
{
	int ret;

	raycaster_init(data);
	data->images.mlx.mlx_ptr = mlx_init();
	if (data->images.mlx.mlx_ptr == NULL)
		return (-1);
	data->images.mlx.win_ptr = mlx_new_window(data->images.mlx.mlx_ptr, data->parse.win_width, data->parse.win_height, "cub3d");
	if (data->images.mlx.win_ptr == NULL)
		return (-1);
	data->images.main.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, data->parse.win_width, data->parse.win_height);
	if (data->images.main.img_ptr == NULL)
		return (-1);
	data->images.main.img_addr = mlx_get_data_addr(data->images.main.img_ptr, &data->images.main.bits_per_pixel, &data->images.main.line_size, &data->images.main.endian);
	ret = init_window(data);
	mlx_hook(data->images.mlx.win_ptr, KeyPress, KeyPressMask, hooks, data);
	if (__linux__)
		mlx_hook(data->images.mlx.win_ptr, ClientMessage, NoEventMask, close_window, data);
	else
		mlx_hook(data->images.mlx.win_ptr, DestroyNotify, StructureNotifyMask, close_window, data);
	mlx_loop(data->images.mlx.mlx_ptr);
	return (0);
}
