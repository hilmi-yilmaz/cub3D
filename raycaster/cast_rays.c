/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

double	cast_single_ray(t_player *player, double angle, char **map, int i, t_parse *parse)
{
	double	hor_dist;
	double	ver_dist;
	double	distance;
	int		wall_hor;
	int		wall_ver;

	wall_hor = horizontal_intersection(player, angle, map);
	wall_ver = vertical_intersection(player, angle, map);
	hor_dist = calculate_ray_len(player, player->hor_ray.x, player->hor_ray.y);
	ver_dist = calculate_ray_len(player, player->ver_ray.x, player->ver_ray.y); 
	if (ver_dist <= hor_dist)
    {
		if (unit_circle_left_right(angle) == 3) // Put these numbers in an ENUM instead of 1, 2, 3, 4
            player->side[i] = 'E';
        else
            player->side[i] = 'W';
		player->which_wall[i] = wall_ver + player->side[i];
        distance = ver_dist;
		if (i == 0)
			player->wall_x_start = player->ver_ray.x;
		else if (i == parse->win_width - 1)
			player->wall_x_end = player->ver_ray.x;
    }
    else
    {
		if (unit_circle_upper_lower(angle) == 0)
            player->side[i] = 'N';
        else
            player->side[i] = 'S';
		player->which_wall[i] = wall_hor + player->side[i];
		distance = hor_dist;
		if (i == 0)
			player->wall_x_start = player->hor_ray.x;
		else if (i == parse->win_width - 1)
			player->wall_x_end = player->hor_ray.x;
    }
    return (distance * cos(player->angle - angle));
}

int cast_all_rays(t_player *player, int width, char **map, t_parse *parse)
{
    int     i;
    double  angle;
    double  angle_increment;

    i = 0;
    angle = player->angle - 0.5 * deg2rad(FOV);
    angle_increment = deg2rad(FOV) / width;
    player->rays_array = malloc(sizeof(double) * width);
    player->side = malloc(sizeof(char) * width);
	player->which_wall = malloc(sizeof(int) * width);
    while (i < width)
    {
        player->rays_array[width - 1 - i] = cast_single_ray(player, angle, map, width - 1 - i, parse);
        angle += angle_increment;
        reset_angle(&angle);
        i++;
    }
    //print_side_array(player->side, width);
    return (0);
}