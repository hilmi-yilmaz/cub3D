#ifndef RAYCASTER_PRINT_H
# define RAYCASTER_PRINT_H

# include <stdio.h>

# include "../raycaster.h"

void	print_intersections(t_player *player, int width);
void	print_ray_data(t_ray ray);
void	print_rays_array(double *rays_array, int width);
void	print_side_array(int *side_array, int width);

#endif