/* Standard Library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"


void    init(t_data *data)
{
    /* Draw the map */
    draw_map(&data->img, &data->parse);

    /* Find the starting position of the player */
    find_start_location(&data->player, data->parse.map);

    /* Set speed and rotation speed of the player */
    data->player.speed = 1;
    data->player.rot_speed = 0.01 * PI;

    /* Set direction struct to zeros (all paths are free at the beginning */
    data->player.direction.north = 0;
    data->player.direction.west = 0;
    data->player.direction.east = 0;
    data->player.direction.south = 0;

    /* Initialize ray data */
    data->player.ray.hor_error = 0;
    data->player.ray.ver_error = 0;

    /* Draw the player and direction arrow */
    draw_player(&data->img, data->player.x, data->player.y, argb_to_hex(0, 255, 0, 0));
    draw_line(&data->img, &data->player, data->player.angle, 25, argb_to_hex(0, 255, 0, 0));

    /* Calculate the intersection point */
    //horizontal_intersection(&data->player, data->player.angle);
    intersections(&data->player, data->player.angle, data->parse.map, &data->img);

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