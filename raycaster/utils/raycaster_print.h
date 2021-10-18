/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_print.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:12:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:12:25 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_PRINT_H
# define RAYCASTER_PRINT_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../raycaster.h"

/* Function prototypes */
void	print_intersections(t_player *player, int width);
void	print_ray_data(t_ray ray);
void	print_rays_array(double *rays_array, int width);
void	print_side_array(int *side_array, int width);

#endif