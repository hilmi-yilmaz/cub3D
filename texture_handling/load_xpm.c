/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    load_all_xpm_images(t_images *images, t_parse *parse)
{
    load_xpm_image(&images->north_xpm, parse->north_text);
    load_xpm_image(&images->south_xpm, parse->south_text);
    load_xpm_image(&images->west_xpm, parse->west_text);
    load_xpm_image(&images->east_xpm, parse->east_text);
}

void    load_xpm_image(t_img *xpm_img, char *path)
{
    xpm_img->img_ptr = mlx_xpm_file_to_image(xpm_img->mlx_ptr, path, &xpm_img->width, &xpm_img->height);
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);
}