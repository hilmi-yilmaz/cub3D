/* Standard Library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    intersections(t_player *player, double angle, char **map, t_img *img)
{
    int hor;
    int ver;

    hor = horizontal_intersection(player, player->angle, map);
    ver = vertical_intersection(player, player->angle, map); 
    printf("angle = %f\n", angle / PI * 180);
    printf("hor_x = %d\n", player->hor_ray.x);
    printf("hor_y = %d\n", player->hor_ray.y);
    printf("ver_x = %d\n", player->ver_ray.x);
    printf("ver_y = %d\n", player->ver_ray.y);
    printf("ver_error = %d, hor_error = %d\n", ver, hor);
    if (ver != -1)
        my_pixel_put(img, player->ver_ray.x, player->ver_ray.y, argb_to_hex(0, 255, 255, 255));
    if (hor != -1)
        my_pixel_put(img, player->hor_ray.x, player->hor_ray.y, argb_to_hex(0, 255, 255, 255));
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}


double	calculate_ray_len(t_player *player, int x, int y)
{
	return(sqrt(pow(player->x - x, 2) + pow(player->y - y, 2)));
}

int v1_check_coordinates(int x, int y, char **map)
{
    if (x < 0 || y < 0)
        return (-1);
    x /= UNIT;
    y /= UNIT;
    if (y >= ft_arrlen(map) || x > ft_strlen(map[y]))
        return (-1);
    return (0);
}

// void    check_coordinates(t_ray *ray, char **map)
// {
//     int hor_x;
//     int hor_y;
//     int ver_x;
//     int ver_y;

//     hor_x = ray->hor_x / UNIT;
//     hor_y = ray->hor_y / UNIT;
//     ver_x = ray->ver_x / UNIT;
//     ver_y = ray->ver_y / UNIT;
//     if (ray->hor_x < 0 || ray->hor_y < 0)
//         ray->hor_error = 1;
//     else if (hor_y >= ft_arrlen(map) || hor_x > ft_strlen(map[hor_y]))
//         ray->hor_error = 1;
//     if (ray->ver_x < 0 || ray->ver_y < 0)
//         ray->ver_error = 1;
//     else if (ver_y >= ft_arrlen(map) || ver_x > ft_strlen(map[ver_y]))
//         ray->ver_error = 1;
// }

int horizontal_intersection(t_player *player, double angle, char **map)
{
    int error;
    
    error = 0;
    /* If the ray is facing up */
    if (unit_circle_upper_lower(player->angle) == 0)
    {
        player->hor_ray.y = (int)(player->y / UNIT) * UNIT - 1;
        player->hor_ray.ya = -UNIT;
    }
    else
    {
        player->hor_ray.y = (int)(player->y / UNIT) * UNIT + UNIT;
        player->hor_ray.ya = UNIT;
    }
    player->hor_ray.x = player->x + (player->y - player->hor_ray.y) / tan(angle);
    player->hor_ray.xa = UNIT / tan(angle);
    if (unit_circle_upper_lower(player->angle) == 1)
        player->hor_ray.xa *= -1;
    error = v1_expand_ray(&player->hor_ray, map);
    if (error == -1)
        return (-1);
    return (0);
}

int vertical_intersection(t_player *player, double angle, char **map)
{
    int error;

    error = 0;    
    /* If the ray is facing right */
    if (unit_circle_left_right(angle) == 1)
    {
        player->ver_ray.x = (int)(player->x / UNIT) * UNIT + UNIT;
        player->ver_ray.xa = UNIT;
    }
    else
    {
        player->ver_ray.x = (int)(player->x / UNIT) * UNIT - 1;
        player->ver_ray.xa = -UNIT;
    }
    player->ver_ray.y = player->y + (player->x - player->ver_ray.x) * tan(angle);
    player->ver_ray.ya = UNIT * tan(angle);
    if (unit_circle_left_right(player->angle) == 1)
        player->ver_ray.ya *= -1;
    error = v1_expand_ray(&player->ver_ray, map);
    if (error == -1)
        return (-1);
    return (0);
}

int v1_expand_ray(t_ray *ray, char **map)
{
    int wall;
    int error;
    int xa;
    int ya;

    wall = 0;
    error = 0;
    while (wall == 0)
    {
        error = v1_check_coordinates(ray->x, ray->y, map);
        if (error == -1)
            return (-1);
        printf("ray->x = %d, ray->y = %d\n", ray->x, ray->y);
        wall = check_wall(map, ray->x, ray->y);
        if (wall == -1)
            return (0);
        ray->x += ray->xa;
        ray->y += ray->ya;
    }
}

// void    expand_hor_ray(t_player *player, char **map)
// {
//     int wall;

//     wall = 0;
//     while (wall == 0)
//     {
//         check_coordinates(&player->ray, map);
//         if (player->ray.hor_error == 1)
//             return ;
//         wall = check_wall(map, player->ray.hor_x, player->ray.hor_y);
//         if (wall == -1)
//             return ;
//         player->ray.hor_x += player->ray.hor_xa;
//         player->ray.hor_y += player->ray.hor_ya;
//     }
// }

// void    expand_ver_ray(t_player *player, char **map)
// {
//     int wall;

//     wall = 0;
//     while (wall == 0)
//     {
//         check_coordinates(&player->ray, map);
//         if (player->ray.ver_error == 1)
//             return ;
//         wall = check_wall(map, player->ray.ver_x, player->ray.ver_y);
//         if (wall == -1)
//             return ;
//         player->ray.ver_x += player->ray.ver_xa;
//         player->ray.ver_y += player->ray.ver_ya;
//     }
// }
