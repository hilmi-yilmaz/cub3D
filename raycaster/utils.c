/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* User defined header files */
#include "../cub3d.h"

void    *error_malloc(unsigned int bytes)
{
    void    *ptr;
    
    ptr = malloc(bytes);
    if (ptr == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return (NULL);
    }
    return (ptr);
}

// void    draw_line_on_wall_edges(t_img *main, int *width_walls, int win_height)
// {
//     int i;
//     int res;

//     i = 0;
//     res = 0;
//     while (width_walls[i] != -1)
//     {
//         res += width_walls[i];
//         draw_columns(main, res, win_height, win_height, argb_to_hex(0, 255, 255, 255));
//         i++;
//     }
// }

// void    ft_swap_doubles(double *x, double *y)
// {
//     double  tmp;

//     tmp = *x;
//     *x = *y;
//     *y = tmp;
// }

/*
 Returns the width of the walls visible on the screen. the width count up to the total width of the screen.
 */
// int *width_of_wall(int *which_wall, int width)
// {
//     int i;
//     int i_temp;
//     int j;
//     int visible_walls;
//     int *width_walls;

//     i = 0;
//     j = 0;
//     i_temp = 0;
//     visible_walls = amount_visible_walls(which_wall, width);
//     width_walls = malloc(sizeof(*width_walls) * (visible_walls + 1));
//     if (width_walls == NULL)
//         return (NULL);
//     while (i < width - 1)
//     {
//         if (which_wall[i] != which_wall[i + 1] || i + 1 == width - 1)
//         {
//             width_walls[j] = i_temp + 1;
//             i_temp = 0;
//             j++;
//             i++;
//             continue ;
//         }
//         i++;
//         i_temp++;
//     }
//     width_walls[j - 1] += 1;
//     width_walls[j] = -1;
//     return (width_walls);
// }

// int amount_visible_walls(int *which_wall, int width)
// {
//     int i;
//     int count;

//     i = 0;
//     count = 1;
//     while (i < width - 1)
//     {
//         if (which_wall[i] != which_wall[i + 1])
//             count++;
//         i++;
//     }
//     return (count);
// }

void    set_start_location(t_player *player, char **map)
{
    int	x;
	int	y;
	
	find_player_location(&x, &y, map);
	if (map[y][x] == 'N')
        player->angle = 0.5 * PI;
    else if (map[y][x] == 'W')
        player->angle = 1 * PI;
    else if (map[y][x] == 'S')
        player->angle = 1.5 * PI;
    else
        player->angle = 0 * PI;
	player->x = (x + 0.5) * UNIT;
    player->y = (y + 0.5) * UNIT;
}

int     ft_int_array_len(int *arr)
{
    int i;

    i = 0;
    while (arr[i] != -1)
        i++;
    return (i);
}

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
        i++;
    return (i);
}

int close_window(t_data *data)
{
    /* Destroy the image and window */
    mlx_destroy_image(data->images.mlx.mlx_ptr, data->images.main.img_ptr);
    mlx_destroy_window(data->images.mlx.mlx_ptr, data->images.mlx.win_ptr);
    if (__linux__)
        mlx_destroy_display(data->images.mlx.mlx_ptr);

    /* Free the pointers */
    free(data->images.mlx.mlx_ptr);
    
    /* Exit the programn */
    exit(0);
    return (1);
}

void    my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
    unsigned int    offset;
    char            *dst;

    offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
    dst = img->img_addr + offset;
    *(unsigned int *)dst = colour;
}

unsigned int    my_pixel_get(t_img *img, int pos_x, int pos_y)
{
    unsigned int    offset;
    char            *dst;

    offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
    dst = img->img_addr + offset;
    return (*(unsigned int *)dst);
}

unsigned int argb_to_hex(int a, int r, int g, int b)
{
    return (a<<24 | r<<16 | g<<8 | b);
}

int get_argb(unsigned int argb, char c)
{
    int shift;
    
    if (c == 'a')
        shift = 24;
    else if (c == 'r')
        shift = 16;
    else if (c == 'g')
        shift = 8;
    else if (c == 'b')
        shift = 0;
    else
        return (-1);
    return ((argb & (0xFF << shift)) >> shift);
}
