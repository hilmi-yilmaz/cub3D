/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_xpm.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:01 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 15:02:52 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "load_xpm.h"

int	static load_xpm_image(void *mlx_ptr, t_img *xpm_img, char *path)
{
	xpm_img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &xpm_img->width, \
											&xpm_img->height);
	if (xpm_img->img_ptr == NULL)
		return (-1);
	xpm_img->img_ptr_flag = 1;
	xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, \
										&xpm_img->bits_per_pixel, \
										&xpm_img->line_size, &xpm_img->endian);
	if (xpm_img->img_addr == NULL)
		return (-1);
	xpm_img->img_addr_flag = 1;
	return (0);
}

int	load_all_xpm_images(t_data *data)
{
	if (load_xpm_image(data->mlx.mlx_ptr, &data->north_xpm, \
						data->parse.north_text)
		|| load_xpm_image(data->mlx.mlx_ptr, &data->south_xpm, \
						data->parse.south_text)
		|| load_xpm_image(data->mlx.mlx_ptr, &data->west_xpm, \
						data->parse.west_text)
		|| load_xpm_image(data->mlx.mlx_ptr, &data->east_xpm, \
						data->parse.east_text))
	{
		printf("Error\nProblem while loading texture.\n");
		return (-1);
	}
	return (0);
}


