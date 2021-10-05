/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

void	raycaster_init(t_data *data)
{
	images_init(&data->images);
	player_init(&data->player, data->parse.win_width);
}

void	images_init(t_images *images)
{
	ft_bzero(&images->mlx, sizeof(images->mlx));
	ft_bzero(&images->main, sizeof(images->main));
	ft_bzero(&images->north_xpm, sizeof(images->north_xpm));
	ft_bzero(&images->south_xpm, sizeof(images->south_xpm));
	ft_bzero(&images->west_xpm, sizeof(images->west_xpm));
	ft_bzero(&images->east_xpm, sizeof(images->east_xpm));
}

void	player_init(t_player *player, int width)
{
	int i;

	i = 0;
	player->x = -1;;
	player->y = -1;
    player->angle = -1;
    player->speed = 0.05;
    player->rot_speed = 0.005 * PI;
    player->rays_array = NULL;
    player->side = NULL;
	player->hor_ray = malloc(sizeof(*player->hor_ray) * width);
	player->ver_ray = malloc(sizeof(*player->ver_ray) * width);
	while (i < width)
	{
		ray_init(&player->hor_ray[i]);
		ray_init(&player->ver_ray[i]);
		i++;
	}
}

void	ray_init(t_ray *ray)
{
	ray->x = -1;
	ray->y = -1;
	ray->xa = -1;
	ray->ya = -1;
	ray->error = -1;
}
