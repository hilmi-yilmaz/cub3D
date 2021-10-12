#ifndef PRINT_H
# define PRINT_H

# include <stdio.h>
#include "parse_structs.h"

void	find_player_location(int *x, int *y, char **map);
char	**copy_map(char **map);

#endif