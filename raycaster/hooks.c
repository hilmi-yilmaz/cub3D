/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int hooks(int keycode, t_data *data)
{	
	int ret;

	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == W_KEY)
		move(&data->player, 0.0, data->player.speed, data->parse.map);
	if (keycode == S_KEY)
		move(&data->player, 0.0, -data->player.speed, data->parse.map);
	if (keycode == D_KEY)
		move(&data->player, -data->player.speed, 0.0, data->parse.map);
	if (keycode == A_KEY)
		move(&data->player, data->player.speed, 0.0, data->parse.map);
	if (keycode == RIGHT_KEY)
        data->player.angle -= data->player.rot_speed;
    else if (keycode == LEFT_KEY)
        data->player.angle += data->player.rot_speed;
	//ret = gameplay(data);
	if (ret == -1)
		return (-1);
    return (0);
}

int	move(t_player *player, double x_local, double y_local, char **map)
{
	rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);

	/* Rotate around the new position and see if the radius of the player is free */
	if (check_next_step(player->x + x_local, player->y + y_local, map) == 1)
		return (-1);
	player->x += x_local;
	player->y += y_local;
	return (0);
}
