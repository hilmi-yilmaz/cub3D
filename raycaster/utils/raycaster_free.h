#ifndef RAYCASTER_FREE_H
# define RAYCASTER_FREE_H

# include "../raycaster_structs.h"
# include "../../parser/utils/parser_free.h"

# ifndef __linux__
#  define __linux__ 0
# endif

#if __linux__ == 1
# include "../../mlx_linux/mlx.h"
#else
# include "../../mlx/mlx.h"
#endif

void	free_all(t_data *data);
void	free_images(t_data *data);
void	free_player(t_player *player);

#endif