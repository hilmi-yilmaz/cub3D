/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

static void	select_xpm_nswe(t_data *data, t_img **selected_xpm, int i)
{
	if (data->player.side[i] == 'N')
		*selected_xpm = &data->images.north_xpm;
	else if (data->player.side[i] == 'S')
		*selected_xpm = &data->images.south_xpm;
	else if (data->player.side[i] == 'W')
		*selected_xpm = &data->images.west_xpm;
	else if (data->player.side[i] == 'E')
		*selected_xpm = &data->images.east_xpm;
}

static void	column_from_texture_to_main_img(t_img *xpm_img, t_img *main, int p, int column, int height, int win_height)
{
	int	i;
	int	start;
	double	text_begin_y;
	double	ratio_heights;
	unsigned int	colour;

	i = 0;
	start = (double)(win_height - height) / 2;
	text_begin_y = 0.0;
	if (start < 0)
	{
		text_begin_y = (double)abs(start);
		start = 0;
	}
	ratio_heights = (double)xpm_img->height / height;
	while (i < height)
	{
		if (start + i >= win_height)
			break ;
		colour = my_pixel_get(xpm_img, column, (double)(text_begin_y + i) * ratio_heights);
		my_pixel_put(main, p, start + i, colour);
		i++;
	}
}

static double get_textwidth(t_data *data, t_img **selected_xpm, int column)
{
	double	textwidth;

	if (data->player.side[column] == 'E')
	{
		select_xpm_nswe(data, selected_xpm, column);
		textwidth = data->player.ver_ray[column].y - floor(data->player.ver_ray[column].y);
	}
	else if (data->player.side[column] == 'W')
	{
		select_xpm_nswe(data, selected_xpm, column);
		textwidth = 1.0 - (data->player.ver_ray[column].y - floor(data->player.ver_ray[column].y));
	}
	else if (data->player.side[column] == 'N')
	{
		select_xpm_nswe(data, selected_xpm, column);
		textwidth = data->player.hor_ray[column].x - floor(data->player.hor_ray[column].x);
	}
	else if (data->player.side[column] == 'S')
	{
		select_xpm_nswe(data, selected_xpm, column);
		textwidth = 1.0 - (data->player.hor_ray[column].x - floor(data->player.hor_ray[column].x));
	}
	textwidth *= (*selected_xpm)->width;
	return (textwidth);
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
		height = 1.0 / data->player.rays_array[column] * dist_to_plane * WALL_RATIO;
		column_from_texture_to_main_img(selected_xpm, &data->images.main, column, textwidth, height, data->parse.win_height);
		column++;
	}
}