/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int check_wall(char **map, double x, double y)
{  
    // printf("Checking with x = %d, y = %d\n", (int)x, (int)y);

    if (check_coordinates(x, y, map) == -1)
        return (-1);
    /* Check for glass wall */
    if (map[(int)y][(int)x] == '1')
		return (1);
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
		if (check_wall(map, x, y) == 1)
			return (1);
		angle += angle_increment;
	}
	return (0);
}

int check_coordinates(double x, double y, char **map)
{
    if (x < 0 || y < 0 || x > INF || y > INF)
        return (-1);
    if ((int)y >= ft_arrlen(map) || x > ft_strlen(map[(int)y]))
        return (-1);
    return (0);
}
