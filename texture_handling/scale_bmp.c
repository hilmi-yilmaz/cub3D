/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img, double scale_x, double scale_y, int xpm_width, int xpm_height)
{
    /* Get the address of the xpm img */
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);
    // printf("%p\n", xpm_img->img_addr);
    // printf("bits_per_pixel = %d\n", xpm_img->bits_per_pixel);
    // printf("line_size = %d\n", xpm_img->line_size);
    // printf("endian = %d\n", xpm_img->endian);

    /* Create a new image for scaled xpm and get the address of the scaled xpm img */
    scaled_xpm_img->img_addr = mlx_get_data_addr(scaled_xpm_img->img_ptr, &scaled_xpm_img->bits_per_pixel, &scaled_xpm_img->line_size, &scaled_xpm_img->endian);
    // printf("%p\n", scaled_xpm_img->img_addr);
    // printf("bits_per_pixel = %d\n", scaled_xpm_img->bits_per_pixel);
    // printf("line_size = %d\n", scaled_xpm_img->line_size);
    // printf("endian = %d\n", scaled_xpm_img->endian);


    // int i = 0;
    // int j = 0;
    // while (i < 32)
    // {
    //     while (j < 32)
    //     {
    //         my_pixel_put_xpm(&xpm_img, j, i, argb_to_hex(0, 255, 0, 0));
    //         j++;
    //     }
    //     j = 0;
    //     i++;
    // }
      
    //     unsigned int colour = my_pixel_get_xpm(&xpm_img, 0, 0);
    // printf("colour = %X\n", colour);

        /* Initialize parameters */
    double scale_ix = 1 / scale_x;
    double scale_iy = 1 / scale_y;

    int     dest_width = xpm_width / scale_x;
    int     dest_height = xpm_height / scale_y;

    printf("src_width = %d\n", xpm_width);
    printf("src_height = %d\n", xpm_height);

    printf("dest_width = %d\n", dest_width);
    printf("dest_height = %d\n", dest_height);

    /* Coordinates of destination pixels */
    int x = 0;
    int y = 0;

    while (y < dest_height)
    {
        
        
        double  sy1 = scale_y * y;
        double  sy2 = sy1 + scale_y;
        int     jstart = trunc(sy1);
        int     jend = trunc(sy2);
        double  dev_Y1 = 1 - (sy1 - jstart);
        double  dev_Y2 = (double)(jend + 1) - sy2;
        while (x < dest_width)
        {
            printf("------------------------------------------- x = %d, y = %d ------------------------------------------------\n", x, y);
            double  sx1 = scale_x * x;
            double  sx2 = sx1 + scale_x;
            int     istart = trunc(sx1);
            int     iend = trunc(sx2);
            double  dev_X1 = 1 - (sx1 - istart);
            double  dev_X2 = (double)(iend + 1) - sx2;
            double  dy = dev_Y1;

            printf("sy1 = %f, sy2 = %f\n", sy1, sy2);
            printf("sx1 = %f, sx2 = %f\n", sx1, sx2);
            printf("dev_Y1 = %f, dev_Y2 = %f\n", dev_Y1, dev_Y2);
            printf("dev_X1 = %f, dev_X2 = %f\n", dev_X1, dev_X2);

            /* Set the colour to zero */
            double  destR = 0;
            double  destG = 0;
            double  destB = 0;

            /* Loop inside of source image */
            int i = istart;
            int j = jstart;
            
            //printf("istart = %d, jstart = %d\n", istart, jstart);
            //printf("iend   = %d, jend   = %d\n", iend, jend);
            while (j <= jend)
            {
                double  dx = dev_X1;
                if (j == jend)
                    dy -= dev_Y2;

                while (i <= iend)
                {
                    if (i == iend)
                        dx -= dev_X2;
                    // else if (i < iend && i != istart)
                    //     dx = 1.0;
                    
                    printf("i = %d, j = %d\n", i, j);
                    
                    /* Read the colour at pixel i,j */
                    int sR = get_argb(my_pixel_get(xpm_img, i, j), 'r');
                    int sG = get_argb(my_pixel_get(xpm_img, i, j), 'g');
                    int sB = get_argb(my_pixel_get(xpm_img, i, j), 'b');

                    printf("src_colour = [%d][%d][%d]\n", (int)sR, (int)sG, (int)sB);

                    /* Area factor */
                    double AP = scale_ix * scale_iy * dx * dy;
                    printf("scale_ix = %f, scale_iy = %f, dx = %f, dy = %f\n", scale_ix, scale_iy, dx, dy);
                    printf("AP = %f\n", AP);

                    

                    /* Add colours */
                    destR += sR * AP;
                    destG += sG * AP;
                    destB += sB * AP;

                    printf("ap_src_colour = [%d][%d][%d]\n", (int)destR, (int)destG, (int)destB);

                    i++;
                }
                dy = 1.0;
                dx = 1.0;
                j++;
            }
            destR = floor(destR);
            destG = floor(destG);
            destB = floor(destB);

            printf("dest_colour = [%d][%d][%d]\n", (int)destR, (int)destG, (int)destB);

            /* Add colour to scaled img */
            //printf("x = %d, y = %d\n", x, y);
            my_pixel_put(scaled_xpm_img, x, y, argb_to_hex(0, destR, destG, destB));

            x++;
        }
        x = 0;
        y++;
    }



}