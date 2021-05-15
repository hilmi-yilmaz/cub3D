/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int hooks(int keycode, t_data *data)
{
    printf("player->x = %f\n", data->player.x);
	printf("player->y = %f\n", data->player.y);
	
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
        data->player.angle += data->player.rot_speed;
    else if (keycode == LEFT_KEY)
        data->player.angle -= data->player.rot_speed;
	reset_angle(&data->player.angle);
	ft_memset(&data->player.direction, '\0', sizeof(data->player.direction));
    cast_all_rays(&data->player, data->parse.win_width, data->parse.map);
	map_to_3d(&data->img, data->player.rays_array, data->parse.win_width, data->parse.win_height);
    free(data->player.rays_array);
	mlx_put_image_to_window(data->img.mlx_ptr, data->img.win_ptr, data->img.img_ptr, 0, 0);
	printf("\n");
    return (0);
}

int	move(t_player *player, double x_local, double y_local, char **map)
{
	double	x_local_copy;
	double	y_local_copy;
	int		wall;
	
	x_local_copy = x_local;
	y_local_copy = y_local;
	rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
	wall = wall_collision(map, player->x + x_local, player->y + y_local);
	if (wall == 1)
	{
		x_local = x_local_copy;
		y_local = distance_to_wall(player, map);
		printf("Distance to wall = %f\n", y_local);
		rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
	}
	player->x += x_local;
	player->y += y_local;
	return (0);
}

double	distance_to_wall(t_player *player, char **map)
{
	t_player player_1;
	double distance;

	player_1.x = player->x;
	player_1.y = player->y;
	distance = cast_single_ray(&player_1, player->angle, map);
	return (distance);
}
