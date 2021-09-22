/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

void    set_player_attributes(t_player *player, char **map)
{
    set_start_location(player, map);
    player->speed = 0.25;
    player->rot_speed = 0.025 * PI;
}