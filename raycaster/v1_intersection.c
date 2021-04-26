/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int horizontal_intersection(t_data *data, float angle, int *horizontal)
{
    float	xa;
    float	ya;
    int		ray_len;

    //printf("--------------- Horizontal ----------------\n");

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
    //draw_point(&data->img, horizontal[0], horizontal[1]);

	/* Check whether the value of xa should be + or - */
	if (unit_circle_upper_lower(angle) == 1) /* Ray facing right */
		xa *= -1;

    //printf("ya = %f, xa = %f\n", ya, xa);

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
    
   // printf("--------------- Vertical ----------------\n");

    /* Calculate horizontal intersection if ray is facing up/down */
    if (unit_circle_left_right(angle) == 1) /* Ray facing right */
    {
        vertical[0] = (int)(data->player.x / UNIT) * UNIT + UNIT;
        xa = UNIT;
    }
    else// if (unit_circle_left_right(angle) == 0) /* Ray facing left */
    {
        vertical[0] = (int)(data->player.x / UNIT) * UNIT - 1;
        xa = -UNIT;
    }
    vertical[1] = data->player.y + (data->player.x - vertical[0]) * tan(angle);
	ya = UNIT * tan(angle);

   // printf("vertical_x = %d, vertical_y = %d\n", vertical[0], vertical[1]);

    //draw_point(&data->img, vertical[0], vertical[1]);

	/* Check whether the value of ya should be + or - */
	if (unit_circle_left_right(angle) == 1)
		ya *= -1;

  //  printf("ya = %f, xa = %f\n", ya, xa);

    //if (horizontal[0] >= data->parse.win_width || horizontal[0] < 0)
    //    return (-1);
    if (check_wall(data->parse.map, vertical[0], vertical[1]) == 1) /* if wall found */
		return (calculate_ray_len(data->player, vertical[0], vertical[1]));
	else if (check_wall(data->parse.map, vertical[0], vertical[1]) == -1)
		return (-1);
   // printf("ray_len vertical:\n");
	return(expand_ray(data, vertical, xa, ya)); 
}

int expand_ray(t_data *data, int *xy_coordinates, float xa, float ya)
{
    int wall;
   // printf("Entered expand_ray\n");
    wall = 0;
    while (wall == 0)
    {
        xy_coordinates[0] += xa;
        xy_coordinates[1] += ya;
	//	printf("x = %d, y = %d\n", xy_coordinates[0], xy_coordinates[1]);
        wall = check_wall(data->parse.map, xy_coordinates[0], xy_coordinates[1]);
        // if (wall != -1)
        //     draw_point(&data->img, xy_coordinates[0], xy_coordinates[1]);
    }
   // printf("---------------------------------------------------------------------------------------\n");
    if (wall == -1)
        return (-1);
    return (calculate_ray_len(data->player, xy_coordinates[0], xy_coordinates[1]));
}
