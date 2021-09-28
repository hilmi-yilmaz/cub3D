/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

static double	set_vertical_data(t_player *player, double angle, double ver_dist, int i, int win_width, int wall_ver)
{
	double distance;

	if (unit_circle_left_right(angle) == 3) // Put these numbers in an ENUM instead of 1, 2, 3, 4
		player->side[i] = 'E';
	else
		player->side[i] = 'W';
	player->which_wall[i] = wall_ver + player->side[i];
	distance = ver_dist;
	if (i == 0)
	{
		if (player->side[i] == 'W')
			player->wall_x_start = 1.0 - (player->ver_ray.y - (int)player->ver_ray.y);
		else if (player->side[i] == 'E')
			player->wall_x_start = player->ver_ray.y - (int)player->ver_ray.y;
	}
	else if (i == win_width - 1)
	{
		if (player->side[i] == 'W')
			player->wall_x_end = player->ver_ray.y - (int)player->ver_ray.y;
		else if (player->side[i] == 'E')
			player->wall_x_end = 1.0 - (player->ver_ray.y - (int)player->ver_ray.y);
	}
	return (distance);
}

static double	set_horizontal_data(t_player *player, double angle, double hor_dist, int i, int win_width, int wall_hor)
{
	double distance;

	if (unit_circle_upper_lower(angle) == 0)
		player->side[i] = 'N';
	else
		player->side[i] = 'S';
	player->which_wall[i] = wall_hor + player->side[i];
	distance = hor_dist;
	if (i == 0)
	{
		if (player->side[i] == 'S')
			player->wall_x_start = 1.0 - (player->hor_ray.x - (int)player->hor_ray.x);
		else if (player->side[i] == 'N')
			player->wall_x_start = player->hor_ray.x - (int)player->hor_ray.x;
	}
	else if (i == win_width - 1)
	{
		if (player->side[i] == 'S') 
			player->wall_x_end = player->hor_ray.x - (int)player->hor_ray.x;
		else if (player->side[i] == 'N')
			player->wall_x_end = 1.0 - (player->hor_ray.x - (int)player->hor_ray.x);
	}
	return (distance);
}

/*
** Function: cast_single_ray
** Casts a single ray for a specific column on the screen.
**
** Arguments:
** 		(t_player *) player: contains information on player position etc.
** 		(t_parse *) parse: contains all information read from .cub file.
**		(double) ange: the angle of the ray to be casted.
**		(int) i: the column on the screen. Used to set player->side and player->which_wall.
*/
static double	cast_single_ray(t_player *player, t_parse *parse, double angle, int i)
{
	double	hor_dist;
	double	ver_dist;
	double	distance;
	int		wall_hor;
	int		wall_ver;

	wall_hor = horizontal_intersection(player, angle, parse->map);
	wall_ver = vertical_intersection(player, angle, parse->map);
	hor_dist = calculate_ray_len(player, player->hor_ray.x, player->hor_ray.y);
	ver_dist = calculate_ray_len(player, player->ver_ray.x, player->ver_ray.y);
	if (ver_dist <= hor_dist)
		distance = set_vertical_data(player, angle, ver_dist, i, parse->win_width, wall_ver);
    else
		distance = set_horizontal_data(player, angle, hor_dist, i, parse->win_width, wall_hor);
    return (distance * cos(player->angle - angle));
}

int cast_all_rays(t_player *player, t_parse *parse)
{
    int     i;
    double  angle;
    double  angle_increment;

    i = 0;
    angle = player->angle - 0.5 * deg2rad(FOV);
    angle_increment = deg2rad(FOV) / parse->win_width;
    player->rays_array = malloc(sizeof(*player->rays_array) * parse->win_width);
    if (player->rays_array == NULL)
        return (-1);
    player->side = malloc(sizeof(*player->side) * parse->win_width);
    if (player->side == NULL)
        return (-1);
    player->which_wall = malloc(sizeof(*player->which_wall) * parse->win_width);
    if (player->which_wall == NULL)
        return (-1);
    while (i < parse->win_width)
    {
        player->rays_array[parse->win_width - 1 - i] = cast_single_ray(player, parse, angle, parse->win_width - 1 - i);
        angle += angle_increment;
        reset_angle(&angle);
        i++;
    }
    return (0);
}