#ifndef PARSE_INIT_H
# define PARSE_INIT_H

/* System headers */
# include <stddef.h>

/* User defined headers */
# include "../parser.h"

/* Macros */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512

/* Function prototypes */
void	parse_init(t_parse *parse);
void	recursion_management_init(t_recursion_management *rec_man);

#endif