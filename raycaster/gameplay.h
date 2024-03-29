/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:11:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:11:38 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

/* System headers */
# include <math.h>

/* User defined headers */
# include "../incl/is_linux.h"
# include "raycaster.h"
# include "cast_rays.h"
# include "map_to_3d_textured.h"
# include "checks.h"
# include "utils/raycaster_utils.h"
# include "utils/maths.h"

# if __LINUX__ == 1
#  include "../mlx_linux/mlx.h"
# else
#  include "../mlx/mlx.h"
# endif

/* Function prototypes */
int	gameplay(t_data *data);

#endif