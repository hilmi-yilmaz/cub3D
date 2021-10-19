/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:26 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/19 10:23:25 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_free.h"

void	free_all(t_data *data)
{
	free_parse(&data->parse);
	free_images(data);
	free_player(&data->player);
}

void	free_images(t_data *data)
{
	if (data->main.img_ptr_flag == 1)
		mlx_destroy_image(data->mlx.mlx_ptr, data->main.img_ptr);
	if (data->north_xpm.img_ptr_flag == 1)
		mlx_destroy_image(data->mlx.mlx_ptr, data->north_xpm.img_ptr);
	if (data->south_xpm.img_ptr_flag == 1)
		mlx_destroy_image(data->mlx.mlx_ptr, data->south_xpm.img_ptr);
	if (data->east_xpm.img_ptr_flag == 1)
		mlx_destroy_image(data->mlx.mlx_ptr, data->east_xpm.img_ptr);
	if (data->west_xpm.img_ptr_flag == 1)
		mlx_destroy_image(data->mlx.mlx_ptr, data->west_xpm.img_ptr);
	if (data->mlx.win_ptr_flag == 1)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	free(data->mlx.mlx_ptr);
}

void	free_player(t_player *player)
{
	free(player->rays_array);
	free(player->side);
	free(player->hor_ray);
	free(player->ver_ray);
}
