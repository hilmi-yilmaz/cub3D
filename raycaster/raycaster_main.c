/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

#define SCALE_X 0.5
#define SCALE_Y 0.5

int raycaster_main(t_data *data)
{
    /* Establish the connection between the X Server and X client */
	data->images.mlx.mlx_ptr = mlx_init();
	if (data->images.mlx.mlx_ptr == NULL)
		return (-1);

	/* Create the window */
	// data->images.mlx.win_ptr = mlx_new_window(data->images.mlx.mlx_ptr, data->parse.win_width, data->parse.win_height, "cub3d");
	// if (data->images.mlx.win_ptr == NULL)
	// 	return (-1);
// ------------------------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------------------------------------------------------------------------------------------//
	/* Create an xpm image */
    t_img	xpm_img;
	// xpm_img.mlx_ptr = data->img.mlx_ptr;
	// xpm_img.win_ptr = data->img.win_ptr;
	// int	img_width;
	// int	img_height;
	xpm_img.img_ptr = mlx_xpm_file_to_image(data->images.mlx.mlx_ptr, "textures/stone.xpm", &xpm_img.width, &xpm_img.height);
	//xpm_img.img_ptr = mlx_png_file_to_image(xpm_img.mlx_ptr, "textures/pics/eagle.png", &img_width, &img_height);
	if (xpm_img.img_ptr == NULL)
	{
		printf("xpm = NULL\n");
		return (-1);
	}

	/* Create a scaled xpm image */
    t_img	scaled_xpm_img;
	scaled_xpm_img.width = 80;
	scaled_xpm_img.height = 32;
	scaled_xpm_img.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, scaled_xpm_img.width, scaled_xpm_img.height);
	if (scaled_xpm_img.img_ptr == NULL)
	{
		printf("scaled_xpm = NULL\n");
		return (-1);
	}

	scale_bmp(&xpm_img, &scaled_xpm_img);

	/* Create the window */
	data->images.mlx.win_ptr = mlx_new_window(data->images.mlx.mlx_ptr, 1024, 1024, "cub3d");
	if (data->images.mlx.win_ptr == NULL)
		return (-1);

	mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, scaled_xpm_img.img_ptr, 0, 40);

	mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, xpm_img.img_ptr, 0, 0);

// ------------------------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------------------------------------------------------------------------------------------//
// ------------------------------------------------------------------------------------------------------------------------------------//
	
	// /* Create an empty image */
	// data->images.main.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, data->parse.win_width, data->parse.win_height);
	// if (data->images.main.img_ptr == NULL)
	// 	return (-1);

	// /* Get the address of the image */
	// data->images.main.img_addr = mlx_get_data_addr(data->images.main.img_ptr, &data->images.main.bits_per_pixel, &data->images.main.line_size, &data->images.main.endian);

	// /* Initialize the screen with the player */
	// init(data);

	/* React on the moving player */
	mlx_hook(data->images.mlx.win_ptr, KeyPress, KeyPressMask, hooks, data);

	/* React on closing the screen */
	if (__linux__)
		mlx_hook(data->images.mlx.win_ptr, ClientMessage, NoEventMask, close_window, data);
	else
		mlx_hook(data->images.mlx.win_ptr, DestroyNotify, StructureNotifyMask, close_window, data);

	/* mlx_loop is needed for listening to events. It is an infinite loop */
	mlx_loop(data->images.mlx.mlx_ptr);

	return (0);
}
