/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:15:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:40:52 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

double	calculate_ray_len(t_player *player, double x, double y)
{
	return (sqrt(pow(fabs(player->x - x), 2) + pow(fabs(player->y - y), 2)));
}

void	reset_angle(double *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

double	deg2rad(double degree)
{
	return (degree / 180 * PI);
}

/* 
** The unit_circle_upper_lower determines whether the direction is facing
** north or south.
**
** Arguments:
**		(double) angle:	the angle for which to determine the direction 
**						(north or south)
**
** Returns:
**		(int)	0 or 1: 0 if angle points to the north
**						1 if angle points to the south.
*/

int	unit_circle_upper_lower(double angle)
{
	if ((angle >= 0 && angle < PI))
		return (0);
	return (1);
}

/* 
** The unit_circle_left_right determines whether the direction is facing
** left of right.
**
** Arguments:
**		(double) angle:	the angle for which to determine the direction
**						(left or right)
**
** Returns:
**		(int)	2 or 3: 2 if angle points to the left
**						3 if angle points to the right.
*/

int	unit_circle_left_right(double angle)
{
	angle -= 0.5 * PI;
	reset_angle(&angle);
	return (unit_circle_upper_lower(angle) + 2);
}
