/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int	gameplay(t_data *data)
{
    int ret;
	
	reset_angle(&data->player.angle);
    clear_screen(&data->images.main, data->parse.win_width, data->parse.win_height);
    draw_floor_ceiling(&data->images.main, &data->parse);
    ret = cast_all_rays(&data->player, &data->parse);
    if (ret == -1)
        return (-1);
    //print_intersections(&data->player, data->parse.win_width);
    ret = map_to_3d_textured(data);
    if (ret == -1)
        return (-1);
	free_player(&data->player);
    mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.main.img_ptr, 0, 0);
	return (0);
}