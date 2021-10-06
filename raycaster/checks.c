/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

/*
** The check_wall function checks whether there is a wall at location (x,y).
**
** Arguments:
**		(char **)	map	: The input map which is read from the .cub file.
**		(double)	x	: The x location of the player.
**		(double)	y	: The y location of the player.
**
** Returns:
**		(int)		-1 if the coordinates are invalid (outside of the map).
**					 0 if there is no wall.
**					 positive integer ( >0 ) if there is a wall.
*/

int	check_wall(char **map, double x, double y)
{
	if (check_coordinates(x, y, map) == -1)
		return (-1);
	if (map[(int)y][(int)x] == '1')
		return ((int)y + (int)x);
	return (0);
}

int	check_next_step(double new_x, double new_y, char **map)
{
	double	angle;
	double	angle_increment;
	double	x;
	double	y;

	angle = 0;
	angle_increment = PI / 180;
	while (angle < 2 * PI)
	{
		x = new_x + GLASS * cos(angle);
		y = new_y + GLASS * sin(angle);
		if (check_wall(map, x, y) > 0)
			return (1);
		angle += angle_increment;
	}
	return (0);
}

int	check_coordinates(double x, double y, char **map)
{
	if (x < 0 || y < 0 || x > INF || y > INF)
		return (-1);
	if ((int)y >= ft_arrlen(map) || x > ft_strlen(map[(int)y]))
		return (-1);
	return (0);
}
