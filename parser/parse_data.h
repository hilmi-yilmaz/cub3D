#ifndef PARSE_DATA_H
# define PARSE_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include "parse_structs.h"

# include "parse_resolution.h"
# include "parse_texture.h"
# include "parse_colour.h"
# include "parse_map.h"
# include "../libft/libft.h"

int	parse_data(int fd, t_parse *parse);

#endif