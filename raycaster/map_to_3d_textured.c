/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int		map_to_3d_textured(t_data *data)
{
	int	i;
	int	j;
	int	height;
	int	count;
	int	dist_to_plane;
	int	*width_walls;
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

    /* ----------------------------------- print width walls ---------------------------- */
    int p = 0;
    int total = 0;
		printf("--------------------\n");
    while (width_walls[p] != -1)
    {
        printf("%d ", width_walls[p]);
        total += width_walls[p];
        p++;
    }
    printf("\nplayer->wall_x_start = %f\n", data->player.wall_x_start);
    printf("player->wall_x_end = %f\n", data->player.wall_x_end);
    /* ---------------------------------------------------------------------------------- */

	while (width_walls[i] != -1)
	{
		
		if (data->player.side[count] == 'N')
			selected_xpm = &data->images.north_xpm;
		else if (data->player.side[count] == 'S')
			selected_xpm = &data->images.south_xpm;
		else if (data->player.side[count] == 'W')
			selected_xpm = &data->images.west_xpm;
		else if (data->player.side[count] == 'E')
			selected_xpm = &data->images.east_xpm;
		if (i == 0)
		{
			wall_x = (int)((double)width_walls[i] / (1.0 - data->player.wall_x_start)); // what the length of the whole wall is (visible + invisible)
			printf("wall_x (start) = %d\n", wall_x);
			get_scale_params_x(&params, selected_xpm, wall_x);
		}
		else if (i == ft_int_array_len(width_walls) - 1)
		{
			wall_x = (int)((double)width_walls[i] / (1.0 - data->player.wall_x_end)); // what the length of the whole wall is (visible + invisible)
			printf("wall_x (end) = %d\n", wall_x);
			get_scale_params_x(&params, selected_xpm, wall_x);
		}
		else
			get_scale_params_x(&params, selected_xpm, width_walls[i]);
		while (j < width_walls[i])
		{

			printf("player->side = %c\n", data->player.side[count]);
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

// void    v1_map_to_3d(t_data *data)
// {
//     int		        i;
//     int             j;
//     int             count;
//     int		        height;
//     unsigned int    colour;
//     double	        dist_to_plane;
//     int             *width_walls;
//     unsigned int    *column_rgb;

//     i = 0;
//     j = 0;
//     count = 0;
//     height = 0;
//     dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
//     width_walls = width_of_wall(data->player.which_wall, data->parse.win_width);

// //-------------------------------------- //
//     // int p = 0;
//     // while (width_walls[p] != -1)
//     // {
//     //     printf("%d ", width_walls[p]);
//     //     p++;
//     // }
//     // printf("\n");
// //-----------------------------------------//

//     while (width_walls[i] != -1)
//     {
//         data->images.scaled_xpm.width = width_walls[i];
//         data->images.scaled_xpm.height = data->images.north_xpm.height;
//         data->images.scaled_xpm.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, data->images.scaled_xpm.width, data->images.scaled_xpm.height);
//         data->images.scaled_xpm.img_addr = mlx_get_data_addr(data->images.scaled_xpm.img_ptr, &data->images.scaled_xpm.bits_per_pixel, &data->images.scaled_xpm.line_size, &data->images.scaled_xpm.endian);
//         //printf("scaled_xpm_address = %p\n", data->images.scaled_xpm.img_addr);
//         scale_bmp_all_rows(&data->images.north_xpm, &data->images.scaled_xpm); // Scale in x direction
//         //mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.scaled_xpm.img_ptr, 0, 0);
        
//         while (j < width_walls[i])
//         {
//             height = 1.0 / data->player.rays_array[count] * dist_to_plane * WALL_RATIO;
//             //printf("count = %d\n", count);
//             //printf("height = %d\n", height);
//             column_rgb = malloc(sizeof(*column_rgb) * height);
//             scale_column(&data->images.scaled_xpm, j, column_rgb, height);
//             //printf("%d\n", j);
//             //print_columns(column_rgb, height);
//             //get_column_xpm(&data->images.scaled_xpm, column_rgb, j);
//             // if (player->side[i] == 'N')
//             //     colour = argb_to_hex(0, 255, 0, 0);
//             // else if (player->side[i] == 'S')
//             //     colour = argb_to_hex(0, 0, 255, 0);
//             // else if (player->side[i] == 'W')
//             //     colour = argb_to_hex(0, 127, 0, 0);
//             // else
//             //     colour = argb_to_hex(0, 0, 127, 0);
//             colour = argb_to_hex(0, data->player.which_wall[i] * 20, data->player.which_wall[i] * 10, data->player.which_wall[i] * 15);
//             // draw_columns(&data->images.main, i, height, data->parse.win_height, colour);
//             draw_texture(&data->images.main, count, height, data->parse.win_height, column_rgb);
//             free(column_rgb);
//             j++;
//             count++;
//             //return ;
//         }
//         mlx_destroy_image(data->images.mlx.mlx_ptr, data->images.scaled_xpm.img_ptr);
//         //break ;
//         //printf("\n");
//         j = 0;
//         i++;
//     }
// 	free(width_walls);
// }

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