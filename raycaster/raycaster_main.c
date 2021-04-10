/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 11:07:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/04/10 20:41:28 by hyilmaz       ########   odam.nl         */
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
int				check_wall(t_map map, int x, int y);
void			set_start_location(t_map map, int *x, int *y, float *alpha);

int				cast_ray(t_img *img);
int				horizontal_intersection(t_img *img);
int				draw_point(t_img *img, int x, int y);

int				ft_arrlen(int **arr);

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
	if (IS_LINUX == 1)
		mlx_hook(img->win_ptr, ClientMessage, NoEventMask, close_window, img);
	else
		mlx_hook(img->win_ptr, DestroyNotify, StructureNotifyMask, close_window, img);

	/* mlx_loop is needed for listening to events. It is an infinite loop */
	mlx_loop(img->mlx_ptr);

	return (0);
}

void	init(t_img *img, t_info *info)
{
	set_start_location(img->info.map, &img->player.x, &img->player.y, &img->player.alpha);
	//printf("x = %d, y = %d\n", img->player.x, img->player.y);
	player_location(img);
	img->player.width = 11;
	img->player.height = 11;
	draw_map(img, info);
	draw_player(img);
	//draw_line(img, img->player.x, img->player.y, 20);

	/* Initialize ray */
	img->ray.len = 1;
	horizontal_intersection(img);
	//cast_ray(img);
}

void	set_start_location(t_map map, int *x, int *y, float *alpha)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*(map.map + i) != NULL)
	{
		while (j < map.len_element[i])
		{
			//printf("%d\n", map.map[i][j]);
			if (map.map[i][j] == 'N' || map.map[i][j] == 'W' || map.map[i][j] == 'S' || map.map[i][j] == 'E')
			{
				*x = (j + 0.5) * UNIT;
				*y = (i + 0.5) * UNIT;
				if (map.map[i][j] == 'N')
					*alpha = 0.5 * PI;
				else if (map.map[i][j] == 'W')
					*alpha = 1 * PI;
				else if (map.map[i][j] == 'S')
					*alpha = 1.5 * PI;
				else
					*alpha = 0 * PI;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_player(t_img *img)
{
	int	i;
	int	j;

	i = -img->player.height / 2; //i = 0;
	j = -img->player.width / 2; //j = 0;
	while (i < img->player.height / 2)
	{
		while (j < img->player.width / 2)
		{
			my_pixel_put(img, img->player.x + j, img->player.y + i, argb_to_hex(0, 255, 255, 255));
			j++;
		}
		j = -img->player.width / 2;
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	remove_current_player(t_img *img)
{
	int	i;
	int	j;

	i = -img->player.height / 2; //i = 0;
	j = -img->player.width / 2; //j = 0;
	while (i < img->player.height / 2)
	{
		while (j < img->player.width / 2)
		{
			my_pixel_put(img, img->player.x + j, img->player.y + i, argb_to_hex(0, 0, 0, 0));
			j++;
		}
		j = -img->player.width / 2;
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
			if (info->map.map[i][j] == 1 + '0')
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

	i = EDGE;
	j = EDGE;
	while (i < UNIT - EDGE)
	{
		while (j < UNIT - EDGE)
		{
			my_pixel_put(img, pos_x + j, pos_y + i, argb_to_hex(0, 255, 0, 0));
			j++;
		}
		j = EDGE;
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

int	horizontal_intersection(t_img *img)
{
	int	y;
	int	x;
	int	ya;
	int	xa;
	int	wall;
	
	if (img->player.alpha >= 0 && img->player.alpha < PI) /* if ray is facing up */
	{
		y = (int)(img->player.y / UNIT) * UNIT - 1; /* y is in pixel coordinates */
		ya = -64;
	}
	else /* if ray is facing down */
	{
		y = (int)(img->player.y / UNIT) * UNIT + UNIT; /* y is in pixel coordinates */
		ya = 64;
	}
	x = img->player.x + (img->player.y - y) / tan(img->player.alpha); /* Also in pixel coordinates */

	printf("\ny_horizontal = %d = (%d / %d) * %d - 1\n", y, img->player.y, UNIT, UNIT);
	printf("x_horizontal = %d = %d + (%d - %d) / %f\n", x, img->player.x, img->player.y, y, tan(img->player.alpha));

	/* Find xa */
	xa = UNIT / tan(img->player.alpha);

	/* Check for wall at (x, y) */
	wall = check_wall(img->info.map, x, y);
	if (wall == 1)
	{
		printf("Found wall at x = %d, y = %d\n", x, y);
		return (1);
	}
	if (wall == -1)
	{
		printf("Can't find horizontal intersection in the image with angle = %f\n", img->player.alpha);
		return (-1);
	}
	draw_point(img, x, y);

	while (wall == 0)
	{
		x += xa;
		y += ya;
		draw_point(img, x, y);
		wall = check_wall(img->info.map, x, y);
		if (wall == 1)
		{
			printf("Found wall at x = %d, y = %d\n", x, y);
			return (1);
		}
		if (wall == -1)
		{
			printf("Can't find horizontal intersection in the image with angle = %f\n", img->player.alpha);
			return (-1);
		}
	}
	return (0);
}

int		draw_point(t_img *img, int x, int y)
{
	my_pixel_put(img, x, y, argb_to_hex(0, 255, 255, 255));
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int		key_input(int keycode, t_img *img)
{
	int speed;
	int	wall;
	
	speed = 8;
	remove_current_player(img);
	//remove_line(img, img->player.x, img->player.y, img->ray.len * UNIT);
	if (keycode == LEFT_KEY)
	{
		wall = check_wall(img->info.map, img->player.x - speed - img->player.width / 2, img->player.y);
		if (wall == 0)
			img->player.x -= speed;
	}
	else if (keycode == RIGHT_KEY)
	{
		wall = check_wall(img->info.map, img->player.x + speed + img->player.width / 2 - 1, img->player.y);
		if (wall == 0)
			img->player.x += speed;
	}
	else if (keycode == UP_KEY)
	{
		wall = check_wall(img->info.map, img->player.x, img->player.y - speed - img->player.height / 2);
		if (wall == 0)
			img->player.y -= speed;
	}
	else if (keycode == DOWN_KEY)
	{
		wall = check_wall(img->info.map, img->player.x, img->player.y + speed + img->player.height / 2 - 1);
		if (wall == 0)
			img->player.y += speed;
	}
	else if (keycode == A_KEY)
		img->player.alpha += 0.02 * PI;
	else if (keycode == D_KEY)
		img->player.alpha -= 0.02 * PI;
	
	draw_player(img);
	player_location(img);
	//cast_ray(img);
	horizontal_intersection(img);
	//printf("x_unit = %f, y_unit = %f\n", img->player.x_unit, img->player.y_unit);
	printf("x = %d, y = %d, alpha = %f\n", img->player.x, img->player.y, img->player.alpha);
	return (0);
}

int		check_wall(t_map map, int x, int y) /* x and y are pixel coordinates */
{
	float next_location_x;
	float next_location_y;

	next_location_x = (float)x / UNIT;
	next_location_y = (float)y / UNIT;

	/* Can't have a higher y than the amount of rows in the map itself */
	if ((int)next_location_y > ft_arrlen(map.map))
		return (-1);
	/* Can't have higher x than the elements in y'th row in the map */
	if (next_location_x > map.len_element[(int)next_location_y])
		return (-1);
	//printf("x = %d, y = %d\n", (int)next_location_x, (int)next_location_y);
	printf("x = %d, y = %d, map[x][y] = %d\n", (int)next_location_x, (int)next_location_y, map.map[(int)next_location_y][(int)next_location_x]);
	if (map.map[(int)next_location_y][(int)next_location_x] == 1 + '0')
		return (1); /* Found wall */
	return (0); /* No wall */
}

int		ft_arrlen(int **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
		i++;
	return (i);
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