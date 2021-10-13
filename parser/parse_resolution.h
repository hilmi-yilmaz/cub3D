#ifndef PARSE_RESOLUTION_H
# define PARSE_RESOLUTION_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"

/* Macros */
# define RESOLUTION_DATA_COUNT 2

/* Function prototypes */
int	parse_resolution(int *win_width, int *win_height, char *line);

#endif