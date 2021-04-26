/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void	remove_current_player(t_img *img, t_player *player)
{
	int	i;
	int	j;

	i = -player->height / 2; //i = 0;
	j = -player->width / 2; //j = 0;
	while (i < player->height / 2)
	{
		while (j < player->width / 2)
		{
			my_pixel_put(img, player->x + j, player->y + i, argb_to_hex(0, 0, 0, 0));
			j++;
		}
		j = -player->width / 2;
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	remove_line(t_img *img, t_player *player, float angle, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, player->x + i * cos(angle), player->y + i * -sin(angle), argb_to_hex(0, 0, 0, 0));
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}