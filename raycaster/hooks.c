/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int hooks(int keycode, t_data *data)
{	
	clear_screen(&data->img, data->parse.win_width, data->parse.win_height);
	if (keycode == W_KEY)
		move(&data->player, 0.0, data->player.speed, data->parse.map);
	if (keycode == S_KEY)
		move(&data->player, 0.0, -data->player.speed, data->parse.map);
	if (keycode == A_KEY)
		move(&data->player, -data->player.speed, 0.0, data->parse.map);
	if (keycode == D_KEY)
		move(&data->player, data->player.speed, 0.0, data->parse.map);
	if (keycode == RIGHT_KEY)
        data->player.angle -= data->player.rot_speed;
    else if (keycode == LEFT_KEY)
        data->player.angle += data->player.rot_speed;
	reset_angle(&data->player.angle);
	draw_floor_ceiling(&data->img, &data->parse);
    cast_all_rays(&data->player, data->parse.win_width, data->parse.map);
	map_to_3d(&data->img, &data->player, data->parse.win_width, data->parse.win_height);
	print_side_array(data->player.which_wall, data->parse.win_width);
    free(data->player.rays_array);
	free(data->player.side);
	free(data->player.which_wall);
	mlx_put_image_to_window(data->img.mlx_ptr, data->img.win_ptr, data->img.img_ptr, 0, 0);
	printf("player->x       = %f\n", data->player.x);
	printf("player->y       = %f\n", data->player.y);
	printf("player->angle   = %f\n", data->player.angle / PI * 180);

	printf("\n");
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
