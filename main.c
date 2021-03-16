/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 12:20:02 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/16 10:26:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(void)
{
    //Declare struct
    t_img   img;

    // Size of the image
    int     img_width;
    int     img_height;

    img.win_width = 1000;
    img.win_height = 800;

    img_width = 20;
    img_height = 20;

    // Establish the connection between X Server and X client
    img.mlx_ptr = mlx_init();
    if (img.mlx_ptr == NULL)
        return (1);

    // Create the window
    img.win_ptr = mlx_new_window(img.mlx_ptr, img.win_width, img.win_height, "Test");
    if (img.win_ptr == NULL)
        return (1);

    // Create an image
    img.img_ptr = mlx_new_image(img.mlx_ptr, img_width, img_height);

    // Get the address of the image
    img.img_addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_size, &img.endian);

    // Draw pixels on the image
    // draw_horizontal_line(&img, win_width, win_height);
    // draw_vertical_line(&img, win_width, win_height);
    //draw_x(&img, win_width / 2, win_height / 2, win_width, win_height);
    img.img_pos_x = img.win_width / 2;
    img.img_pos_y = img.win_height / 2;
    draw_box(&img, img.img_pos_x, img.img_pos_y, img_width, img_height);

    // Put the image on the window
    //mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0); //x, y coordinates, where to put the image

    // Whenever a specific key is pressed, close the window
    mlx_hook(img.win_ptr, 2, 1L<<0, move, &img);
    //mlx_hook(img.win_ptr, DestroyNotify, StructureNotifyMask, close, &img);

    mlx_loop(img.mlx_ptr);
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

void    draw_horizontal_line(t_img *img, int win_width, int win_height)
{
    int i;

    i = 0;
    while (i < win_width)
    {
        my_pixel_put(img, i, win_height / 2, argb_to_hex(0, 255, 0, 255));
        i++;
    }
}

void    draw_vertical_line(t_img *img, int win_width, int win_height)
{
    int i;

    i = 0;
    while (i < win_height)
    {
        my_pixel_put(img, win_width / 2, i, argb_to_hex(0, 0, 255, 255));
        i++;
    }
}

void    draw_x(t_img *img, int x, int y, int win_width, int win_height)
{
    int i;
    int factor;

    i = 0;
    factor = 10;
    // Draw horizontal
    while (i < win_width / factor)
    {
        my_pixel_put(img, (x - win_width / factor / 2) + i, win_height / 2, argb_to_hex(0, 255, 0, 0));
        i++;
    }
    i = 0;
    while (i < win_height / factor)
    {
        my_pixel_put(img, win_width / 2, (y - win_height / factor / 2) + i, argb_to_hex(0, 255, 0, 0));
        i++;
    }
}

void    draw_box(t_img *img, int x, int y, int box_width, int box_height)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < box_width)
    {
        while (j < box_height)
        {
            my_pixel_put(img, j, i, argb_to_hex(0, 255, 255, 255));
            j++;
        }
        j = 0;
        i++;
    }
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, x, y);
}

int argb_to_hex(int t, int r, int g, int b)
{
    return (t<<24 | r<<16 | g<<8 | b);
}

int key_hook(int keycode, t_img *img)
{
    printf("Hello from key_hook!\n");
    return (0);
}

int close(int keycode, t_img *img)
{
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    return (0);
}

int move(int keycode, t_img *img)
{
    int step;

    step = 5;
    mlx_destroy_image(img->mlx_ptr, img->img_ptr);
    mlx_clear_window(img->mlx_ptr, img->win_ptr);
    img->img_ptr = mlx_new_image(img->mlx_ptr, 20, 20);
    img->img_addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_size, &img->endian);
    if (keycode == RIGHT_KEY)
    {
        draw_box(img, img->img_pos_x += step, img->img_pos_y, 20, 20);
        printf("Move right\n");
    }
    if (keycode == LEFT_KEY)
    {
        draw_box(img, img->img_pos_x -= step, img->img_pos_y, 20, 20);
        printf("Move left\n");
    }
    if (keycode == DOWN_KEY)
    {
        draw_box(img, img->img_pos_x, img->img_pos_y += step, 20, 20);
        printf("Move down\n");
    }
    if (keycode == UP_KEY)
    {
        draw_box(img, img->img_pos_x, img->img_pos_y -= step, 20, 20);
        printf("Move up\n");
    }
    return (0);
}
