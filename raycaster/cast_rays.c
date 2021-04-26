/* Standard library header files */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

// int	cast_ray(t_data data, float angle)
// {
// 	int	ray_len;
// 	int	*wall_hit_point;

// 	wall_hit_point = intersection(img, angle);
// 	if (wall_hit_point == NULL)
// 		return (-1);
// 	ray_len = sqrt(pow(img->player.x - wall_hit_point[0], 2) + pow(img->player.y - wall_hit_point[1], 2));
// 	//printf("wall hit points: x = %d, y = %d\n", wall_hit_point[0], wall_hit_point[1]);
// 	draw_line(img, angle, ray_len);
// 	free(wall_hit_point);
// 	return (0);
// }

// int cast_all_rays(t_img *img)
// {
// 	int i;
// 	float angle;
// 	float angle_increment;

// 	i = 0;
// 	angle = img->player.alpha - 0.5 * ((float)FOV / 180 * PI);
// 	angle_increment = (float)FOV / 180 * PI / img->info.win_width;
// 	printf("FOV = %f\n", ((float)FOV / 180 * PI));
// 	printf("angle_increment = %f\n", angle_increment);
// 	while (i < img->info.win_width)
// 	{
// 		cast_ray(img, angle);
// 		i++;
// 		angle += angle_increment;
// 		printf("%d\n", i);
// 	}
// 	return (0);
// }

// int cast_fov(t_data *data)
// {
// 	float first_angle;
// 	float last_angle;

// 	first_angle = data.player.angle - 0.5 * ((float)FOV / 180 * PI);
// 	last_angle = data.player.angle + 0.5 * ((float)FOV / 180 * PI);
// 	cast_ray(data, first_angle);
// 	cast_ray(data, last_angle);
// 	return (0);
// }