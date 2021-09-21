/* Standard library header files */
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

void    free_images(t_images *images)
{
    free(images->mlx.mlx_ptr);
    free(images->mlx.win_ptr);
    free(images->north_xpm.img_ptr);
    free(images->south_xpm.img_ptr);
    free(images->west_xpm.img_ptr);
    free(images->east_xpm.img_ptr);
}

void    free_player(t_player *player)
{
    free(player->rays_array);
    free(player->side);
    free(player->which_wall);
}