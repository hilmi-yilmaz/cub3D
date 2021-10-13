#ifndef RAYCASTER_FREE_H
# define RAYCASTER_FREE_H

/* User defined headers */
# include "../raycaster.h"
# include "../../parser/utils/parser_free.h"

# if __linux__ == 1
#  include "../../mlx_linux/mlx.h"
# else
#  include "../../mlx/mlx.h"
# endif

/* Macros */
# ifndef __linux__
#  define __linux__ 0
# endif

/* Function prototypes */
void	free_all(t_data *data);
void	free_images(t_data *data);
void	free_player(t_player *player);

#endif