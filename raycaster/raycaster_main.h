/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_main.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:11:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:29:38 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_MAIN_H
# define RAYCASTER_MAIN_H

/* System headers */
# include <stddef.h>

/* User defined headers */
//# include "../incl/X.h"
# include "../incl/is_linux.h"
# include "raycaster.h"
# include "gameplay.h"
# include "hooks.h"
# include "load_xpm.h"
# include "utils/raycaster_init.h"
# include "utils/raycaster_utils.h"
# include "../parser/utils/parser_utils.h"

/* Macros */
# define KeyPress 2
# define KeyPressMask (1L<<0)
# define KeyRelease 3
# define KeyReleaseMask (1L<<1)
# define ClientMessage 33
# define NoEventMask 0L
# define DestroyNotify 17
# define StructureNotifyMask (1L<<17)
# define UNIT 1

/* Function prototypes */
int	raycaster_main(t_data *data);

#endif