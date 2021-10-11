/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int     load_all_xpm_images(t_images *images, t_parse *parse)
{
    int ret;

    if (load_xpm_image(images->mlx.mlx_ptr, &images->north_xpm, parse->north_text)
        || load_xpm_image(images->mlx.mlx_ptr, &images->south_xpm, parse->south_text)
        || load_xpm_image(images->mlx.mlx_ptr, &images->west_xpm, parse->west_text)
        || load_xpm_image(images->mlx.mlx_ptr, &images->east_xpm, parse->east_text))
        return (-1);
    return (0);
}

int     load_xpm_image(void *mlx_ptr, t_img *xpm_img, char *path)
{
    xpm_img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &xpm_img->width, &xpm_img->height);
    if (xpm_img->img_ptr == NULL)
        return (-1);
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);
	if (xpm_img->img_addr == NULL)
		return (-1);
    return (0);
}