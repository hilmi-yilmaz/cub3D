/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/11 11:16:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int	horizontal_intersection(t_player *player, double angle, char **map, int i)
{	
	if (unit_circle_upper_lower(angle) == 0)
	{
		player->hor_ray[i].y = floor(player->y);
		player->hor_ray[i].ya = -1.0;
	}
	else
	{
		player->hor_ray[i].y = floor(player->y) + 1.0;
		player->hor_ray[i].ya = 1.0;
	}
	player->hor_ray[i].x = player->x + \
							(player->y - player->hor_ray[i].y) / tan(angle);
	player->hor_ray[i].xa = 1.0 / tan(angle);
	if (unit_circle_upper_lower(angle) == 1)
		player->hor_ray[i].xa *= -1;
	return (expand_ray(&player->hor_ray[i], map, angle, \
						unit_circle_upper_lower));
}

int	vertical_intersection(t_player *player, double angle, char **map, int i)
{
	if (unit_circle_left_right(angle) == 3)
	{
		player->ver_ray[i].x = floor(player->x) + 1.0;
		player->ver_ray[i].xa = 1.0;
	}
	else
	{
		player->ver_ray[i].x = floor(player->x);
		player->ver_ray[i].xa = -1.0;
	}
	player->ver_ray[i].y = player->y + \
							(player->x - player->ver_ray[i].x) * tan(angle);
	player->ver_ray[i].ya = 1.0 * tan(angle);
	if (unit_circle_left_right(angle) == 3)
		player->ver_ray[i].ya *= -1;
	return (expand_ray(&player->ver_ray[i], map, angle, \
						unit_circle_left_right));
}

int	expand_ray(t_ray *ray, char **map, double angle, \
				int (*angle_direction)(double))
{
	int	wall;
	int	dir;

	dir = angle_direction(angle);
	wall = 0;
	while (wall == 0)
	{
		if (dir == 0)
			wall = check_wall(map, ray->x, ray->y - 1.0);
		else if (dir == 1)
			wall = check_wall(map, ray->x, ray->y);
		else if (dir == 2)
			wall = check_wall(map, ray->x - 1.0, ray->y);
		else
			wall = check_wall(map, ray->x, ray->y);
		if (wall > 0)
			return (wall);
		if (wall == -1)
			return (-1);
		ray->x += ray->xa;
		ray->y += ray->ya;
	}
	return (0);
}
