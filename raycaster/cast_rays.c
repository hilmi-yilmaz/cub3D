/* Standard library header files */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int cast_single_ray(t_data *data, float angle)
{
    int ray_len_hor;
	int	ray_len_ver;
	int	min_len;
	
	/* These are the horizontal and vertical intersection points */
    int horizontal[XY_COORDINATES];
    int vertical[XY_COORDINATES];

	min_len = -1;
	ray_len_hor = horizontal_intersection(data, angle, horizontal);
	ray_len_ver = vertical_intersection(data, angle, vertical);
	printf("ray_len_hor = %d\n", ray_len_hor);
	printf("ray_len_ver = %d\n", ray_len_ver);
	if (ray_len_hor >= ray_len_ver)
		min_len = ray_len_ver;
	else if (ray_len_hor < ray_len_ver)
		min_len = ray_len_hor;
	if (ray_len_hor == -1)
		min_len = ray_len_ver;
	if (ray_len_ver == -1)
		min_len = ray_len_hor;
	//printf("min_len = %d\n", min_len);
	// if (min_len != -1)
	// 	draw_line(&data->img, &data->player, angle, min_len);
	return (min_len);
}

void    cast_all_rays(t_data *data)
{
	int i;
	float angle;
	float angle_increment;

	i = 0;
	angle = data->player.angle - 0.5 * ((float)FOV / 180 * PI);
	angle_increment = (float)FOV / 180 * PI / data->parse.win_width;
	//printf("FOV = %f\n", ((float)FOV / 180 * PI));
	//printf("angle_increment = %f\n", angle_increment);
	while (i < data->parse.win_width)
	{
		data->player.rays_array[i] = cast_single_ray(data, angle);
		i++;
		angle += angle_increment;
		//printf("%d\n", i);
	}
}

int cast_fov(t_data *data)
{
	float first_angle;
	float last_angle;

	first_angle = data->player.angle - 0.5 * ((float)FOV / 180 * PI);
	last_angle = data->player.angle + 0.5 * ((float)FOV / 180 * PI);

    draw_line(&data->img, &data->player, first_angle, data->player.rays_array[0]);
    draw_line(&data->img, &data->player, last_angle, data->player.rays_array[data->parse.win_width - 1]);
	//cast_single_ray(data, first_angle);
	//cast_single_ray(data, last_angle);
	return (0);
}

int remove_cast_fov(t_data *data)
{
	float first_angle;
	float last_angle;

	first_angle = data->player.angle - 0.5 * ((float)FOV / 180 * PI);
	last_angle = data->player.angle + 0.5 * ((float)FOV / 180 * PI);

    remove_line(&data->img, &data->player, first_angle, data->player.rays_array[0]);
    remove_line(&data->img, &data->player, last_angle, data->player.rays_array[data->parse.win_width - 1]);
	//cast_single_ray(data, first_angle);
	//cast_single_ray(data, last_angle);
	return (0);
}