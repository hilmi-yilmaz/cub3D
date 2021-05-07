/* Standard Library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    draw_player(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
    my_pixel_put(img, pos_x, pos_y, colour);
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    draw_unit(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < UNIT)
    {
        while (j < UNIT)
        {
            if (i == 0 || i == UNIT - EDGE || j == 0 || j == UNIT - EDGE)
                my_pixel_put(img, pos_x + j, pos_y + i, argb_to_hex(0, 0, 0, 0));
            else
                my_pixel_put(img, pos_x + j, pos_y + i, colour);
            j++;
        }
        j = 0;
        i++;
    }
}

void    set_background_color(t_img *img, t_parse *parse, unsigned int colour)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (parse->map[i] != NULL)
    {
        while (parse->map[i][j] != '\0')
        {
            draw_unit(img, j * UNIT, i * UNIT, colour);
            j++;
        }
        j = 0;
        i++;
    }
}

void    draw_map(t_img *img, t_parse *parse)
{
    int i;
    int j;

    i = 0;
    j = 0;
    set_background_color(img, parse, argb_to_hex(150, 100, 100, 100));
    while (parse->map[i] != NULL)
    {
        while (parse->map[i][j] != '\0')
        {
            if (parse->map[i][j] == '1')
                draw_unit(img, j * UNIT, i * UNIT, argb_to_hex(0, 255, 255, 0));
            j++;
        }
        j = 0;
        i++;
    }
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void	draw_line(t_img *img, t_player *player, double angle, int len, int colour)
{
	int i;

	i = 0;
	while (i < len)
	{
		my_pixel_put(img, player->x + i * cos(angle), player->y + i * -sin(angle), colour);
		i++;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    clear_screen(t_img *img, int win_width, int win_height)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < win_height)
    {
        while(j < win_width)
        {
            my_pixel_put(img, j, i, argb_to_hex(0, 0, 0, 0));
            j++;
        }
        j = 0;
        i++;
    }
}
