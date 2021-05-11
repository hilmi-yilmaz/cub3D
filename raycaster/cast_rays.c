/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

double	cast_single_ray(t_player *player, double angle, char **map)
{
	double	hor_dist;
	double	ver_dist;
	double	distance;

	horizontal_intersection(player, angle, map);
	vertical_intersection(player, angle, map);
	hor_dist = calculate_ray_len(player, player->hor_ray.x, angle);
	ver_dist = calculate_ray_len(player, player->ver_ray.x, angle);
	if (ver_dist <= hor_dist)
		distance = ver_dist;
	else
		distance = hor_dist;
	return (distance * cos(player->angle - angle));
}

int cast_all_rays(t_player *player, int width, char **map)
{
    int     i;
    double  angle;
    double  angle_increment;

    i = 0;
    angle = player->angle - 0.5 * deg2rad(FOV);
    angle_increment = deg2rad(FOV) / width;
    player->rays_array = malloc(sizeof(double) * width);
    while (i < width)
    {
        player->rays_array[i] = cast_single_ray(player, angle, map);
        angle += angle_increment;
        reset_angle(&angle);
        i++;
    }
    print_rays_array(player->rays_array, width);
    return (0);
}