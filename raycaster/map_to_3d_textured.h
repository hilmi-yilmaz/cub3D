/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_3d_textured.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:11:48 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:15:58 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TO_3D_TEXTURED_H
# define MAP_TO_3D_TEXTURED_H

/* System headers */
# include <stdlib.h>
# include <math.h>

/* User defined headers */
# include "raycaster.h"
# include "utils/maths.h"
# include "utils/raycaster_utils.h"

/* Macros */
# define WALL_RATIO 2

/* Data structures */
typedef struct s_map3d
{
	int		column;
	int		height;
	double	textwidth;
}				t_map3d;

/* Function prototypes */
void	map_to_3d_textured(t_data *data);

#endif