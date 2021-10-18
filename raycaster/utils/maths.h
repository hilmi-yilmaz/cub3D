/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:13:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:13:08 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

/* System headers */
# include <math.h>

/* User defined headers */
# include "../raycaster.h"

/* Function prototypes */
double			calculate_ray_len(t_player *player, double x, double y);
void			reset_angle(double *angle);
int				unit_circle_upper_lower(double angle);
int				unit_circle_left_right(double angle);
double			deg2rad(double degree);

#endif