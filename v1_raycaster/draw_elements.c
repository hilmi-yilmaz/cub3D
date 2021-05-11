/* User defined header files */
#include "../cub3d.h"

void    draw_columns(t_img *img, int column, int wall_height, int win_height)
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
        my_pixel_put(img, column, start, argb_to_hex(0, 255, 0, 0));
        start++;
    }
}

void    clear_screen(t_img *img, int win_width, int win_height)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < win_height)
    {
        while(j < win_width)
        {
            my_pixel_put(img, j, i, argb_to_hex(0, 0, 0, 0));
            j++;
        }
        j = 0;
        i++;
    }
}