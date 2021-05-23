/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

#define PRINT 0

// static void	init_params(t_scale *scale_params)
// {
//     /* Calculate the scaling factors */
//     scale_params->fx = (double)xpm_width / scaled_xpm_width;
//     scale_params->fy = (double)xpm_height / scaled_xpm_height;

//     /* Correcting for the rounding error */
//     scale_params.fxstep = 0.9999 * scale_params.fx;
//     scale_params.fystep = 0.9999 * scale_params.fy;

//     /* Inverse of fx and fy */
//     scale_params.fix = 1 / scale_params.fx;
//     scale_params.fiy = 1 / scale_params.fy;
// }

void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img, int xpm_width, int xpm_height, int scaled_xpm_width, int scaled_xpm_height)
{
    t_scale	scale_params;
	
	/* Get the address of the xpm img */
    xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);

    /* Get the address of the scaled xpm img */
    scaled_xpm_img->img_addr = mlx_get_data_addr(scaled_xpm_img->img_ptr, &scaled_xpm_img->bits_per_pixel, &scaled_xpm_img->line_size, &scaled_xpm_img->endian);

    // /* Calculate the scaling factors */
    // scale_params.fx = (double)xpm_width / scaled_xpm_width;
    // scale_params.fy = (double)xpm_height / scaled_xpm_height;

    // /* Correcting for the rounding error */
    // scale_params.fxstep = 0.9999 * scale_params.fx;
    // scale_params.fystep = 0.9999 * scale_params.fy;

    // /* Inverse of fx and fy */
    // scale_params.fix = 1 / scale_params.fx;
    // scale_params.fiy = 1 / scale_params.fy;

    if (PRINT == 1)
        printf("fx = %f, fy = %f\n", scale_params.fx, scale_params.fy);

    /* x and y loop over the destination bitmap, the scaled bitmap */
    int x = 0;
    int y = 0;

    /* i and j loop over the source bitmap, the original image */
    int i = 0;
    int j = 0;

    while (y < scaled_xpm_height)
    {
        scale_params.sy1 = y * scale_params.fy;
        scale_params.sy2 = scale_params.sy1 + scale_params.fystep;
        scale_params.jstart = trunc(scale_params.sy1);
        scale_params.jend = trunc(scale_params.sy2);
        scale_params.devY1 = 1.0 - (scale_params.sy1 - scale_params.jstart);
        scale_params.devY2 = 1.0 - (scale_params.sy2 - scale_params.jend);

        if (PRINT == 1)
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

        while (x < scaled_xpm_width)
        {
            scale_params.sx1 = x * scale_params.fx;
            scale_params.sx2 = scale_params.sx1 + scale_params.fxstep;
            scale_params.istart = trunc(scale_params.sx1);
            scale_params.iend = trunc(scale_params.sx2);
            scale_params.devX1 = 1.0 - (scale_params.sx1 - scale_params.istart);
            scale_params.devX2 = 1.0 - (scale_params.sx2 - scale_params.iend);

            scale_params.destR = 0;
            scale_params.destG = 0;
            scale_params.destB = 0;

            scale_params.dy = scale_params.devY1;

            if (PRINT == 1)
            {
                printf("x = %d, y = %d\n", x, y);
                printf("sx1 = %f, sx2 = %f\n", scale_params.sx1, scale_params.sx2);
                printf("sy1 = %f, sy2 = %f\n", scale_params.sy1, scale_params.sy2);
                printf("istart = %d, iend = %d\n", scale_params.istart, scale_params.iend);
                printf("jstart = %d, jend = %d\n", scale_params.jstart, scale_params.jend);
                printf("devX1 = %f, devX2 = %f\n", scale_params.devX1, scale_params.devX2);
                printf("devY1 = %f, devY2 = %f\n", scale_params.devY1, scale_params.devY2);
            }

            j = scale_params.jstart;
            while (j <= scale_params.jend)
            {
                scale_params.dx = scale_params.devX1;
                if (j == scale_params.jend)
                    scale_params.dy -= scale_params.devY2;

                i = scale_params.istart;
                while (i <= scale_params.iend)
                {
                    if (i == scale_params.iend)
                        scale_params.dx -= scale_params.devX2;
                    else
                        scale_params.dx = 1.0;
                    

                    /* Read colour of source bitmap at pixel i,j */
                    unsigned int    colour = my_pixel_get(xpm_img, i, j);
                    scale_params.sR = get_argb(colour, 'r');
                    scale_params.sG = get_argb(colour, 'g');
                    scale_params.sB = get_argb(colour, 'b');

                    if (PRINT == 1)
                    {
                        printf("colour = %u\n", colour);
                        printf("sR = %d, sG = %d, sB = %d\n", scale_params.sR, scale_params.sG, scale_params.sB);
                    }

                    /* Area factor */
                    scale_params.AP = scale_params.fix * scale_params.fiy * scale_params.dx * scale_params.dy;

                    scale_params.destR += scale_params.sR * scale_params.AP;
                    scale_params.destG += scale_params.sG * scale_params.AP;
                    scale_params.destB += scale_params.sB * scale_params.AP;

                    i++;
                }
                scale_params.dy = 1.0;
                j++;
            }

            if (PRINT == 1)
                printf("color = %d %d %d\n", (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);

            unsigned int    dst_colour = argb_to_hex(0, (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);
            my_pixel_put(scaled_xpm_img, x, y, dst_colour);

            x++;
        }
        x = 0;
        y++;
    }
}