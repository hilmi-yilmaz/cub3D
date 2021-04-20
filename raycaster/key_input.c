/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int		key_input(int keycode, t_data *data)
{
	int speed;
	int	wall;
	
	speed = 8;
	remove_current_player(data->img);
	//remove_line(img, img->player.x, img->player.y, img->ray.len * UNIT);
	remove_line(data->img, data->player.angle, 20);
	if (keycode == LEFT_KEY)
	{
		wall = check_wall(data->parse.map, img->player.x - speed - img->player.width / 2, img->player.y);
		if (wall == 0)
			img->player.x -= speed;
	}
	else if (keycode == RIGHT_KEY)
	{
		wall = check_wall(img->info.map, img->player.x + speed + img->player.width / 2 - 1, img->player.y);
		if (wall == 0)
			img->player.x += speed;
	}
	else if (keycode == UP_KEY)
	{
		wall = check_wall(img->info.map, img->player.x, img->player.y - speed - img->player.height / 2);
		if (wall == 0)
			img->player.y -= speed;
	}
	else if (keycode == DOWN_KEY)
	{
		wall = check_wall(img->info.map, img->player.x, img->player.y + speed + img->player.height / 2 - 1);
		if (wall == 0)
			img->player.y += speed;
	}
	else if (keycode == A_KEY)
		img->player.alpha += 0.02 * PI;
	else if (keycode == D_KEY)
		img->player.alpha -= 0.02 * PI;

	/* If the angle is bigger than 2PI, substract 2PI */
	if (img->player.alpha > 2 * PI)
		img->player.alpha -= 2 * PI;
	if (img->player.alpha < -2 * PI)
		img->player.alpha += 2 * PI;
	
	draw_player(img);
	player_location(img);
	draw_line(img, img->player.alpha, 20);
	//cast_rays(img, img->info.win_width);
	//cast_ray(img, img->player.alpha);
	//cast_all_rays(img);
	cast_fov(img);
	//printf("x_unit = %f, y_unit = %f\n", img->player.x_unit, img->player.y_unit);
	printf("x = %d, y = %d, alpha = %f (%f)\n", img->player.x, img->player.y, img->player.alpha, img->player.alpha / PI * 180);
	return (0);
}