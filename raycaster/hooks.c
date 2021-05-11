/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int hooks(int keycode, t_data *data)
{
    printf("player->x = %f\n", data->player.x);
	printf("player->y = %f\n", data->player.y);
	
	clear_screen(&data->img, data->parse.win_width, data->parse.win_height);
	check_directions(&data->player, data->parse.map);
	printf("direction.north = %d\n\n", data->player.direction.north);
	if (keycode == W_KEY && data->player.direction.north == 0)
		move(&data->player, 0.0, data->player.speed);
	if (keycode == S_KEY && data->player.direction.south == 0)
		move(&data->player, 0.0, -data->player.speed);
	if (keycode == A_KEY)
		move(&data->player, -data->player.speed, 0.0);
	if (keycode == D_KEY)
		move(&data->player, data->player.speed, 0.0);
	if (keycode == RIGHT_KEY)
        data->player.angle += data->player.rot_speed;
    else if (keycode == LEFT_KEY)
        data->player.angle -= data->player.rot_speed;
	reset_angle(&data->player.angle);
	ft_memset(&data->player.direction, '\0', sizeof(data->player.direction));
    cast_all_rays(&data->player, data->parse.win_width, data->parse.map);
	map_to_3d(&data->img, data->player.rays_array, data->parse.win_width, data->parse.win_height);
    free(data->player.rays_array);
	mlx_put_image_to_window(data->img.mlx_ptr, data->img.win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

void	move(t_player *player, double x_local, double y_local)
{
	rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
	player->x += x_local;
	player->y += y_local;
}
