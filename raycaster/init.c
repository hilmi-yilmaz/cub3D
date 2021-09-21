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

	/* Load xpm images */
	ret = load_all_xpm_images(&data->images, &data->parse);
	if (ret == -1)
		return (-1);

    cast_all_rays(&data->player, data->parse.win_width, data->parse.map, &data->parse);
	map_to_3d_without_texture(data);
	mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.main.img_ptr, 0, 0);
	free(data->player.rays_array);
	free(data->player.side);
	free(data->player.which_wall);
	return (0);
}

void    set_start_location(t_player *player, char **map)
{
    int	x;
	int	y;
	
	find_player_location(&x, &y, map);
	if (map[y][x] == 'N')
        player->angle = 0.5 * PI;
    else if (map[y][x] == 'W')
        player->angle = 1 * PI;
    else if (map[y][x] == 'S')
        player->angle = 1.5 * PI;
    else
        player->angle = 0 * PI;
	player->x = (x + 0.5) * UNIT;
    player->y = (y + 0.5) * UNIT;
}