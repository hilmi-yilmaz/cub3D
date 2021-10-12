#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include "../../libft/libft.h"

void	find_player_location(int *x, int *y, char **map);
char	**copy_map(char **map);

#endif