/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

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

void	draw_line(t_img *img, float angle, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, img->player.x + i * cos(angle), img->player.y + i * -sin(angle), argb_to_hex(0, 255, 0, 0));
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

int		draw_point(t_img *img, int x, int y)
{
	my_pixel_put(img, x, y, argb_to_hex(0, 255, 255, 255));
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}