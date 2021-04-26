/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int		key_input(int keycode, t_data *data)
{
	int speed;
	int	wall;
	
	speed = 8;
	remove_current_player(&data->img, &data->player);
	//remove_line(img, img->player.x, img->player.y, img->ray.len * UNIT);
	remove_line(&data->img, &data->player, data->player.angle, 20);
	remove_cast_fov(data);
	if (keycode == LEFT_KEY)
	{
		wall = check_wall(data->parse.map, data->player.x - speed - data->player.width / 2, data->player.y);
		if (wall == 0)
			data->player.x -= speed;
	}
	else if (keycode == RIGHT_KEY)
	{
		wall = check_wall(data->parse.map, data->player.x + speed + data->player.width / 2 - 1, data->player.y);
		if (wall == 0)
			data->player.x += speed;
	}
	else if (keycode == UP_KEY)
	{
		wall = check_wall(data->parse.map, data->player.x, data->player.y - speed - data->player.height / 2);
		if (wall == 0)
			data->player.y -= speed;
	}
	else if (keycode == DOWN_KEY)
	{
		wall = check_wall(data->parse.map, data->player.x, data->player.y + speed + data->player.height / 2 - 1);
		if (wall == 0)
			data->player.y += speed;
	}
	else if (keycode == A_KEY)
		data->player.angle += 0.02 * PI;
	else if (keycode == D_KEY)
		data->player.angle -= 0.02 * PI;

	/* If the angle is bigger than 2PI, substract 2PI */
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	if (data->player.angle < -2 * PI)
		data->player.angle += 2 * PI;
	
	draw_player(&data->img, &data->player);
	player_location(&data->player);
	draw_line(&data->img, &data->player, data->player.angle, 20);
	//cast_rays(img, img->info.win_width);
	//cast_ray(img, img->player.alpha);
	//cast_all_rays(img);
	//cast_fov(data);
	//cast_single_ray(data, data->player.angle);
	cast_all_rays(data);
	print_rays(data->player.rays_array, data->parse.win_width);
	cast_fov(data);
	//printf("x_unit = %f, y_unit = %f\n", img->player.x_unit, img->player.y_unit);
	//printf("x = %d, y = %d, alpha = %f (%f)\n", img->player.x, img->player.y, img->player.alpha, img->player.alpha / PI * 180);
	return (0);
}