#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

/* System headers */
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "../../libft/libft.h"
# include "parser_free.h"

/* Function prototypes */
void	find_player_location(int *x, int *y, char **map);
char	**copy_map(char **map);

#endif