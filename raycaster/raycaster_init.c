/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"


void    init(t_data *data)
{
    ft_memset(&data->player, 0, sizeof(data->player));
    find_start_location(&data->player, data->parse.map);
    data->player.speed = 0.1;
    data->player.rot_speed = 0.01 * PI;

	/* Set start angle */
	//data->player.angle = deg2rad(360 - 45);

    cast_all_rays(&data->player, data->parse.win_width, data->parse.map);
	map_to_3d(&data->img, data->player.rays_array, data->parse.win_width, data->parse.win_height);
	mlx_put_image_to_window(data->img.mlx_ptr, data->img.win_ptr, data->img.img_ptr, 0, 0);
    free(data->player.rays_array);
}

void    find_start_location(t_player *player, char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2')
			{
				set_start_location(player, map, i, j);
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void    set_start_location(t_player *player, char **map, int i, int j)
{
    player->x = (j + 0.5) * UNIT; /* check wether value j + 0.5 is not rounded to j */
    player->y = (i + 0.5) * UNIT;
    if (map[i][j] == 'N')
        player->angle = 0.5 * PI;
    else if (map[i][j] == 'W')
        player->angle = 1 * PI;
    else if (map[i][j] == 'S')
        player->angle = 1.5 * PI;
    else
        player->angle = 0 * PI;
}
