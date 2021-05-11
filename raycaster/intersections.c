/* Standard Library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    intersections(t_player *player, double angle, char **map, t_img *img)
{
    int hor;
    int ver;

    hor = horizontal_intersection(player, angle, map, img);
    ver = vertical_intersection(player, angle, map, img);
    printf("angle=%8f ", angle);
    printf("hor_x=%8f ", player->hor_ray.x);
    printf("hor_y=%8f ", player->hor_ray.y);
    printf("ver_x=%8f ", player->ver_ray.x);
    printf("ver_y=%8f ", player->ver_ray.y);
    // printf("ver_error = %d, hor_error = %d\n", ver, hor);
    //if (ver != -1)
        //my_pixel_put(img, (int)player->ver_ray.x, (int)player->ver_ray.y, argb_to_hex(0, 255, 255, 255));
    //if (hor != -1)
        //my_pixel_put(img, (int)player->hor_ray.x, (int)player->hor_ray.y, argb_to_hex(0, 255, 255, 255));
    //mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

int horizontal_intersection(t_player *player, double angle, char **map, t_img *img)
{
    int error;
   
    //---printf("horizontal intersections\n");
    error = 0;
    /* If the ray is facing up */
    if (unit_circle_upper_lower(angle) == 0)
    {
        printf("up ");
		player->hor_ray.y = (player->y / UNIT) * UNIT - 1;
        player->hor_ray.ya = -UNIT;
    }
    else
    {
        printf("down ");
		player->hor_ray.y = (player->y / UNIT) * UNIT + UNIT;
        player->hor_ray.ya = UNIT;
    }
    player->hor_ray.x = player->x + (player->y - player->hor_ray.y) / tan(angle);
    player->hor_ray.xa = UNIT / tan(angle);
    if (unit_circle_upper_lower(angle) == 1)
        player->hor_ray.xa *= -1;
    error = expand_ray(&player->hor_ray, map, img, angle);
    if (error == -1)
        return (-1);
    return (0);
}

int vertical_intersection(t_player *player, double angle, char **map, t_img *img)
{
    int error;

    //---printf("vertical intersections\n");
    error = 0;    
    /* If the ray is facing right */
    if (unit_circle_left_right(angle) == 1)
    {
        printf("right ");
		player->ver_ray.x = (player->x / UNIT) * UNIT + UNIT;
        player->ver_ray.xa = UNIT;
    }
    else
    {
        printf("left ");
		player->ver_ray.x = (player->x / UNIT) * UNIT - 1;
        player->ver_ray.xa = -UNIT;
    }
    player->ver_ray.y = player->y + (player->x - player->ver_ray.x) * tan(angle);
    player->ver_ray.ya = UNIT * tan(angle);
    if (unit_circle_left_right(angle) == 1)
        player->ver_ray.ya *= -1;
    error = expand_ray(&player->ver_ray, map, img, angle);
    if (error == -1)
        return (-1);
    return (0);
}

int expand_ray(t_ray *ray, char **map, t_img *img, double angle)
{
    int wall;
    int wall_corners;
    int error;

    wall = 0;
    wall_corners = 0;
    error = 0;
    while (wall == 0)
    {
        error = check_coordinates(ray->x, ray->y, map);
        if (error == -1)
            return (-1);
        wall = check_wall(map, ray->x, ray->y);
        //wall_corners = check_wall_corners(map, ray->x, ray->y, angle);
        if (wall == -1 || wall_corners == -1)// || wall2 == -1 || wall1 == -1)
            return (0);
        ///---printf("x = %f, y = %f\n", ray->x, ray->y);
        //my_pixel_put(img, (int)ray->x, (int)ray->y, argb_to_hex(0, 255, 255, 255));
        ray->x += ray->xa;
        ray->y += ray->ya;
    }
    return (0);
}
