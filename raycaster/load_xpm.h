#ifndef LOAD_XPM_H
# define LOAD_XPM_H

# include "stddef.h"

# include "raycaster.h"

#if __linux__ == 1
# include "../mlx_linux/mlx.h"
#else
# include "../mlx/mlx.h"
#endif

int	load_all_xpm_images(t_data *data);

#endif