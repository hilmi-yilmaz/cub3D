/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:10:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:11:23 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

/* System headers */
# include <math.h>

/* User defined headers */
# include "../libft/libft.h"
# include "raycaster.h"

/* Macros */
# define GLASS 0.1
# define INF 2147483647

/* Function prototypes */
int	check_wall(char **map, double x, double y);
int	check_coordinates(double x, double y, char **map);
int	check_next_step(double new_x, double new_y, char **map);

#endif