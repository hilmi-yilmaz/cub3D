/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_xpm.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:09:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 20:48:27 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_XPM_H
# define LOAD_XPM_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../incl/is_linux.h"
# include "raycaster.h"

# if __LINUX__ == 1
#  include "../mlx_linux/mlx.h"
# else
#  include "../mlx/mlx.h"
# endif

/* Function prototypes */
int	load_all_xpm_images(t_data *data);

#endif