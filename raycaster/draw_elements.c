/* User defined header files */
#include "../cub3d.h"

#include <stdio.h>

void    draw_columns(t_img *img, int column, int wall_height, int win_height, unsigned int colour)
{
    int start;
    int end;

    start = (win_height - wall_height) / 2;
    if (start < 0)
        start = 0;
    end = (win_height + wall_height) / 2;
    if (end >= win_height)
        end = win_height - 1;
    while (start < end)
    {
        my_pixel_put(img, column, start, colour);
        start++;
    }
}

void    draw_floor_ceiling(t_img *main, t_parse *parse)
{
    int             i;
    int             j;
    unsigned int    ceiling_colour;
    unsigned int    floor_colour;

    i = 0;
    j = 0;
    ceiling_colour = argb_to_hex(0, parse->ceiling_colour[0], parse->ceiling_colour[1], parse->ceiling_colour[2]);
    floor_colour = argb_to_hex(0, parse->floor_colour[0], parse->floor_colour[1], parse->floor_colour[2]);
    while (i < parse->win_height)
    {
        while (j < parse->win_width)
        {
            if (i < parse->win_height / 2)
                my_pixel_put(main, j, i, ceiling_colour);
            else
                my_pixel_put(main, j, i, floor_colour);
            j++;
        }
        j = 0;
        i++;
    }
}

void    clear_screen(t_img *main, int win_width, int win_height)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < win_height)
    {
        while(j < win_width)
        {
            my_pixel_put(main, j, i, argb_to_hex(0, 0, 0, 0));
            j++;
        }
        j = 0;
        i++;
    }
}