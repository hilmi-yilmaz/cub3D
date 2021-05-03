/* Standard Library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    intersections(t_player *player, double angle, char **map, t_img *img)
{
    /* Reset error values */
    player->ray.hor_error = 0;
    player->ray.ver_error = 0;

    horizontal_intersection(player, player->angle); 
    expand_hor_ray(player, map);
    vertical_intersection(player, player->angle); 
    expand_ver_ray(player, map);
    printf("angle = %f\n", angle / PI * 180);
    printf("hor_x = %d\n", player->ray.hor_x);
    printf("hor_y = %d\n", player->ray.hor_y);
    printf("ver_x = %d\n", player->ray.ver_x);
    printf("ver_y = %d\n", player->ray.ver_y);
    if (player->ray.ver_error != 1)
        my_pixel_put(img, player->ray.ver_x, player->ray.ver_y, argb_to_hex(0, 255, 255, 255));
    if (player->ray.hor_error != 1)
        my_pixel_put(img, player->ray.hor_x, player->ray.hor_y, argb_to_hex(0, 255, 255, 255));
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}


double	calculate_ray_len(t_player *player, int x, int y)
{
	return(sqrt(pow(player->x - x, 2) + pow(player->y - y, 2)));
}

void    check_coordinates(t_ray *ray, char **map)
{
    int hor_x;
    int hor_y;
    int ver_x;
    int ver_y;

    hor_x = ray->hor_x / UNIT;
    hor_y = ray->hor_y / UNIT;
    ver_x = ray->ver_x / UNIT;
    ver_y = ray->ver_y / UNIT;
    if (ray->hor_x < 0 || ray->hor_y < 0)
        ray->hor_error = 1;
    else if (hor_y >= ft_arrlen(map) || hor_x > ft_strlen(map[hor_y]))
        ray->hor_error = 1;
    if (ray->ver_x < 0 || ray->ver_y < 0)
        ray->ver_error = 1;
    else if (ver_y >= ft_arrlen(map) || ver_x > ft_strlen(map[ver_y]))
        ray->ver_error = 1;
}

void    horizontal_intersection(t_player *player, double angle)
{
    /* If the ray is facing up */
    if (unit_circle_upper_lower(player->angle) == 0)
    {
        player->ray.hor_y = (int)(player->y / UNIT) * UNIT - 1;
        player->ray.hor_ya = -UNIT;
    }
    else
    {
        player->ray.hor_y = (int)(player->y / UNIT) * UNIT + UNIT;
        player->ray.hor_ya = UNIT;
    }
    player->ray.hor_x = player->x + (player->y - player->ray.hor_y) / tan(angle);
    player->ray.hor_xa = UNIT / tan(angle);
    if (unit_circle_upper_lower(player->angle) == 1)
        player->ray.hor_xa *= -1;
}

void    vertical_intersection(t_player *player, double angle)
{
    /* If the ray is facing right */
    if (unit_circle_left_right(angle) == 1)
    {
        player->ray.ver_x = (int)(player->x / UNIT) * UNIT + UNIT;
        player->ray.ver_xa = UNIT;
    }
    else
    {
        player->ray.ver_x = (int)(player->x / UNIT) * UNIT - 1;
        player->ray.ver_xa = -UNIT;
    }
    player->ray.ver_y = player->y + (player->x - player->ray.ver_x) * tan(angle);
    player->ray.ver_ya = UNIT * tan(angle);
    if (unit_circle_left_right(player->angle) == 1)
        player->ray.ver_ya *= -1;
}

void    expand_hor_ray(t_player *player, char **map)
{
    int wall;

    wall = 0;
    while (wall == 0)
    {
        check_coordinates(&player->ray, map);
        if (player->ray.hor_error == 1)
            return ;
        wall = check_wall(map, player->ray.hor_x, player->ray.hor_y);
        if (wall == -1)
            return ;
        player->ray.hor_x += player->ray.hor_xa;
        player->ray.hor_y += player->ray.hor_ya;
    }
}

void    expand_ver_ray(t_player *player, char **map)
{
    int wall;

    wall = 0;
    while (wall == 0)
    {
        check_coordinates(&player->ray, map);
        if (player->ray.ver_error == 1)
            return ;
        wall = check_wall(map, player->ray.ver_x, player->ray.ver_y);
        if (wall == -1)
            return ;
        player->ray.ver_x += player->ray.ver_xa;
        player->ray.ver_y += player->ray.ver_ya;
    }

}
