/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int raycaster_main(t_data *data)
{
    /* Establish the connection between the X Server and X client */
	data->img.mlx_ptr = mlx_init();
	if (data->img.mlx_ptr == NULL)
		return (-1);

	/* Create the window */
	data->img.win_ptr = mlx_new_window(data->img.mlx_ptr, data->parse.win_width, data->parse.win_height, "cub3d");
	if (data->img.win_ptr == NULL)
		return (-1);

	/* Create an empty image */
	data->img.img_ptr = mlx_new_image(data->img.mlx_ptr, data->parse.win_width, data->parse.win_height);
	if (data->img.img_ptr == NULL)
		return (-1);

	/* Get the address of the image */
	data->img.img_addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_size, &data->img.endian);

	/* Initialize the screen with the player */
	init(data);

	//printf("x = %d, y = %d, alpha = %f (%f)\n", data->player.x, data->player.y, data->player.angle, data->player.angle / PI * 180);

	/* React on the moving player */
	mlx_hook(data->img.win_ptr, KeyPress, KeyPressMask, hooks, data);

	/* React on closing the screen */
	if (__linux__)
		mlx_hook(data->img.win_ptr, ClientMessage, NoEventMask, close_window, data);
	else
		mlx_hook(data->img.win_ptr, DestroyNotify, StructureNotifyMask, close_window, data);

	/* mlx_loop is needed for listening to events. It is an infinite loop */
	mlx_loop(data->img.mlx_ptr);

	return (0);
}
