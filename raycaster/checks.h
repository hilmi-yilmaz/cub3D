#ifndef CHECKS_H
# define CHECKS_H

/* System headers */
#include <math.h>

/* User defined headers */
# include "../libft/libft.h"
# include "raycaster.h"

/* Macros */
# define GLASS 0.1
# define INF 2147483647

/* Function prototypes */
int	check_wall(char **map, double x, double y);
int	check_coordinates(double x, double y, char **map);
int	check_next_step(double new_x, double new_y, char **map);

#endif