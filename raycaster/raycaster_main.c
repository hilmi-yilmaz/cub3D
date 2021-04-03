/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 11:07:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/03 15:04:43 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415

/* User defined header files */
#include "../cub3d.h"

/* Prototypes while testing */
int				close_window(t_img *img);
unsigned int 	argb_to_hex(int a, int r, int g, int b);
void    		my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
void			init(t_img *img, t_info *info);
void			draw_player(t_img *img);
void			remove_current_player(t_img *img);
int				key_input(int keycode, t_img *img);

void			draw_map(t_img *img, t_info *info);
void			draw_unit(t_img *img, int pos_x, int pos_y);

void			draw_line(t_img *img, int x_start, int y_start, int len);
void			remove_line(t_img *img, int x_start, int y_start, int len);

void			player_location(t_img *img);
int				check_wall(int **map, int x, int y);

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
	init(img, info);

	/* React on the moving player */
	mlx_hook(img->win_ptr, KeyPress, KeyPressMask, key_input, img);

	/* React on closing the screen */
	if (IS_LINUX)
		mlx_hook(img->win_ptr, ClientMessage, NoEventMask, close_window, img);
	else
		mlx_hook(img->win_ptr, DestroyNotify, StructureNotifyMask, close_window, img);

	/* mlx_loop is needed for listening to events. It is an infinite loop */
	mlx_loop(img->mlx_ptr);

	return (0);
}

void	init(t_img *img, t_info *info)
{
	img->player.x = 100;
	img->player.y = 100;
	player_location(img);
	img->player.width = 11;
	img->player.height = 11;
	img->player.alpha = 0.25 * PI;
	draw_map(img, info);
	draw_player(img);
	draw_line(img, img->player.x + 0.5 * img->player.width, img->player.y + 0.5 * img->player.height, 20);
}

void	draw_player(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->player.height)
	{
		while (j < img->player.width)
		{
			my_pixel_put(img, img->player.x + j, img->player.y + i, argb_to_hex(0, 255, 255, 255));
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	remove_current_player(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->player.height)
	{
		while (j < img->player.width)
		{
			my_pixel_put(img, img->player.x + j, img->player.y + i, argb_to_hex(0, 0, 0, 0));
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	player_location(t_img *img)
{
	img->player.x_unit = (float)img->player.x / UNIT;
	img->player.y_unit = (float)img->player.y / UNIT;
}

void	draw_map(t_img *img, t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*(info->map.map + i) != NULL)
	{
		while (j < 8)
		{
			//printf("info->map.map[i][j] = %d\n", info->map.map[i][j]);
			if (info->map.map[i][j] == 1)
				draw_unit(img, j * UNIT, i * UNIT);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_unit(t_img *img, int pos_x, int pos_y)
{
	int i;
	int j;

	i = 2;
	j = 2;
	while (i < UNIT - 2)
	{
		while (j < UNIT - 2)
		{
			my_pixel_put(img, pos_x + j, pos_y + i, argb_to_hex(0, 255, 255, 0));
			j++;
		}
		j = 2;
		i++;
	}
}

void	draw_line(t_img *img, int x_start, int y_start, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, x_start + i * cos(img->player.alpha), y_start + i * -sin(img->player.alpha), argb_to_hex(0, 255, 0, 0));
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	remove_line(t_img *img, int x_start, int y_start, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, x_start + i * cos(img->player.alpha), y_start + i * -sin(img->player.alpha), argb_to_hex(0, 0, 0, 0));
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

int		key_input(int keycode, t_img *img)
{
	int speed;
	int	wall;
	
	speed = 10;
	remove_current_player(img);
	remove_line(img, img->player.x + 0.5 * img->player.width, img->player.y + 0.5 * img->player.height, 20);
	if (keycode == LEFT_KEY)
	{
		wall = check_wall(img->info.map.map, img->player.x - speed, img->player.y);
		if (wall == 0)
			img->player.x -= speed;
	}
	else if (keycode == RIGHT_KEY)
	{
		wall = check_wall(img->info.map.map, img->player.x + speed, img->player.y);
		if (wall == 0)
			img->player.x += speed;
	}
	else if (keycode == UP_KEY)
	{
		wall = check_wall(img->info.map.map, img->player.x, img->player.y - speed);
		if (wall == 0)
			img->player.y -= speed;
	}
	else if (keycode == DOWN_KEY)
	{
		wall = check_wall(img->info.map.map, img->player.x, img->player.y + speed);
		if (wall == 0)
			img->player.y += speed;
	}
	else if (keycode == A_KEY)
		img->player.alpha += 0.02 * PI;
	else if (keycode == D_KEY)
		img->player.alpha -= 0.02 * PI;
	
	draw_player(img);
	draw_line(img, img->player.x + 0.5 * img->player.width, img->player.y + 0.5 * img->player.height, 20);
	player_location(img);
	//printf("x_unit = %f, y_unit = %f\n", img->player.x_unit, img->player.y_unit);
	return (0);
}

int		check_wall(int **map, int x, int y)
{
	float next_location_x;
	float next_location_y;

	next_location_x = (float)x / UNIT;
	next_location_y = (float)y / UNIT;
	printf("x = %d, y = %d, map[x][y] = %d\n", (int)next_location_x, (int)next_location_y, map[(int)next_location_y][(int)next_location_x]);
	if (map[(int)next_location_y][(int)next_location_x] == 1)
		return (1);
	return (0);
}

int	close_window(t_img *img)
{
	/* Destroy the image and window */
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);

	/* Free the pointer */
	free(img->mlx_ptr); /* mlx_init pointer */

	/* Exit the program */
	exit(0);
	return (1);
}

void    my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
    unsigned int    offset;
    char            *dst;

    offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
    dst = img->img_addr + offset;
    *(unsigned int *)dst = colour;
}

unsigned int argb_to_hex(int a, int r, int g, int b)
{
    return (a<<24 | r<<16 | g<<8 | b);
}