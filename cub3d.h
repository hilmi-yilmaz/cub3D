#ifndef CUB3D_H
# define CUB3D_H

# ifdef IS_LINUX
#  include "mlx_linux/mlx.h"
#  include <X11/X.h>
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
# else
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define KeyPress 2
#  define KeyPressMask 1L<<0
#  define NoEventMask 1L<<0
#  define DestroyNotify 17
#  define StructureNotifyMask 1L<<17
# endif

typedef struct s_img
{
    void            *mlx_ptr;
    void            *win_ptr;
    void            *img_ptr;
    void            *img_addr;

    int             bits_per_pixel;
    int             line_size;
    int             endian;

    unsigned int    floor_colour;
    unsigned int    ceiling_colour;

}                   t_img;

typedef struct s_info
{
    int     win_width;
    int     win_height;

    char    *north_text;
    char    *south_text;
    char    *west_text;
    char    *east_text;

    char    *sprite_text;

    int     floor_colour[3];
    int     ceiling_colour[3];

}                   t_info;

/* Parsing data */
void    parse_data(t_info *info, char **argv);
void    parse_resolution(t_info *info, char *line);

/* Utils */
int skip_spaces(char *str);

/* Temporary helper functions */
void    print_info(t_info *info);

#endif