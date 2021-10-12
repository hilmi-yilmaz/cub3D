#ifndef RAYCASTER_MAIN_H
# define RAYCASTER_MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# include "../incl/X.h"
# include "raycaster_structs.h"

# include "gameplay.h"
# include "hooks.h"
# include "load_xpm.h"
# include "../parser/utils/parser_utils.h"
# include "utils/raycaster_init.h"
# include "utils/raycaster_utils.h"

# ifndef __linux__
#  define __linux__ 0
# endif

# define UNIT 1

int	raycaster_main(t_data *data);

#endif