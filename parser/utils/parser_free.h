#ifndef PARSER_FREE_H
# define PARSER_FREE_H

/* System headers */
#include <stdlib.h>

/* User defined headers */
# include "../parser.h"

/* Function prototypes */
void	free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);
void	*free_2d_str_array_if_fails(char **copy, int i);

#endif