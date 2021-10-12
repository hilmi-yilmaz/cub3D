/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:37:44 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "init_data.h"

/*
** Initialize all images.
*/
static void	images_init(t_data *data)
{
	ft_bzero(&data->mlx, sizeof(data->mlx));
	ft_bzero(&data->main, sizeof(data->main));
	ft_bzero(&data->north_xpm, sizeof(data->north_xpm));
	ft_bzero(&data->south_xpm, sizeof(data->south_xpm));
	ft_bzero(&data->west_xpm, sizeof(data->west_xpm));
	ft_bzero(&data->east_xpm, sizeof(data->east_xpm));
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

static	int	allocate(t_player *player, int width)
{
	player->rays_array = error_malloc(sizeof(*player->rays_array) * width);
	if (player->rays_array == NULL)
		return (-1);
	player->side = error_malloc(sizeof(*player->side) * width);
	if (player->side == NULL)
		return (-1);
	player->hor_ray = error_malloc(sizeof(*player->hor_ray) * width);
	if (player->hor_ray == NULL)
		return (-1);
	player->ver_ray = error_malloc(sizeof(*player->ver_ray) * width);
	if (player->ver_ray == NULL)
		return (-1);
	return (0);
}

/*
** Initialize the player struct.
*/
static int	player_init(t_player *player, int width)
{
	int	i;
	int	ret;

	i = 0;
	player->x = -1;
	player->y = -1;
	player->angle = -1;
	player->speed = 0.05;
	player->rot_speed = 0.008 * PI;
	player->rays_array = NULL;
	player->side = NULL;
	player->hor_ray = NULL;
	player->ver_ray = NULL;
	ret = allocate(player, width);
	if (ret == -1)
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
** Initialize the images and player structs.
*/
int	raycaster_init(t_data *data)
{
	int	ret;

	images_init(data);
	ret = player_init(&data->player, data->parse.win_width);
	if (ret == -1)
		return (-1);
	ft_bzero(&data->key_handler, sizeof(data->key_handler));
	return (0);
}
