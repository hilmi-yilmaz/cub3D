/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

#define PRINT 1

void    scale_bmp_v1(t_img *xpm_img, t_img *scaled_xpm_img, int xpm_width, int xpm_height, int scaled_xpm_width, int scaled_xpm_height)
{
    /* Get the address of the xpm img */
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);

    /* Get the address of the scaled xpm img */
    scaled_xpm_img->img_addr = mlx_get_data_addr(scaled_xpm_img->img_ptr, &scaled_xpm_img->bits_per_pixel, &scaled_xpm_img->line_size, &scaled_xpm_img->endian);

	printf("xpm_width = %d, xpm_scaled_width = %d\n", xpm_width, scaled_xpm_width);

    /* Calculate the scaling factors */
    double fx = (double)xpm_width / scaled_xpm_width;
    double fy = (double)xpm_height / scaled_xpm_height;

    /* Correcting for the rounding error */
    double fxstep = 0.9999 * fx;
    double fystep = 0.9999 * fy;

    /* Inverse of fx and fy */
    double fix = 1 / fx;
    double fiy = 1 / fy;

    if (PRINT == 1)
        printf("fx = %f, fy = %f\n", fx, fy);

    /* x and y loop over the destination bitmap, the scaled bitmap */
    int x = 0;
    int y = 0;

    /* i and j loop over the source bitmap, the original image */
    int i = 0;
    int j = 0;

    while (y < scaled_xpm_height)
    {
        double  sy1 = y * fy;
        double  sy2 = sy1 + fystep;
        int     jstart = trunc(sy1);
        int     jend = trunc(sy2);
        double  devY1 = 1.0 - (sy1 - jstart);
        double  devY2 = 1.0 - (sy2 - jend);

        if (PRINT == 1)
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

        while (x < scaled_xpm_width)
        {
            double  sx1 = x * fx;
            double  sx2 = sx1 + fxstep;
            int     istart = trunc(sx1);
            int     iend = trunc(sx2);
            double  devX1 = 1.0 - (sx1 - istart);
            double  devX2 = 1.0 - (sx2 - iend);

            double  destR = 0;
            double  destG = 0;
            double  destB = 0;

            double  dy = devY1;

            if (PRINT == 1)
            {
                printf("x = %d, y = %d\n", x, y);
                printf("sx1 = %f, sx2 = %f\n", sx1, sx2);
                printf("sy1 = %f, sy2 = %f\n", sy1, sy2);
                printf("istart = %d, iend = %d\n", istart, iend);
                printf("jstart = %d, jend = %d\n", jstart, jend);
                printf("devX1 = %f, devX2 = %f\n", devX1, devX2);
                printf("devY1 = %f, devY2 = %f\n", devY1, devY2);
            }

            j = jstart;
            while (j <= jend)
            {
                double  dx = devX1;
                if (j == jend)
                    dy -= devY2;

                i = istart;
                while (i <= iend)
                {
                    if (i == iend)
                        dx -= devX2;
                    else
                        dx = 1.0;
                    

                    /* Read colour of source bitmap at pixel i,j */
                    unsigned int    colour = my_pixel_get(xpm_img, i, j);
                    int          sR = get_argb(colour, 'r');
                    int          sG = get_argb(colour, 'g');
                    int          sB = get_argb(colour, 'b');

                    if (PRINT == 1)
                    {
                        printf("colour = %u\n", colour);
                        printf("sR = %d, sG = %d, sB = %d\n", sR, sG, sB);
                    }

                    /* Area factor */
                    double  AP = fix * fiy * dx * dy;

                    destR += sR * AP;
                    destG += sG * AP;
                    destB += sB * AP;

                    i++;
                }
                dy = 1.0;
                j++;
            }

            if (PRINT == 1)
                printf("color = %d %d %d\n", (int)destR, (int)destG, (int)destB);

            unsigned int    dst_colour = argb_to_hex(0, (int)destR, (int)destG, (int)destB);
            my_pixel_put(scaled_xpm_img, x, y, dst_colour);

            x++;
        }
        x = 0;
        y++;
    }
}