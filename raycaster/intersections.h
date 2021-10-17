/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:08:55 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:08:56 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

/* User defined headers */
# include "utils/maths.h"
# include "checks.h"
# include "raycaster.h"

/* Function prototypes */
int				horizontal_intersection(t_player *player, double angle, \
										char **map, int i);
int				vertical_intersection(t_player *player, double angle, \
										char **map, int i);
int				expand_ray(t_ray *ray, char **map, double angle, \
							int (*angle_direction)(double));

#endif