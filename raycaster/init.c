/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int	init_window(t_data *data)
{
    int ret;
	
    set_start_location(&data->player, data->parse.map);
    data->player.speed = 0.25;
    data->player.rot_speed = 0.025 * PI;
	draw_floor_ceiling(&data->images.main, &data->parse);
    //ret = load_all_xpm_images(&data->images, &data->parse);
	//if (ret == -1)
	//	return (-1);

    ret = cast_all_rays(&data->player, data->parse.win_width, data->parse.map, &data->parse);
    if (ret == -1)
    {
        free_player(&data->player);
        return (-1);
    }
    ret = map_to_3d_without_texture(data);
    if (ret == -1)
    {
        free_player(&data->player);
        return (-1);
    }
    mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.main.img_ptr, 0, 0);
	free_player(&data->player);
	return (0);
}