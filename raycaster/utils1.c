/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void	player_location(t_img *img)
{
	img->player.x_unit = (float)img->player.x / UNIT;
	img->player.y_unit = (float)img->player.y / UNIT;
}
/*
** Returns 0 if upperhalf cirle, 1 if lowerhalf circle
*/
int	unit_circle_upper_lower(float alpha)
{
	if ((alpha >= 0 && alpha < PI) || (alpha <= -PI && alpha > -2 * PI))
		return (0);
	else if ((alpha >= PI && alpha < 2 * PI) || (alpha > -PI && alpha < 0))
		return (1);
	else
		return (-1);
}

/*
** Return 0 if left half, 1 if right half.
*/
int	unit_circle_left_right(float alpha)
{
	alpha -= 0.5 * PI;
	/* If the angle is bigger than 2PI, substract 2PI */
	if (alpha > 2 * PI)
		alpha -= 2 * PI;
	if (alpha < -2 * PI)
		alpha += 2 * PI;
	return(unit_circle_upper_lower(alpha));
}

int		check_wall(t_map map, int x, int y) /* x and y are pixel coordinates */
{
	float x_unit;
	float y_unit;

	x_unit = (float)x / UNIT;
	y_unit = (float)y / UNIT;

	//printf("Checking wall at x = %d, y = %d\n", x, y);
	
	/* Can't have a higher y than the amount of rows in the map itself */
	//printf("y_unit = %d, map_rows = %d\n", (int)y_unit, ft_arrlen(map.map));
	if ((int)y_unit >= ft_arrlen(map.map))
		return (-1);
	/* Can't have higher x than the elements in y'th row in the map */
	if (x_unit > map.len_element[(int)y_unit])
		return (-1);
	//printf("x = %d, y = %d\n", (int)x_unit, (int)y_unit);
	//printf("x = %d, y = %d, map[x][y] = %d\n", (int)x_unit, (int)y_unit, map.map[(int)y_unit][(int)x_unit]);
	if (map.map[(int)y_unit][(int)x_unit] == 1 + '0')
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