#ifndef RAYCASTER_UTILS_H
# define RAYCASTER_UTILS_H

# include "../raycaster_structs.h"

# include "raycaster_free.h"

int				close_window(t_data *data);
void			my_pixel_put(t_img *img, int pos_x, int pos_y, \
								unsigned int colour);
unsigned int	my_pixel_get(t_img *img, int pos_x, int pos_y);
unsigned int	argb_to_hex(int a, int r, int g, int b);

#endif