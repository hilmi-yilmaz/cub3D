/* Standard library header files */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

// int	cast_rays(t_img *img, int win_width)
// {
// 	int	i;
// 	int angle;
// 	int *wall_hit_point; /* store x and y coordinates of where the ray hits the wall */
// 	float ray_len;
// 	float angle_increment;

// 	i = 0;
// 	angle = img->player.alpha - 0.5 * FOV;
// 	angle_increment = FOV / win_width;
// 	while (i < win_width)
// 	{
// 		/* Fill the wall_hit_point array with x and y value of hit point */
// 		wall_hit_point = intersection(img, angle);
// 		if (wall_hit_point == NULL)
// 		{
// 			i++;
// 			angle += angle_increment;
// 			continue;
// 		}

// 		/* Calculate the length of the ray using square root */
// 		ray_len = sqrt(pow(img->player.x - *(wall_hit_point + 0), 2) + pow(img->player.y - *(wall_hit_point + 1), 2));

// 		/* Free wall_hit_point */
// 		free(wall_hit_point);

// 		/* Draw the ray */
// 		draw_line(img, angle, ray_len);

// 		/* Increment angle and i */
// 		angle += angle_increment;
// 		i++;

// 		break ;
// 	}
// 	return (0);
// }

int	cast_ray(t_img *img)
{
	int		ray_len;
	int	*wall_hit_point;

	wall_hit_point = intersection(img, img->player.alpha);
	ray_len = sqrt(pow(img->player.x - wall_hit_point[0], 2) + pow(img->player.y - wall_hit_point[1], 2));
	//printf("wall hit points: x = %d, y = %d\n", wall_hit_point[0], wall_hit_point[1]);
	draw_line(img, img->player.alpha, ray_len);
	free(wall_hit_point);
	return (0);
}