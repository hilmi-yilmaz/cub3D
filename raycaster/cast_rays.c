/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

double  cast_single_ray(t_img *img, t_player *player, double angle, char **map)
{
    double  hor_distance;
    double  ver_distance;
    double  ray_len;

    
    intersections(player, angle, map, img);
	// printf("\n----\n");
	// printf("player->x = %f\n", player->x);
	// printf("player->y = %f\n", player->y);
	// printf("angle = %f\n", angle);
	// printf("player->hor_ray.x = %f\n", player->hor_ray.x);
	// printf("player->hor_ray.y = %f\n", player->hor_ray.y);
	// printf("player->ver_ray.x = %f\n", player->ver_ray.x);
	// printf("player->ver_ray.y = %f\n", player->ver_ray.y);
	// printf("player->hor_ray.xa = %f\n", player->hor_ray.xa);
	// printf("player->hor_ray.ya = %f\n", player->hor_ray.ya);
	// printf("player->ver_ray.xa = %f\n", player->ver_ray.xa);
	// printf("player->ver_ray.ya = %f\n", player->ver_ray.ya);
    hor_distance = calculate_ray_len_1(player, player->hor_ray.x, angle);
    ver_distance = calculate_ray_len_1(player, player->ver_ray.x, angle);
	// printf("hor_distance = %f\n", hor_distance);
	// printf("ver_distance = %f\n", ver_distance);
    if (hor_distance >= ver_distance)
    {
        ray_len = ver_distance;
        //my_pixel_put(img, (int)player->ver_ray.x, (int)player->ver_ray.y, argb_to_hex(0, 255, 255, 255));
    }
    else
    {
        ray_len = hor_distance;
        //my_pixel_put(img, (int)player->hor_ray.x, (int)player->hor_ray.y, argb_to_hex(0, 255, 255, 255));
    }

	printf("ray_len=%.8f ", ray_len);

    /* Remove fisheye effect */
    ray_len *= cos(player->angle - angle);
	printf("ray_len=%.8f\n", ray_len);

    //draw_line(img, player, angle, ray_len, argb_to_hex(0, 255, 0, 0));
    return (ray_len);
}

int cast_all_rays(t_img *img, t_player *player, int width, char **map)
{
    int     i;
    double  angle;
    double  angle_increment;

    i = 0;
    angle = player->angle - 0.5 * ((double)FOV / 180 * PI);
    angle_increment = ((double)FOV / 180 * PI) / width;
    player->rays_array = malloc(sizeof(double) * width);
    player->angles_array = malloc(sizeof(double) * width);
    while (i < width)
    {
        player->rays_array[i] = cast_single_ray(img, player, angle, map);
        //draw_line(img, player, angle, player->rays_array[i], argb_to_hex(0, 255, 0, 0));
        player->angles_array[i] = angle;
        angle += angle_increment;
        bounds_angle(&angle);
        i++;
    }
    /* Draw fov */
    //draw_line(img, player, player->angles_array[0], player->rays_array[0], argb_to_hex(0, 255, 0, 0));
    //draw_line(img, player, player->angles_array[width - 1], player->rays_array[width - 1], argb_to_hex(0, 255, 0, 0));

    //mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
    // printf("\n");
    //print_rays_array(player->rays_array, width);
    //free(player->rays_array);
    free(player->angles_array);
    return (0);
}

