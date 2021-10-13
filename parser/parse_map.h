#ifndef PARSE_MAP_H
# define PARSE_MAP_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"
# include "utils/parser_free.h"

/* Function prototypes */
int	parse_map(int fd, t_parse *parse, char **line);

#endif