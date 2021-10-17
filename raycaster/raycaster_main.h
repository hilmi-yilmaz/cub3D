#ifndef RAYCASTER_MAIN_H
# define RAYCASTER_MAIN_H

/* System headers */
# include <stddef.h>

/* User defined headers */
# include "../incl/X.h"
# include "../incl/is_linux.h"
# include "raycaster.h"
# include "gameplay.h"
# include "hooks.h"
# include "load_xpm.h"
# include "utils/raycaster_init.h"
# include "utils/raycaster_utils.h"
# include "../parser/utils/parser_utils.h"

/* Macros */
# define UNIT 1

/* Function prototypes */
int	raycaster_main(t_data *data);

#endif