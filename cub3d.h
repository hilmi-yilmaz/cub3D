#ifndef CUB3D_H
# define CUB3D_H

//# include "parser/parse.h"
# include "raycaster/raycaster.h"

/* Parser */
# define UNINIT -1	/* Uninitialized value */


# ifdef __linux__
#  include "mlx_linux/mlx.h"
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

/* If not defined, we are on OSX */
# ifndef __linux__
#  define __linux__ 0
# endif

# include "incl/X.h"
# include "libft/libft.h"

// # define LEN_R 1	/* Rename to OFFSET_R */
// # define LEN_NO 2
// # define LEN_SO 2
// # define LEN_WE 2
// # define LEN_EA 2
// # define LEN_S 1
// # define LEN_F 1
// # define LEN_C 1

// # define RGB_DATA_COUNT 3
// # define RESOLUTION_DATA_COUNT 2
// # define MAX_KOMMAS 2

// # define STACK_MAX 10000

# define TRUE 1
# define FALSE 0

// # define UNIT 1
# define EDGE 1
# define INF 2147483647 

#define GLASS 0.1

# define XY_COORDINATES 2

# define PI 3.141592653589793

# define FOV 60

# define WALL_RATIO 2

# define INF 2147483647

# define INF_SMALL 0.0000000000001

#endif
