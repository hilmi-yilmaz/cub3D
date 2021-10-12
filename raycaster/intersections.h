#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

#include <stdio.h>
#include <math.h>

# include "math.h"
# include "checks.h"
# include "raycaster_structs.h"

int				horizontal_intersection(t_player *player, double angle, \
										char **map, int i);
int				vertical_intersection(t_player *player, double angle, \
										char **map, int i);
int				expand_ray(t_ray *ray, char **map, double angle, \
							int (*angle_direction)(double));

#endif