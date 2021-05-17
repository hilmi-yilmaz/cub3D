/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    map_to_3d(t_img *img, t_player *player, int win_width, int win_height)
{
    int		        i;
    int		        height;
    unsigned int    colour;
    double	        dist_to_plane;

    i = 0;
    height = 0;
    dist_to_plane = win_width / 2 * tan(deg2rad(FOV) / 2);
    while (i < win_width)
    {
        height = 1.0 / player->rays_array[i] * dist_to_plane * WALL_RATIO;
        if (player->side[i] == 'N')
            colour = argb_to_hex(0, 255, 0, 0);
        else if (player->side[i] == 'S')
            colour = argb_to_hex(0, 0, 255, 0);
        else if (player->side[i] == 'W')
            colour = argb_to_hex(0, 127, 0, 0);
        else
            colour = argb_to_hex(0, 0, 127, 0);
        draw_columns(img, i, height, win_height, colour);
        i++;
    }
}
