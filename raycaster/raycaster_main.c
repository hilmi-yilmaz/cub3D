/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 11:07:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/12 09:33:51 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int				cast_ray(t_img *img);


int	raycaster_main(t_img *img, t_info *info)
{
	t_player player;
	
	/* Copy the data of the info struct inside the img struct */
	img->info = *info;
	//print_map(&img->info);
	
	/* Establish the connection between the X Server and X client */
	img->mlx_ptr = mlx_init();
	if (img->mlx_ptr == NULL)
		return (-1);

	/* Create the window */
	img->win_ptr = mlx_new_window(img->mlx_ptr, info->win_width, info->win_height, "cub3d");
	if (img->win_ptr == NULL)
		return (-1);

	/* Create an empty image */
	img->img_ptr = mlx_new_image(img->mlx_ptr, info->win_width, info->win_height);
	if (img->img_ptr == NULL)
		return (-1);

	/* Get the address of the image */
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_size, &img->endian);

	/* Initialize the screen with the player */
	init(img);

	/* React on the moving player */
	mlx_hook(img->win_ptr, KeyPress, KeyPressMask, key_input, img);

	/* React on closing the screen */
	if (IS_LINUX == 1)
		mlx_hook(img->win_ptr, ClientMessage, NoEventMask, close_window, img);
	else
		mlx_hook(img->win_ptr, DestroyNotify, StructureNotifyMask, close_window, img);

	/* mlx_loop is needed for listening to events. It is an infinite loop */
	mlx_loop(img->mlx_ptr);

	return (0);
}


int	cast_ray(t_img *img)
{
	float step;
	float x_line_end;
	float y_line_end;

	img->ray.len = 0;
	step = 0.01;
	while (1)
	{
		x_line_end = img->player.x_unit + img->ray.len * cos(img->player.alpha);
		y_line_end = img->player.y_unit - img->ray.len * sin(img->player.alpha);
		//printf("%c\n", img->info.map.map[(int)x_line_end][(int)y_line_end]);
		//printf("len_ray = %f\n", img->ray.len);
		if (img->info.map.map[(int)y_line_end][(int)x_line_end] == 1 + '0')
		{
			draw_line(img, img->player.x, img->player.y, img->ray.len * UNIT);
			return (0);
		}
		img->ray.len += step;
		// x_line_end = img->ray.len * cos(img->player.alpha);
		// y_line_end = img->ray.len * sin(img->player.alpha);
	}
	return (-1);
}

int	close_window(t_img *img)
{
	/* Destroy the image and window */
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	if (IS_LINUX == 1)
		mlx_destroy_display(img->mlx_ptr);

	/* Free the pointer */
	free(img->mlx_ptr); /* mlx_init pointer */

	/* Exit the program */
	exit(0);
	return (1);
}