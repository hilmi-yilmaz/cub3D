/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void	remove_current_player(t_img *img)
{
	int	i;
	int	j;

	i = -img->player.height / 2;
	j = -img->player.width / 2;
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

void	remove_line(t_img *img, float angle, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, img->player.x + i * cos(angle), img->player.y + i * -sin(angle), argb_to_hex(0, 0, 0, 0));
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}