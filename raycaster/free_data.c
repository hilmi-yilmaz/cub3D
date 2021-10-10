/* Standard library header files */
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

void	free_all(t_data *data)
{
	free_images(&data->images);
	free_player(&data->player);
}

void	free_images(t_images *images)
{
	mlx_destroy_image(images->mlx.mlx_ptr, images->main.img_ptr);
	mlx_destroy_image(images->mlx.mlx_ptr, images->north_xpm.img_ptr);
	mlx_destroy_image(images->mlx.mlx_ptr, images->south_xpm.img_ptr);
	mlx_destroy_image(images->mlx.mlx_ptr, images->east_xpm.img_ptr);
	mlx_destroy_image(images->mlx.mlx_ptr, images->west_xpm.img_ptr);
	mlx_destroy_window(images->mlx.mlx_ptr, images->mlx.win_ptr);
	if (__linux__)
		mlx_destroy_display(images->mlx.mlx_ptr);
	free(images->mlx.mlx_ptr);
}

void	free_player(t_player *player)
{
	free(player->rays_array);
	free(player->side);
}
