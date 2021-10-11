/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int     load_all_xpm_images(t_data *data)
{
    int ret;

    if (load_xpm_image(data->mlx.mlx_ptr, &data->north_xpm, data->parse.north_text)
        || load_xpm_image(data->mlx.mlx_ptr, &data->south_xpm, data->parse.south_text)
        || load_xpm_image(data->mlx.mlx_ptr, &data->west_xpm, data->parse.west_text)
        || load_xpm_image(data->mlx.mlx_ptr, &data->east_xpm, data->parse.east_text))
        return (-1);
    return (0);
}

int     load_xpm_image(void *mlx_ptr, t_img *xpm_img, char *path)
{
    xpm_img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &xpm_img->width, &xpm_img->height);
    if (xpm_img->img_ptr == NULL)
        return (-1);
    xpm_img->img_ptr_flag = 1;
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);
	if (xpm_img->img_addr == NULL)
		return (-1);
    xpm_img->img_addr_flag = 1;
    return (0);
}