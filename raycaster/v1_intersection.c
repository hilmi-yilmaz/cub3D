/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int cast_single_ray(t_data *data, float angle)
{
    int ray_len_hor;
	int	ray_len_ver;
	int	min_len;
	
	/* These are the horizontal and vertical intersection points */
    int horizontal[XY_COORDINATES];
    int vertical[XY_COORDINATES];

	min_len = -1;
	ray_len_hor = horizontal_intersection(data, angle, horizontal);
	ray_len_ver = vertical_intersection(data, angle, vertical);
	//printf("ray_len_hor = %d\n", ray_len_hor);
	//printf("ray_len_ver = %d\n", ray_len_ver);
	if (ray_len_hor > ray_len_ver)
		min_len = ray_len_ver;
	else if (ray_len_hor < ray_len_ver)
		min_len = ray_len_hor;
	if (ray_len_hor == -1)
		min_len = ray_len_ver;
	if (ray_len_ver == -1)
		min_len = ray_len_hor;
	//printf("min_len = %d\n", min_len);
	if (min_len != -1)
		draw_line(&data->img, &data->player, angle, min_len);
	return (min_len);
}

int horizontal_intersection(t_data *data, float angle, int *horizontal)
{
    float	xa;
    float	ya;
    int		ray_len;

	printf("-------------------------------------------------\n");

    /* Calculate horizontal intersection if ray is facing up/down */
    if (unit_circle_upper_lower(angle) == 0)
    {
        horizontal[1] = (int)(data->player.y / UNIT) * UNIT - 1;
        ya = -UNIT;
    }
    else
    {
        horizontal[1] = (int)(data->player.y / UNIT) * UNIT + UNIT;
        ya = UNIT;
    }
    horizontal[0] = data->player.x + (data->player.y - horizontal[1]) / tan(angle);
	xa = UNIT / tan(angle);

	/* Check whether the value of xa should be + or - */
	if (unit_circle_left_right(angle) == 1) /* Ray facing right */
		xa *= -1;

    //if (horizontal[0] >= data->parse.win_width || horizontal[0] < 0)
    //    return (-1);
    if (check_wall(data->parse.map, horizontal[0], horizontal[1]) == 1) /* if wall found */
		return (calculate_ray_len(data->player, horizontal[0], horizontal[1]));
	else if (check_wall(data->parse.map, horizontal[0], horizontal[1]) == -1)
		return (-1);
	return(expand_ray(data, horizontal, xa, ya)); 
}

int vertical_intersection(t_data *data, float angle, int *vertical)
{
    float	xa;
    float	ya;
    int		ray_len;

    /* Calculate horizontal intersection if ray is facing up/down */
    if (unit_circle_left_right(angle) == 1) /* Ray facing right */
    {
        vertical[0] = (int)(data->player.x / UNIT) * UNIT - 1;
        xa = UNIT;
    }
    else if (unit_circle_left_right(angle) == 0) /* Ray facing left */
    {
        vertical[0] = (int)(data->player.y / UNIT) * UNIT + UNIT;
        xa = -UNIT;
    }
    vertical[1] = data->player.y + (data->player.x - vertical[0]) * tan(angle);
	ya = UNIT * tan(angle);

	/* Check whether the value of ya should be + or - */
	if (unit_circle_upper_lower(angle) == 0)
		ya *= -1;

    //if (horizontal[0] >= data->parse.win_width || horizontal[0] < 0)
    //    return (-1);
    if (check_wall(data->parse.map, vertical[0], vertical[1]) == 1) /* if wall found */
		return (calculate_ray_len(data->player, vertical[0], vertical[1]));
	else if (check_wall(data->parse.map, vertical[0], vertical[1]) == -1)
		return (-1);
	return(expand_ray(data, vertical, xa, ya)); 
}

int expand_ray(t_data *data, int *xy_coordinates, float xa, float ya)
{
    int wall;

    wall = 0;
    while (wall == 0)
    {
        xy_coordinates[0] += xa;
        xy_coordinates[1] += ya;
		printf("x = %d, y = %d\n", xy_coordinates[0], xy_coordinates[1]);
        wall = check_wall(data->parse.map, xy_coordinates[0], xy_coordinates[1]);
    }
    if (wall == -1)
        return (-1);
    return (calculate_ray_len(data->player, xy_coordinates[0], xy_coordinates[1]));
}
