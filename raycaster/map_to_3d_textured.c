/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

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
								int column, int xpm_column, int height)
{
	int				i;
	int				start;
	double			text_begin_y;
	double			ratio_heights;
	unsigned int	colour;

	i = 0;
	start = (double)(data->parse.win_height - height) / 2;
	text_begin_y = 0.0;
	if (start < 0)
	{
		text_begin_y = (double)abs(start);
		start = 0;
	}
	ratio_heights = (double)xpm_img->height / height;
	while (i < height)
	{
		if (start + i >= data->parse.win_height)
			break ;
		colour = my_pixel_get(xpm_img, xpm_column, \
							(double)(text_begin_y + i) * ratio_heights);
		my_pixel_put(&data->main, column, start + i, colour);
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
	int		column;
	int		height;
	int		dist_to_plane;
	double	textwidth;
	t_img	*selected_xpm;

	column = 0;
	dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
	while (column < data->parse.win_width)
	{
		textwidth = get_textwidth(data, &selected_xpm, column);
		height = 1.0 / data->player.rays_array[column] * \
				dist_to_plane * WALL_RATIO;
		column_from_texture_to_main_img(data, selected_xpm, \
										column, textwidth, height);
		column++;
	}
}
