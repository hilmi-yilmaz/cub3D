/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void	player_location(t_img *img)
{
	img->player.x_unit = (float)img->player.x / UNIT;
	img->player.y_unit = (float)img->player.y / UNIT;
}

int	unit_circle(float alpha)
{
	if ((alpha >= 0 && alpha < PI) || (alpha <= -PI && alpha > -2 * PI))
		return (0);
	else if ((alpha >= PI && alpha < 2 * PI) || (alpha > -PI && alpha < 0))
		return (1);
	else
		return (-1);
}

int		check_wall(t_map map, int x, int y) /* x and y are pixel coordinates */
{
	float next_location_x;
	float next_location_y;

	next_location_x = (float)x / UNIT;
	next_location_y = (float)y / UNIT;

	printf("Checking wall at x = %d, y = %d\n", x, y);
	
	/* Can't have a higher y than the amount of rows in the map itself */
	if ((int)next_location_y > ft_arrlen(map.map))
		return (-1);
	/* Can't have higher x than the elements in y'th row in the map */
	if (next_location_x > map.len_element[(int)next_location_y])
		return (-1);
	//printf("x = %d, y = %d\n", (int)next_location_x, (int)next_location_y);
	//printf("x = %d, y = %d, map[x][y] = %d\n", (int)next_location_x, (int)next_location_y, map.map[(int)next_location_y][(int)next_location_x]);
	if (map.map[(int)next_location_y][(int)next_location_x] == 1 + '0')
		return (1); /* Found wall */
	return (0); /* No wall */
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