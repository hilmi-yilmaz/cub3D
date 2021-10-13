#ifndef HOOKS_H
# define HOOKS_H

/* User defined headers */
# include "raycaster.h"
# include "utils/raycaster_utils.h"

/* Macros */
# if __linux__ == 1
#  include "../mlx_linux/mlx.h"
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define A_KEY 97
#  define D_KEY 100
#  define W_KEY 119
#  define S_KEY 115
#  define ESC_KEY 65307
# else
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define A_KEY 0
#  define D_KEY 2
#  define W_KEY 13
#  define S_KEY 1
#  define ESC_KEY 53
# endif

/* Function prototypes */
int	keypress_hook(int keycode, t_data *data);
int	keyrelease_hook(int keycode, t_data *data);

#endif