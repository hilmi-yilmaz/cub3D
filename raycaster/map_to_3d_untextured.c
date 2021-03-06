/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int     map_to_3d_untextured(t_data *data)
{
    int		        i;
    int             j;
    int		        height;
    unsigned int    colour;
    double	        dist_to_plane;
    int             *width_walls;

    i = 0;
    j = 0;
    height = 0;
    dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
    width_walls = width_of_wall(data->player.which_wall, data->parse.win_width); // CONTINUE HERE
    if (width_walls == NULL)
        return (-1);

    /* ----------------------------------- print width walls ---------------------------- */
    int p = 0;
    int total = 0;
    while (width_walls[p] != -1)
    {
        printf("%d ", width_walls[p]);
        total += width_walls[p];
        p++;
    }
    printf("\ntotal = %d\n", total);
    printf("player->wall_x_start = %f\n", data->player.wall_x_start);
    printf("player->wall_x_end = %f\n", data->player.wall_x_end);
    /* ---------------------------------------------------------------------------------- */

    while (i < data->parse.win_width)
    {
        height = 1.0 / data->player.rays_array[i] * dist_to_plane * WALL_RATIO;
        colour = argb_to_hex(0, data->player.which_wall[i] * 20, data->player.which_wall[i] * 10, data->player.which_wall[i] * 15);
        draw_columns(&data->images.main, i, height, data->parse.win_height, colour);
        i++;
    }
	free(width_walls);
    return (0);
}