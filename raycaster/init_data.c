/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

void	raycaster_init(t_data *data)
{
	images_init(&data->images);
	player_init(&data->player);
}

void	images_init(t_images *images)
{
	ft_bzero(&images->main, sizeof(images->mlx));
	ft_bzero(&images->main, sizeof(images->main));
	ft_bzero(&images->north_xpm, sizeof(images->north_xpm));
	ft_bzero(&images->south_xpm, sizeof(images->south_xpm));
	ft_bzero(&images->west_xpm, sizeof(images->west_xpm));
	ft_bzero(&images->east_xpm, sizeof(images->east_xpm));
}

void	player_init(t_player *player)
{
	player->x = -1;;
	player->y = -1;
    player->angle = -1;
    player->speed = -1;
    player->rot_speed = -1;
    player->rays_array = NULL;
    player->side = NULL;
	player->which_wall = NULL;
	player->wall_x_start = -1;	
	player->wall_x_end = -1;
	ray_init(&player->hor_ray);
	ray_init(&player->ver_ray);
}

void	ray_init(t_ray *ray)
{
	ray->x = -1;
	ray->y = -1;
	ray->xa = -1;
	ray->ya = -1;
	ray->error = -1;
}
