/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

// void    map_to_3d(t_img *main, t_player *player, int win_width, int win_height)
// {
//     int		        i;
//     int             j;
//     int		        height;
//     unsigned int    colour;
//     double	        dist_to_plane;
//     int             *width_walls;

//     i = 0;
//     j = 0;
//     height = 0;
//     dist_to_plane = win_width / 2 * tan(deg2rad(FOV) / 2);
//     width_walls = width_of_wall(player->which_wall, win_width);

// //-------------------------------------- //
//     // int p = 0;
//     // while (width_walls[p] != -1)
//     // {
//     //     printf("%d ", width_walls[p]);
//     //     p++;
//     // }
//     // printf("\n");
// //-----------------------------------------//

//     while (i < win_width)
//     {
//         height = 1.0 / player->rays_array[i] * dist_to_plane * WALL_RATIO;
//         // if (player->side[i] == 'N')
//         //     colour = argb_to_hex(0, 255, 0, 0);
//         // else if (player->side[i] == 'S')
//         //     colour = argb_to_hex(0, 0, 255, 0);
//         // else if (player->side[i] == 'W')
//         //     colour = argb_to_hex(0, 127, 0, 0);
//         // else
//         //     colour = argb_to_hex(0, 0, 127, 0);
//         colour = argb_to_hex(0, player->which_wall[i] * 20, player->which_wall[i] * 10, player->which_wall[i] * 15);
//         draw_columns(main, i, height, win_height, colour);
//         i++;
//     }
// }

void    v1_map_to_3d(t_img *main, t_player *player, int win_width, int win_height)
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
    dist_to_plane = win_width / 2 * tan(deg2rad(FOV) / 2);
    width_walls = width_of_wall(player->which_wall, win_width);

//-------------------------------------- //
    int p = 0;
    while (width_walls[p] != -1)
    {
        printf("%d ", width_walls[p]);
        p++;
    }
    printf("\n");
//-----------------------------------------//

    while (i < win_width)
    {
        height = 1.0 / player->rays_array[i] * dist_to_plane * WALL_RATIO;
        // if (player->side[i] == 'N')
        //     colour = argb_to_hex(0, 255, 0, 0);
        // else if (player->side[i] == 'S')
        //     colour = argb_to_hex(0, 0, 255, 0);
        // else if (player->side[i] == 'W')
        //     colour = argb_to_hex(0, 127, 0, 0);
        // else
        //     colour = argb_to_hex(0, 0, 127, 0);
        colour = argb_to_hex(0, player->which_wall[i] * 20, player->which_wall[i] * 10, player->which_wall[i] * 15);
        draw_columns(main, i, height, win_height, colour);
        i++;
    }
}

int *width_of_wall(int *which_wall, int width)
{
    int i;
    int i_temp;
    int j;
    int visible_walls;
    int *width_walls;

    i = 0;
    j = 0;
    i_temp = 0;
    visible_walls = amount_visible_walls(which_wall, width);
    width_walls = malloc(sizeof(*width_walls) * (visible_walls + 1));
    while (i < width - 1)
    {
        if (which_wall[i] != which_wall[i + 1] || i + 1 == width - 1)
        {
            width_walls[j] = i_temp + 1;
            i_temp = 0;
            j++;
            i++;
            continue ;
        }
        i++;
        i_temp++;
    }
    width_walls[j - 1] += 1;
    width_walls[j] = -1;

    int p = 0;
    int res = 0;
    while (width_walls[p] != -1)
    {
        res += width_walls[p];
        p++;
    }
    printf("res = %d\n", res);
    return (width_walls);
}

int amount_visible_walls(int *which_wall, int width)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (i < width - 1)
    {
        if (which_wall[i] != which_wall[i + 1])
            count++;
        i++;
    }
    return (count);
}
