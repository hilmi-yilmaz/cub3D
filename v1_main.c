/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   v1_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:41:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/16 17:51:06 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>
#include <stdlib.h>

int     main(void)
{
    t_img   img;

    img.win_width = 1000;
    img.win_height = 800;

    // Establish the connection between the X Server and X client
    img.mlx_ptr = mlx_init();
    if (img.mlx_ptr == NULL)
        return (1);
    
    // Create the window
    img.win_ptr = mlx_new_window(img.mlx_ptr, img.win_width, img.win_height, "Test");
    if (img.win_ptr == NULL)
        return (1);

    // Create an image
    img.img_ptr = mlx_new_image(img.mlx_ptr, img.win_width, img.win_height);

    // Get the address of the image
    img.img_addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_size, &img.endian);

    // Make a square which we can move
    put_square(&img, 20, 20);

    // Put the image on the window
    mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);

    // React on events
    mlx_hook(img.win_ptr, DestroyNotify, StructureNotifyMask, close_window, &img);
    mlx_hook(img.win_ptr, KeyPress, KeyPressMask, key_input, &img);

    // mlx loop which is needed for listening to events
    mlx_loop(img.mlx_ptr);

    return (0);
}

void    put_square(t_img *img, int square_width, int square_height, int x, int y)
{
    int i;
    int j;
    int step;
    int start_x;
    int start_y;

    i = 0;
    j = 0;
    step = 10;
    start_x = img->win_width / 2 - square_width / 2 + step;
    start_y = img->win_height / 2 - square_height / 2 + step;
    while (i < square_height)
    {
        while (j < square_width)
        {
            my_pixel_put(img, start_x + i, start_y + j, argb_to_hex(100, 255, 255, 255));
            j++;
        }
        j = 0;
        i++;
    }
}

void reset_image(t_img *img)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < img->win_width)
    {
        while (j < img->win_height)
        {
            my_pixel_put(img, i, j, argb_to_hex(0, 0, 0, 0));
            j++;
        }
        j = 0;
        i++;
    }
}

int key_input(int keycode, t_img *img)
{
    if (keycode == LEFT_KEY)
    {
        reset_image(img);
        put_square(img, 20, 20);
    }
    return (0);
}

void    my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour)
{
    unsigned int    offset;
    char            *dst;

    offset = pos_y * img->line_size + pos_x * (img->bits_per_pixel / 8);
    dst = img->img_addr + offset;
    *(unsigned int *)dst = colour;
}

unsigned int argb_to_hex(int a, int r, int g, int b)
{
    return (a<<24 | r<<16 | g<<8 | b);
}

int close_window(t_img *img)
{
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    exit(0);
    return (1);
}