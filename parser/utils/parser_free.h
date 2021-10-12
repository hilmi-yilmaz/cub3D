#ifndef PARSER_FREE_H
# define PARSER_FREE_H

#include <stdlib.h>

# include "../parser.h"

void	free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);

#endif