/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

static void	set_vertical_data(t_player *player, double angle, int i)
{
	if (unit_circle_left_right(angle) == 3)
		player->side[i] = 'E';
	else
		player->side[i] = 'W';
}

static void	set_horizontal_data(t_player *player, double angle, int i)
{
	if (unit_circle_upper_lower(angle) == 0)
		player->side[i] = 'N';
	else
		player->side[i] = 'S';
}

/*
** Function: cast_single_ray
** Casts a single ray for a specific column on the screen.
**
** Arguments:
** 		(t_player *) player: contains information on player position etc.
** 		(t_parse *) parse: contains all information read from .cub file.
**		(double) ange: the angle of the ray to be casted.
**		(int) i: the column on the screen. 
**				 Used to set player->side and player->which_wall.
*/
static double	cast_single_ray(t_player *player, t_parse *parse, \
								double angle, int i)
{
	double	hor_dist;
	double	ver_dist;
	double	distance;
	int		wall_hor;
	int		wall_ver;

	wall_hor = horizontal_intersection(player, angle, parse->map, i);
	wall_ver = vertical_intersection(player, angle, parse->map, i);
	hor_dist = calculate_ray_len(player, player->hor_ray[i].x, \
								player->hor_ray[i].y);
	ver_dist = calculate_ray_len(player, player->ver_ray[i].x, \
								player->ver_ray[i].y);
	if (ver_dist <= hor_dist)
	{
		set_vertical_data(player, angle, i);
		return (ver_dist * cos(player->angle - angle));
	}
	else
	{
		set_horizontal_data(player, angle, i);
		return (hor_dist * cos(player->angle - angle));
	}
}

int	cast_all_rays(t_player *player, t_parse *parse)
{
	int		i;
	double	angle;
	double	angle_increment;

	i = 0;
	angle = player->angle - 0.5 * deg2rad(FOV);
	angle_increment = deg2rad(FOV) / parse->win_width;
	player->rays_array = error_malloc(sizeof(*player->rays_array) * \
									parse->win_width);
	if (player->rays_array == NULL)
		return (-1);
	player->side = error_malloc(sizeof(*player->side) * parse->win_width);
	if (player->side == NULL)
		return (-1);
	while (i < parse->win_width)
	{
		player->rays_array[parse->win_width - 1 - i] = cast_single_ray(\
							player, parse, angle, parse->win_width - 1 - i);
		angle += angle_increment;
		reset_angle(&angle);
		i++;
	}
	return (0);
}
