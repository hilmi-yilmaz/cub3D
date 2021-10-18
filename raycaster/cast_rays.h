/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:11:58 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:11:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_RAYS_H
# define CAST_RAYS_H

/* System headers */
# include <math.h>

/* User defined headers */
# include "utils/maths.h"
# include "intersections.h"
# include "raycaster.h"

/* Function prototypes */
void	cast_all_rays(t_player *player, t_parse *parse);

#endif