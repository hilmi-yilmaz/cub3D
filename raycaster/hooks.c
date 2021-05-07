/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int hooks(int keycode, t_data *data)
{
    //draw_line(&data->img, &data->player, data->player.angle, 25, argb_to_hex(0, 0, 0, 0));
    clear_screen(&data->img, data->parse.win_width, data->parse.win_height);
    check_directions(&data->player, data->parse.map);
    if (keycode == UP_KEY && data->player.direction.north != -1)
        data->player.y -= data->player.speed;
    else if (keycode == DOWN_KEY && data->player.direction.south != -1)
        data->player.y += data->player.speed;
    else if (keycode == RIGHT_KEY && data->player.direction.east != -1)
        data->player.x += data->player.speed;
    else if (keycode == LEFT_KEY && data->player.direction.west != -1)
        data->player.x -= data->player.speed;
    if (keycode == A_KEY)
        data->player.angle += data->player.rot_speed;
    else if (keycode == D_KEY)
        data->player.angle -= data->player.rot_speed;
    
    /* Reset the angle */
    bounds_angle(&data->player.angle);

    /* Draw the map and player again */
    //printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    //draw_map(&data->img, &data->parse);
    //draw_player(&data->img, data->player.x, data->player.y, argb_to_hex(0, 255, 0, 0));
    //draw_line(&data->img, &data->player, data->player.angle, 25, argb_to_hex(0, 255, 0, 0));
    //intersections(&data->player, data->player.angle, data->parse.map, &data->img);
    //cast_single_ray(&data->img, &data->player, data->player.angle, data->parse.map);
    cast_all_rays(&data->img, &data->player, data->parse.win_width, data->parse.map);
    //print_rays_array(data->player.rays_array, data->parse.win_width);
    map_to_3d(&data->img, data->player.rays_array, data->parse.win_width, data->parse.win_height);
    free(data->player.rays_array);
    free(data->player.angles_array);
    return (0);
}
