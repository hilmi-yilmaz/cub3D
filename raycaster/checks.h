#ifndef CHECKS_H
# define CHECKS_H

#include <stdio.h>
#include <math.h>

# include "raycaster.h"

# include "../libft/libft.h"

# define GLASS 0.1
# define INF 2147483647

int	check_wall(char **map, double x, double y);
int	check_coordinates(double x, double y, char **map);
int	check_next_step(double new_x, double new_y, char **map);

#endif