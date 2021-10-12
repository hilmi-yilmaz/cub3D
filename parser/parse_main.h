#ifndef PARSE_MAIN_H
# define PARSE_MAIN_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "parse_structs.h"
# include "parse_data.h"
# include "checks/check_data_completeness.h"
# include "checks/check_map.h"
# include "utils/init.h"
# include "utils/parser_utils.h"
# include "utils/parser_free.h"

int	parse_main(t_parse *parse, char **argv);

#endif