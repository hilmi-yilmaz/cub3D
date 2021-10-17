#ifndef RAYCASTER_FREE_H
# define RAYCASTER_FREE_H

/* User defined headers */
# include "../../incl/is_linux.h"
# include "../raycaster.h"
# include "../../parser/utils/parser_free.h"

# if __LINUX__ == 1
#  include "../../mlx_linux/mlx.h"
# else
#  include "../../mlx/mlx.h"
# endif

/* Function prototypes */
void	free_all(t_data *data);
void	free_images(t_data *data);
void	free_player(t_player *player);

#endif