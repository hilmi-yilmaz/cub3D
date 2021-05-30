/* Standard library header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    map_to_3d(t_data *data)
{
    int		        i;
    int             j;
    int		        height;
    unsigned int    colour;
    double	        dist_to_plane;
    int             *width_walls;

    i = 0;
    j = 0;
    height = 0;
    dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
    width_walls = width_of_wall(data->player.which_wall, data->parse.win_width);

//-------------------------------------- //
    // int p = 0;
    // while (width_walls[p] != -1)
    // {
    //     printf("%d ", width_walls[p]);
    //     p++;
    // }
    // printf("\n");
//-----------------------------------------//

    while (i < data->parse.win_width)
    {
        height = 1.0 / data->player.rays_array[i] * dist_to_plane * WALL_RATIO;
        // if (player->side[i] == 'N')
        //     colour = argb_to_hex(0, 255, 0, 0);
        // else if (player->side[i] == 'S')
        //     colour = argb_to_hex(0, 0, 255, 0);
        // else if (player->side[i] == 'W')
        //     colour = argb_to_hex(0, 127, 0, 0);
        // else
        //     colour = argb_to_hex(0, 0, 127, 0);
        colour = argb_to_hex(0, data->player.which_wall[i] * 20, data->player.which_wall[i] * 10, data->player.which_wall[i] * 15);
        draw_columns(&data->images.main, i, height, data->parse.win_height, colour);
        i++;
    }
	free(width_walls);
}

void    v1_map_to_3d(t_data *data)
{
    int		        i;
    int             j;
    int             count;
    int		        height;
    unsigned int    colour;
    double	        dist_to_plane;
    int             *width_walls;
    unsigned int    *column_rgb;

    i = 0;
    j = 0;
    count = 0;
    height = 0;
    dist_to_plane = data->parse.win_width / 2 * tan(deg2rad(FOV) / 2);
    width_walls = width_of_wall(data->player.which_wall, data->parse.win_width);

//-------------------------------------- //
    // int p = 0;
    // while (width_walls[p] != -1)
    // {
    //     printf("%d ", width_walls[p]);
    //     p++;
    // }
    // printf("\n");
//-----------------------------------------//

    while (width_walls[i] != -1)
    {
        data->images.scaled_xpm.width = width_walls[i];
        data->images.scaled_xpm.height = data->images.north_xpm.height;
        data->images.scaled_xpm.img_ptr = mlx_new_image(data->images.mlx.mlx_ptr, data->images.scaled_xpm.width, data->images.scaled_xpm.height);
        data->images.scaled_xpm.img_addr = mlx_get_data_addr(data->images.scaled_xpm.img_ptr, &data->images.scaled_xpm.bits_per_pixel, &data->images.scaled_xpm.line_size, &data->images.scaled_xpm.endian);
        //printf("scaled_xpm_address = %p\n", data->images.scaled_xpm.img_addr);
        scale_bmp_all_rows(&data->images.north_xpm, &data->images.scaled_xpm); // Scale in x direction
        //mlx_put_image_to_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr, data->images.scaled_xpm.img_ptr, 0, 0);
        
        while (j < width_walls[i])
        {
            height = 1.0 / data->player.rays_array[count] * dist_to_plane * WALL_RATIO;
            //printf("count = %d\n", count);
            //printf("height = %d\n", height);
            column_rgb = malloc(sizeof(*column_rgb) * height);
            scale_column(&data->images.scaled_xpm, j, column_rgb, height);
            //printf("%d\n", j);
            //print_columns(column_rgb, height);
            //get_column_xpm(&data->images.scaled_xpm, column_rgb, j);
            // if (player->side[i] == 'N')
            //     colour = argb_to_hex(0, 255, 0, 0);
            // else if (player->side[i] == 'S')
            //     colour = argb_to_hex(0, 0, 255, 0);
            // else if (player->side[i] == 'W')
            //     colour = argb_to_hex(0, 127, 0, 0);
            // else
            //     colour = argb_to_hex(0, 0, 127, 0);
            colour = argb_to_hex(0, data->player.which_wall[i] * 20, data->player.which_wall[i] * 10, data->player.which_wall[i] * 15);
            // draw_columns(&data->images.main, i, height, data->parse.win_height, colour);
            draw_texture(&data->images.main, count, height, data->parse.win_height, column_rgb);
            free(column_rgb);
            j++;
            count++;
            //return ;
        }
        mlx_destroy_image(data->images.mlx.mlx_ptr, data->images.scaled_xpm.img_ptr);
        //break ;
        //printf("\n");
        j = 0;
        i++;
    }
	free(width_walls);
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

int *width_of_wall(int *which_wall, int width)
{
    int i;
    int i_temp;
    int j;
    int visible_walls;
    int *width_walls;

    i = 0;
    j = 0;
    i_temp = 0;
    visible_walls = amount_visible_walls(which_wall, width);
    width_walls = malloc(sizeof(*width_walls) * (visible_walls + 1));
    while (i < width - 1)
    {
        if (which_wall[i] != which_wall[i + 1] || i + 1 == width - 1)
        {
            width_walls[j] = i_temp + 1;
            i_temp = 0;
            j++;
            i++;
            continue ;
        }
        i++;
        i_temp++;
    }
    width_walls[j - 1] += 1;
    width_walls[j] = -1;

    int p = 0;
    int res = 0;
    while (width_walls[p] != -1)
    {
        res += width_walls[p];
        p++;
    }
    //printf("res = %d\n", res);
    return (width_walls);
}

int amount_visible_walls(int *which_wall, int width)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (i < width - 1)
    {
        if (which_wall[i] != which_wall[i + 1])
            count++;
        i++;
    }
    return (count);
}
