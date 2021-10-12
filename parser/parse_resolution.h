#ifndef PARSE_RESOLUTION_H
# define PARSE_RESOLUTION_H

# include <stdio.h>
# include "parse_structs.h"

# include "../libft/libft.h"

# define RESOLUTION_DATA_COUNT 2

int	parse_resolution(int *win_width, int *win_height, char *line);

#endif