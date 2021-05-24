/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    load_xpm_images(t_img *xpm_img)
{
    xpm_img->img_ptr = mlx_xpm_file_to_image(img->mlx_ptr, parse.north_text, parse.north_xpm.width, parse.north_xpm.height);
    xpm_img->img_ptr = mlx_xpm_file_to_image(img->mlx_ptr, parse.north_text, parse.north_xpm.width, parse.north_xpm.height);
}