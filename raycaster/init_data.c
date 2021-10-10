/* Standard Library header files */
#include <stdio.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

/*
** Initialize all images.
*/
static void	images_init(t_images *images)
{
	ft_bzero(&images->mlx, sizeof(images->mlx));
	ft_bzero(&images->main, sizeof(images->main));
	ft_bzero(&images->north_xpm, sizeof(images->north_xpm));
	ft_bzero(&images->south_xpm, sizeof(images->south_xpm));
	ft_bzero(&images->west_xpm, sizeof(images->west_xpm));
	ft_bzero(&images->east_xpm, sizeof(images->east_xpm));
}

/*
** Initialize the ray struct.
*/
static void	ray_init(t_ray *ray)
{
	ray->x = -1;
	ray->y = -1;
	ray->xa = -1;
	ray->ya = -1;
	ray->error = -1;
}

/*
** Initialize the player struct.
*/
static int	player_init(t_player *player, int width)
{
	int	i;

	i = 0;
	player->x = -1;
	player->y = -1;
	player->angle = -1;
	player->speed = 0.05;
	player->rot_speed = 0.008 * PI;
	player->rays_array = NULL;
	player->side = NULL;
	player->hor_ray = error_malloc(sizeof(*player->hor_ray) * width);
	if (player->hor_ray == NULL)
		return (-1);
	player->ver_ray = error_malloc(sizeof(*player->ver_ray) * width);
	if (player->ver_ray == NULL)
		return (-1);
	while (i < width)
	{
		ray_init(&player->hor_ray[i]);
		ray_init(&player->ver_ray[i]);
		i++;
	}
	return (0);
}

/*
** Initialize moving flags.
*/

static void	keyflags_init(t_mlx_key_handler *keys)
{
	keys->w_key = 0;
	keys->s_key = 0;
	keys->d_key = 0;
	keys->a_key = 0;
	keys->right_key = 0;
	keys->left_key = 0;
}

/* 
** Initialize the images and player structs.
*/
int	raycaster_init(t_data *data)
{
	int	ret;

	images_init(&data->images);
	ret = player_init(&data->player, data->parse.win_width);
	if (ret == -1)
		return (-1);
	keyflags_init(&data->key_handler);
	return (0);
}
