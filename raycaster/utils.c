/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void    set_start_location(t_player *player, char **map)
{
    int	x;
	int	y;
	
	find_player_location(&x, &y, map);
	if (map[y][x] == 'N')
        player->angle = 0.5 * PI;
    else if (map[y][x] == 'W')
        player->angle = 1 * PI;
    else if (map[y][x] == 'S')
        player->angle = 1.5 * PI;
    else
        player->angle = 0 * PI;
	player->x = (x + 0.5) * UNIT;
    player->y = (y + 0.5) * UNIT;
}

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
        i++;
    return (i);
}

int close_window(t_data *data)
{
    /* Destroy the image and window */
    mlx_destroy_image(data->images.mlx.mlx_ptr, data->images.main.img_ptr);
    mlx_destroy_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr);
    if (__linux__)
        mlx_destroy_display(data->images.mlx.mlx_ptr);

    /* Free the pointers */
    free(data->images.mlx.mlx_ptr);
    
    /* Exit the programn */
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

unsigned int    my_pixel_get(t_img *img, int pos_x, int pos_y)
{
    unsigned int    offset;
    char            *dst;

    offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
    dst = img->img_addr + offset;
    return (*(unsigned int *)dst);
}

unsigned int argb_to_hex(int a, int r, int g, int b)
{
    return (a<<24 | r<<16 | g<<8 | b);
}

int get_argb(unsigned int argb, char c)
{
    int shift;
    
    if (c == 'a')
        shift = 24;
    else if (c == 'r')
        shift = 16;
    else if (c == 'g')
        shift = 8;
    else if (c == 'b')
        shift = 0;
    else
        return (-1);
    return ((argb & (0xFF << shift)) >> shift);
}
