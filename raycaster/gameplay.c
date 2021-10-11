/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

/* Define for 2D rotation matrix */
#define ROWS 2
#define COLUMNS 2

static void	rotate_vector(double *x, double *y, double angle)
{	
	double	x_temp;
	double	y_temp;
	double	rot_matrix[ROWS][COLUMNS];

	x_temp = *x;
	y_temp = *y;
	rot_matrix[0][0] = cos(angle);
	rot_matrix[0][1] = sin(angle);
	rot_matrix[1][0] = -sin(angle);
	rot_matrix[1][1] = cos(angle);
	*x = rot_matrix[0][0] * x_temp + rot_matrix[0][1] * y_temp;
	*y = rot_matrix[1][0] * x_temp + rot_matrix[1][1] * y_temp;
}

static int	move(t_player *player, double x_local, double y_local, char **map)
{
	rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
	if (check_next_step(player->x + x_local, player->y + y_local, map) == 1)
		return (-1);
	player->x += x_local;
	player->y += y_local;
	return (0);
}

static void	move_player(t_data *data)
{	
	if (data->key_handler.w_key == 1)
		move(&data->player, 0.0, data->player.speed, data->parse.map);
	if (data->key_handler.s_key == 1)
		move(&data->player, 0.0, -data->player.speed, data->parse.map);
	if (data->key_handler.d_key == 1)
		move(&data->player, -data->player.speed, 0.0, data->parse.map);
	if (data->key_handler.a_key == 1)
		move(&data->player, data->player.speed, 0.0, data->parse.map);
	if (data->key_handler.right_key == 1)
		data->player.angle -= data->player.rot_speed;
	else if (data->key_handler.left_key == 1)
		data->player.angle += data->player.rot_speed;
}

int	gameplay(t_data *data)
{
	reset_angle(&data->player.angle);
	draw_floor_ceiling(&data->images.main, &data->parse);
	move_player(data);
	cast_all_rays(&data->player, &data->parse);
	map_to_3d_textured(data);
	mlx_put_image_to_window(data->images.mlx.mlx_ptr, \
							data->images.mlx.win_ptr, \
							data->images.main.img_ptr, 0, 0);
	return (0);
}
