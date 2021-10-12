#ifndef PARSE_MAP_H
# define PARSE_MAP_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "parser.h"

# include "../libft/libft.h"

# include "utils/parser_free.h"

int	parse_map(int fd, t_parse *parse, char *line);

#endif