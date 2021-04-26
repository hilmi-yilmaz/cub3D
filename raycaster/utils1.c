/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void	player_location(t_player *player)
{
	player->x_unit = (float)player->x / UNIT;
	player->y_unit = (float)player->y / UNIT;
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

int		check_wall(char **map, int x, int y) /* x and y are pixel coordinates */
{
	int	x_unit;
	int	y_unit;

	x_unit = (float)x / UNIT;
	y_unit = (float)y / UNIT;

	//printf("Checking wall at x = %d, y = %d\n", x, y);

	//printf("x_unit = %d, y_unit = %d\n", x_unit, y_unit);
	
	/* Can't have a higher y than the amount of rows in the map itself */
	//printf("y_unit = %d, map_rows = %d\n", (int)y_unit, ft_arrlen(map.map));
	if (y_unit < 0 || y_unit + 1 >= ft_arrlen(map))
		return (-1);
	/* Can't have higher x than the elements in y'th row in the map */
	if (x_unit > ft_strlen(map[y_unit])) 
		return (-1);
	//printf("x = %d, y = %d\n", (int)x_unit, (int)y_unit);
	//printf("x = %d, y = %d, map[x][y] = %d\n", (int)x_unit, (int)y_unit, map.map[(int)y_unit][(int)x_unit]);
	if (map[y_unit][x_unit] == '1')
		return (1); /* Found wall */
	return (0); /* No wall */
}

double	calculate_ray_len(t_player player, int x, int y)
{
	return(sqrt(pow(player.x - x, 2) + pow(player.y - y, 2)));
}

/*
** This function checks whether the coordinates x_unit, y_unit are in the map.
*/

// int	check_coordinates(t_parse *parse, float x_unit, float y_unit)
// {
// 	if (y_unit >= ft_arrlen(parse->map) || y < 0)
// 		return (-1);
// 	if (x >= ft_strlen(parse->map[(int)(y / UNIT)]))
// 		return (-1);
// 	return (0);
// }

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