/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 15:12:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:12:12 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_UTILS_H
# define RAYCASTER_UTILS_H

/* User defined headers */
# include "../raycaster.h"
# include "raycaster_free.h"

/* Function prototypes */
int				close_window(t_data *data);
void			my_pixel_put(t_img *img, int pos_x, int pos_y, \
								unsigned int colour);
unsigned int	my_pixel_get(t_img *img, int pos_x, int pos_y);
unsigned int	argb_to_hex(int a, int r, int g, int b);

#endif