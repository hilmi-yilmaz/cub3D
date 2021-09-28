/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

static void	select_xpm_nswe(t_data *data, t_img **selected_xpm, int count)
{
	if (data->player.side[count] == 'N')
		*selected_xpm = &data->images.north_xpm;
	else if (data->player.side[count] == 'S')
		*selected_xpm = &data->images.south_xpm;
	else if (data->player.side[count] == 'W')
		*selected_xpm = &data->images.west_xpm;
	else if (data->player.side[count] == 'E')
		*selected_xpm = &data->images.east_xpm;
}

int		map_to_3d_textured(t_data *data)
{
	int	i; // loops over all walls [98, 255, 99]
	int	j; // loops over each wall [0..97, 0..255, 0..99]
	int	height; // height of the column
	int	count;  // which columns we are at (0..width)
	int	dist_to_plane; // const distance to plane
	int	*width_walls;  // contains width of the walls [98, 255, 99]
	int wall_x;
	t_img *selected_xpm;
	t_tmpscale params;

	i = 0;
	j = 0;
	count = 0; // stores which column (0 to width of screen)
	dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
	width_walls = width_of_wall(data->player.which_wall, data->parse.win_width);
    if (width_walls == NULL)
        return (-1);

	while (width_walls[i] != -1)
	{
		select_xpm_nswe(data, &selected_xpm, count);
		if (i == 0)
		{
			wall_x = (int)((double)width_walls[i] / (1.0 - data->player.wall_x_start)); // what the length of the whole wall is (visible + invisible)
			get_scale_params_x(&params, selected_xpm, wall_x);
		}
		else if (i == ft_int_array_len(width_walls) - 1)
		{
			wall_x = (int)((double)width_walls[i] / (1.0 - data->player.wall_x_end)); // what the length of the whole wall is (visible + invisible)
			get_scale_params_x(&params, selected_xpm, wall_x);
		}
		else
			get_scale_params_x(&params, selected_xpm, width_walls[i]);
		while (j < width_walls[i])
		{
			height = 1.0 / data->player.rays_array[count] * dist_to_plane * WALL_RATIO;
			get_scale_params_y(&params, selected_xpm, height);
			pixel_from_xpm_to_window(&data->images.main, selected_xpm, &params, count, j, height, data->parse.win_height, &data->player, width_walls, i, wall_x, ft_int_array_len(width_walls));
			j++;
			count++;
		}
		j = 0;
		i++;
	}
	draw_line_on_wall_edges(&data->images.main, width_walls, data->parse.win_height);
	free(width_walls);
	return (0);
}

void    get_column_xpm(t_img *xpm_img, unsigned int *column_rgb, int column)
{
    int i;

    i = 0;
    while (i < xpm_img->height)
    {
        column_rgb[i] = my_pixel_get(xpm_img, column, i);
        i++;
    }
}