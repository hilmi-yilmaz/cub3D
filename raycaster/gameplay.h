#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "raycaster.h"

# include "utils/raycaster_utils.h"
# include "checks.h"
# include "utils/maths.h"
# include "cast_rays.h"
# include "map_to_3d_textured.h"

#if __linux__ == 1
# include "../mlx_linux/mlx.h"
#else
# include "../mlx/mlx.h"
#endif

int	gameplay(t_data *data);

#endif