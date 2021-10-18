/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_3d_textured.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:14:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 15:23:18 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map_to_3d_textured.h"

static void	select_xpm_nswe(t_data *data, t_img **selected_xpm, int i)
{
	if (data->player.side[i] == 'N')
		*selected_xpm = &data->north_xpm;
	else if (data->player.side[i] == 'S')
		*selected_xpm = &data->south_xpm;
	else if (data->player.side[i] == 'W')
		*selected_xpm = &data->west_xpm;
	else if (data->player.side[i] == 'E')
		*selected_xpm = &data->east_xpm;
}

static void	column_from_texture_to_main_img(t_data *data, t_img *xpm_img, \
											t_map3d *map3d)
{
	int				i;
	int				start;
	double			text_begin_y;
	double			ratio_heights;
	unsigned int	colour;

	i = 0;
	start = (double)(data->parse.win_height - map3d->height) / 2;
	text_begin_y = 0.0;
	if (start < 0)
	{
		text_begin_y = (double)abs(start);
		start = 0;
	}
	ratio_heights = (double)xpm_img->height / map3d->height;
	while (i < map3d->height)
	{
		if (start + i >= data->parse.win_height)
			break ;
		colour = my_pixel_get(xpm_img, map3d->textwidth, \
							(double)(text_begin_y + i) * ratio_heights);
		my_pixel_put(&data->main, map3d->column, start + i, colour);
		i++;
	}
}

static double	get_textwidth(t_data *data, t_img **selected_xpm, int i)
{
	if (data->player.side[i] == 'E')
	{
		select_xpm_nswe(data, selected_xpm, i);
		return ((data->player.ver_ray[i].y - \
				floor(data->player.ver_ray[i].y)) * (*selected_xpm)->width);
	}
	else if (data->player.side[i] == 'W')
	{
		select_xpm_nswe(data, selected_xpm, i);
		return ((1.0 - (data->player.ver_ray[i].y - \
				floor(data->player.ver_ray[i].y))) * (*selected_xpm)->width);
	}
	else if (data->player.side[i] == 'N')
	{
		select_xpm_nswe(data, selected_xpm, i);
		return ((data->player.hor_ray[i].x - \
				floor(data->player.hor_ray[i].x)) * (*selected_xpm)->width);
	}
	else
	{
		select_xpm_nswe(data, selected_xpm, i);
		return ((1.0 - (data->player.hor_ray[i].x - \
				floor(data->player.hor_ray[i].x))) * (*selected_xpm)->width);
	}
}

void	map_to_3d_textured(t_data *data)
{
	t_map3d	map3d;
	t_img	*selected_xpm;

	map3d.column = 0;
	map3d.dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
	while (map3d.column < data->parse.win_width)
	{
		map3d.textwidth = get_textwidth(data, &selected_xpm, map3d.column);
		map3d.height = 1.0 / data->player.rays_array[map3d.column] * \
				map3d.dist_to_plane * WALL_RATIO;
		column_from_texture_to_main_img(data, selected_xpm, &map3d);
		map3d.column++;
	}
}
