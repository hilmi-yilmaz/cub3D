/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    map_to_3d(t_img *img, double *rays_array, int win_width, int win_height)
{
    int i;
    int height;
    int dist_to_plane;

    i = 0;
    height = 0;
    dist_to_plane = win_width / 2 * tan((float)FOV / 180 * PI / 2);
    //printf("dist_to_plane = %d\n", dist_to_plane);
    while (i < win_width)
    {
        height = (double)UNIT / rays_array[i] * dist_to_plane * WALL_RATIO;
        draw_columns(img, i, height, win_height);
        //printf("%d ", i);
        i++;
    }
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    draw_columns(t_img *img, int column, int wall_height, int win_height)
{
    int start;
    int end;

    //printf("win_height = %d\n", win_height);
    start = (win_height - wall_height) / 2;
    if (start < 0)
        start = 0;
    end = (win_height + wall_height) / 2;
    if (end >= win_height)
        end = win_height - 1;
    while (start < end)
    {
        //printf("start + i = %d\n", start + i);
        //printf("column = %d\n", column);
        my_pixel_put(img, column, start, argb_to_hex(0, 255, 0, 0));
        start++;
    }
}
