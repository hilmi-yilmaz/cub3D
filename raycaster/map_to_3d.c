/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    map_to_3d(t_img *img, double *rays_array, int win_width, int win_height)
{
    int		i;
    int		height;
    double	dist_to_plane;

    i = 0;
    height = 0;
    dist_to_plane = win_width / 2 * tan(deg2rad(FOV) / 2);
    while (i < win_width)
    {
        height = 1.0 / rays_array[i] * dist_to_plane * WALL_RATIO;
        draw_columns(img, i, height, win_height);
        i++;
    }
}
