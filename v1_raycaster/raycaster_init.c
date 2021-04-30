/* Standard Library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"


void    init(t_data *data)
{
    /* Draw the map */
    draw_map(&data->img, &data->parse);
    find_start_location(&data->player, data->parse.map);
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
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
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
