/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   v1_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:41:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/19 13:29:07 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    put_circle(&img);

    // Set the ceiling and floor
    img.ceiling_colour = argb_to_hex(0, 0, 255, 0);
    img.floor_colour = argb_to_hex(0, 0, 0, 255);
    //reset_image(&img);

    // Make a square which we can move, also initialize the location of it
    img.square.width = 20;
    img.square.height = 20;
    img.square.pos_x = img.win_width / 2 - img.square.width / 2;
    img.square.pos_y = img.win_height / 2 - img.square.height / 2;
    //put_square(&img);

    // React on closing the screen
    if (IS_LINUX)
        mlx_hook(img.win_ptr, ClientMessage, NoEventMask, close_window, &img);
    else
        mlx_hook(img.win_ptr, DestroyNotify, StructureNotifyMask, close_window, &img);

    // React on user keyboard input
    mlx_hook(img.win_ptr, KeyPress, KeyPressMask, key_input, &img);

    // mlx loop which is needed for listening to events
    mlx_loop(img.mlx_ptr);

    return (0);
}

void    set_ceiling(t_img *img)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < img->win_height / 2)
    {
        while (i < img->win_width)
        {
            my_pixel_put(img, i, j, img->ceiling_colour);
            i++;
        }
        i = 0;
        j++;
    }
    //mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    set_floor(t_img *img)
{
    int i;
    int j;

    i = 0;
    j = img->win_height / 2;
    while (j < img->win_height)
    {
        while (i < img->win_width)
        {
            my_pixel_put(img, i, j, img->floor_colour);
            i++;
        }
        i = 0;
        j++;
    }
    //mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    put_circle(t_img *img)
{
    double x;
    double y;
    int start_x;
    int start_y;
    int r;
    double alpha;

    start_x = img->win_width / 2;
    start_y = img->win_height / 2;
    r = 50;
    alpha = 0;

    while (alpha < 2 * 3.14)
    {
        x = start_x + r * cos(alpha);
        y = start_y + r * sin(alpha);
        my_pixel_put(img, x, y, argb_to_hex(0, 255, 255, 255));
        alpha += 0.01;
    }
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void    put_square(t_img *img)
{
    int i;
    int j;
    int step;

    i = 0;
    j = 0;
    step = 10;
    // printf("entered put_square\n");
    printf("pos_x = %d\n", img->square.pos_x);
    printf("pos_y = %d\n", img->square.pos_y);
    // printf("width = %d\n", img->square.width);
    // printf("height = %d\n", img->square.height);
    while (i < img->square.height)
    {
        while (j < img->square.width)
        {
            my_pixel_put(img, img->square.pos_x + i, img->square.pos_y + j, argb_to_hex(0, 255, 255, 255));
            j++;
        }
        j = 0;
        i++;
    }
    // Put the image on the window
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

void reset_image(t_img *img)
{
    // int i;
    // int j;

    // i = 0;
    // j = 0;
    // while (i < img->win_width)
    // {
    //     while (j < img->win_height)
    //     {
    //         my_pixel_put(img, i, j, argb_to_hex(0, 0, 0, 0));
    //         j++;
    //     }
    //     j = 0;
    //     i++;
    // }

    set_ceiling(img);
    set_floor(img);

    // After the image is resetted, we put the image to the window again
    //mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}

int key_input(int keycode, t_img *img)
{
    if (keycode == LEFT_KEY)
    {
        if (img->square.pos_x <= 0)
            return (1);
        reset_image(img);
        img->square.pos_x -= 10;
        put_square(img);
    }
    if (keycode == RIGHT_KEY)
    {
        if (img->square.pos_x >= img->win_width - img->square.width)
            return (1);
        reset_image(img);
        img->square.pos_x += 10;
        put_square(img);
    }
    if (keycode == UP_KEY)
    {
        if (img->square.pos_y <= 0)
            return (1);
        reset_image(img);
        img->square.pos_y -= 10;
        put_square(img);
    }
    if (keycode == DOWN_KEY)
    {
        if (img->square.pos_y >= img->win_height - img->square.height)
            return (1);
        reset_image(img);
        img->square.pos_y += 10;
        put_square(img);
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