/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 16:26:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 16:26:58 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_utils.h"

int	close_window(t_data *data)
{
	free_images(data);
	free_parse(&data->parse);
	free_player(&data->player);
	exit(0);
	return (1);
}

void	my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
	unsigned int	offset;
	char			*dst;

	offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
	dst = img->img_addr + offset;
	*(unsigned int *)dst = colour;
}

unsigned int	my_pixel_get(t_img *img, int pos_x, int pos_y)
{
	unsigned int	offset;
	char			*dst;

	offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
	dst = img->img_addr + offset;
	return (*(unsigned int *)dst);
}

unsigned int	argb_to_hex(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}