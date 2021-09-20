/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"


void    init(t_data *data)
{
    ft_memset(&data->player, 0, sizeof(data->player));
    set_start_location(&data->player, data->parse.map);
	printf("player->x = %f, player->y = %f\n", data->player.x, data->player.y);
    data->player.speed = 0.25;
    data->player.rot_speed = 0.025 * PI;

	/* Set the floor and ceiling colour */
	draw_floor_ceiling(&data->images.main, &data->parse);

	/* Set start angle */
	//data->player.angle = deg2rad(360 - 45);

	/* Set start location */
	//data->player.x = 4.5;
	//data->player.y = 8.8;

	/* Load xpm images */
	load_all_xpm_images(data->images.mlx.mlx_ptr, &data->images, &data->parse);

    cast_all_rays(&data->player, data->parse.win_width, data->parse.map, &data->parse);
	v1_map_to_3d(data);
	mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.main.img_ptr, 0, 0);
    //print_side_array(data->player.which_wall, data->parse.win_width);
	free(data->player.rays_array);
	free(data->player.side);
	free(data->player.which_wall);
}

void    set_start_location(t_player *player, char **map)
{
    find_player_location(&player->x, &player->y, map);
	printf("player->x = %f, player->y = %f\n", player->x, player->y);
	if (map[(int)player->y][(int)player->x] == 'N')
        player->angle = 0.5 * PI;
    else if (map[(int)player->y][(int)player->x] == 'W')
        player->angle = 1 * PI;
    else if (map[(int)player->y][(int)player->x] == 'S')
        player->angle = 1.5 * PI;
    else
        player->angle = 0 * PI;
	player->x = (player->x + 0.5) * UNIT;
    player->y = (player->y + 0.5) * UNIT;
}
