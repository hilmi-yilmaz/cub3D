#ifndef CUB3D_H
# define CUB3D_H

/* Include headerfiles */
# include "raycaster/raycaster_structs.h"
# include "parser/parse_structs.h"

# include "parser/parse_main.h"
# include "raycaster/main.h"

# include "raycaster/utils/raycaster_free.h"
# include "parser/utils/parser_free.h"

/* If not defined, we are on OSX */
// # ifndef __linux__
// #  define __linux__ 0
// # endif

// /* Define keybindings for linux and macosx */
// # ifdef __linux__
// #  include "mlx_linux/mlx.h"
// #  define UP_KEY 65362
// #  define DOWN_KEY 65364
// #  define RIGHT_KEY 65363
// #  define LEFT_KEY 65361
// #  define A_KEY 97
// #  define D_KEY 100
// #  define W_KEY 119
// #  define S_KEY 115
// #  define ESC_KEY 65307
// # else
// #  include "mlx/mlx.h"
// #  define UP_KEY 126
// #  define DOWN_KEY 125
// #  define RIGHT_KEY 124
// #  define LEFT_KEY 123
// #  define A_KEY 0
// #  define D_KEY 2
// #  define W_KEY 13
// #  define S_KEY 1
// #  define ESC_KEY 53
// # endif

#endif
