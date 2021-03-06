/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

#define PRINT 0

void    scale_column(t_img *scaled_xpm, int column, unsigned int *dst, int dst_height)
{
    double  fy = (double)scaled_xpm->height / dst_height;
    double  fystep = 0.9999 * fy;
    double  fiy = 1 / fy;

    int y = 0;
    int j = 0;

    //printf("scaled_xpm->height = %d\n", scaled_xpm->height);
    //printf("dst_height = %d\n", dst_height);

    while (y < dst_height)
    {
        double sy1 = y * fy;
        double sy2 = sy1 + fystep;
        double jstart = trunc(sy1);
        double jend = trunc(sy2);
        double devY1 = 1.0 - (sy1 - jstart);
        double devY2 = 1.0 - (sy2 - jend);

        double destR = 0;
        double destG = 0;
        double destB = 0;

        double dy = devY1;
        j = jstart;
        while(j <= jend)
        {
            if (j == jend)
                dy -= devY2;

            /* Read colour of source bitmap at pixel i,j */
            unsigned int colour = my_pixel_get(scaled_xpm, column, j);
            double sR = get_argb(colour, 'r');
            double sG = get_argb(colour, 'g');
            double sB = get_argb(colour, 'b');

            /* Area factor */
            double AP = fiy * dy;

            destR += sR * AP;
            destG += sG * AP;
            destB += sB * AP;

            dy = 1.0;

            j++;
        }
        unsigned int    dst_colour = argb_to_hex(0, (int)destR, (int)destG, (int)destB);
        //printf("%p\n", scaled_xpm_img);
        //my_pixel_put(scaled_xpm, column, y, dst_colour);
        dst[y] = dst_colour;
        //printf(" ---- %u\n", dst_colour);
        y++;
    }
}

void    scale_bmp_all_rows(t_img *xpm_img, t_img *scaled_xpm)
{
    int		i;
	t_scale	scale_params;

    i = 0;
    while (i < xpm_img->width)
    {
		scale_params.f = (double)xpm_img->width / scaled_xpm->width;
    	scale_params.fi = 1 / scale_params.f;
    	scale_params.fstep = 0.9999 * scale_params.f;
		scale_bmp_single_row(xpm_img, scaled_xpm, &scale_params, i);
        i++;
    }
}

void    scale_bmp_single_row(t_img *xpm_img, t_img *scaled_xpm, t_scale *scale_params, int row)
{
    int src_i;  // loops over rows/columns source image
    int dst_i;  // loops over rows/columns destination image

    //xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);
    //scaled_xpm->img_addr = mlx_get_data_addr(scaled_xpm->img_ptr, &scaled_xpm->bits_per_pixel, &scaled_xpm->line_size, &scaled_xpm->endian);

    src_i = 0;
    dst_i = 0;

	//printf("fx = %f\n", scale_params->f);
    //scale_params.fix = 1 / scale_params.fx; 
    while (dst_i < scaled_xpm->width)
    {
        scale_params->s1 = dst_i * scale_params->f;
        scale_params->s2 = scale_params->s1 + scale_params->fstep;
        scale_params->start = trunc(scale_params->s1);
        scale_params->end = trunc(scale_params->s2);
        scale_params->dev1 = 1.0 - (scale_params->s1 - scale_params->start);
        scale_params->dev2 = 1.0 - (scale_params->s2 - scale_params->end);

        scale_params->destR = 0;
        scale_params->destG = 0;
        scale_params->destB = 0;

        if (PRINT == 1)
        {
            printf(" >>>>>>>>> x = %d, y = %d <<<<<<<<<<< \n", dst_i, row);
            printf("sx1 = %f, sx2 = %f\n", scale_params->s1, scale_params->s2);
            printf("istart = %d, iend = %d\n", scale_params->start, scale_params->end);
            printf("devX1 = %f, devX2 = %f\n", scale_params->dev1, scale_params->dev2);
        }

		scale_params->d = scale_params->dev1;
		src_i = scale_params->start;
        while (src_i <= scale_params->end)
        {
			// if (i == scale_params.istart)
            //     scale_params.dx = scale_params.devX1;
            if (src_i == scale_params->end)
                scale_params->d -= scale_params->dev2;


            //printf("row = %d, i = %d\n", row, src_i);
            unsigned int    colour = my_pixel_get(xpm_img, src_i, row);
            scale_params->sR = get_argb(colour, 'r');
            scale_params->sG = get_argb(colour, 'g');
            scale_params->sB = get_argb(colour, 'b');

			if (PRINT == 1)
			{
				printf("colour = %u\n", colour);
				printf("sR = %d, sG = %d, sB = %d at i = %d, row = %d\n", scale_params->sR, scale_params->sG, scale_params->sB, src_i, row);
			}

			//printf("dx = %f\n", scale_params->d);
            scale_params->AP = scale_params->fi * scale_params->d;
		
            scale_params->destR += (scale_params->sR * scale_params->AP);
            scale_params->destG += (scale_params->sG * scale_params->AP);
            scale_params->destB += (scale_params->sB * scale_params->AP);

			if (PRINT == 1)
			{
				printf("AP = %f\n", scale_params->AP);
				printf("destR = %d\ndestG = %d\ndestB = %d\n", (int)scale_params->destR, (int)scale_params->destG, (int)scale_params->destB);
			}
			scale_params->d = 1.0;

            src_i++;
        }
        unsigned int    dst_colour = argb_to_hex(0, (int)scale_params->destR, (int)scale_params->destG, (int)scale_params->destB);
        //printf("%p\n", scaled_xpm_img);

		if (PRINT == 1)
			printf("--------------------------------------------------------- >>>> color = %d %d %d\n", (int)scale_params->destR, (int)scale_params->destG, (int)scale_params->destB);

        my_pixel_put(scaled_xpm, dst_i, row, dst_colour);
        dst_i++;
    }
}

// void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img)
// {
//     t_scale	scale_params;
	
// 	/* Get the address of the xpm img */
//     xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);

//     /* Get the address of the scaled xpm img */
//     scaled_xpm_img->img_addr = mlx_get_data_addr(scaled_xpm_img->img_ptr, &scaled_xpm_img->bits_per_pixel, &scaled_xpm_img->line_size, &scaled_xpm_img->endian);

//     /* Calculate the scaling factors */
//     scale_params.fx = (double)xpm_img->width / scaled_xpm_img->width;
//     scale_params.fy = (double)xpm_img->height / scaled_xpm_img->height;

//     /* Correcting for the rounding error */
//     scale_params.fxstep = 0.9999 * scale_params.fx;
//     scale_params.fystep = 0.9999 * scale_params.fy;

//     /* Inverse of fx and fy */
//     scale_params.fix = 1.0 / scale_params.fx;
//     scale_params.fiy = 1.0 / scale_params.fy;

//     if (PRINT == 1)
//         printf("fx = %f, fy = %f\n", scale_params.fx, scale_params.fy);

//     /* x and y loop over the destination bitmap, the scaled bitmap */
//     int x = 0;
//     int y = 0;

//     /* i and j loop over the source bitmap, the original image */
//     int i = 0;
//     int j = 0;

//     while (y < scaled_xpm_img->height)
//     {
//         scale_params.sy1 = y * scale_params.fy;
//         scale_params.sy2 = scale_params.sy1 + scale_params.fystep;
//         scale_params.jstart = trunc(scale_params.sy1);
//         scale_params.jend = trunc(scale_params.sy2);
//         scale_params.devY1 = 1.0 - (scale_params.sy1 - scale_params.jstart);
//         scale_params.devY2 = 1.0 - (scale_params.sy2 - scale_params.jend);

//         if (PRINT == 1)
//             printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

//         while (x < scaled_xpm_img->width)
//         {
//             scale_params.sx1 = x * scale_params.fx;
//             scale_params.sx2 = scale_params.sx1 + scale_params.fxstep;
//             scale_params.istart = trunc(scale_params.sx1);
//             scale_params.iend = trunc(scale_params.sx2);
//             scale_params.devX1 = 1.0 - (scale_params.sx1 - scale_params.istart);
//             scale_params.devX2 = 1.0 - (scale_params.sx2 - scale_params.iend);

//             scale_params.destR = 0;
//             scale_params.destG = 0;
//             scale_params.destB = 0;

//             scale_params.dy = scale_params.devY1;

//             if (PRINT == 1)
//             {
//                 printf(" >>>>>>>>> x = %d, y = %d <<<<<<<<<<< \n", x, y);
//                 printf("sx1 = %f, sx2 = %f\n", scale_params.sx1, scale_params.sx2);
//                 printf("sy1 = %f, sy2 = %f\n", scale_params.sy1, scale_params.sy2);
//                 printf("istart = %d, iend = %d\n", scale_params.istart, scale_params.iend);
//                 printf("jstart = %d, jend = %d\n", scale_params.jstart, scale_params.jend);
//                 printf("devX1 = %f, devX2 = %f\n", scale_params.devX1, scale_params.devX2);
//                 printf("devY1 = %f, devY2 = %f\n", scale_params.devY1, scale_params.devY2);
//             }

//             j = scale_params.jstart;
//             while (j <= scale_params.jend)
//             {
//                 //scale_params.dx = scale_params.devX1;
//                 scale_params.dx = 1.0;
//                 if (j == scale_params.jend)
//                     scale_params.dy -= scale_params.devY2;

//                 i = scale_params.istart;
//                 while (i <= scale_params.iend)
//                 {
//                     if (i == scale_params.istart)
//                         scale_params.dx = scale_params.devX1;
//                     if (i == scale_params.iend)
//                         scale_params.dx = 1.0 - scale_params.devX2;

//                     if (PRINT == 1)
//                     {
//                         printf("dx = %f, dy = %f\n", scale_params.dx, scale_params.dy);
//                     }
                    
//                     /* Read colour of source bitmap at pixel i,j */
//                     unsigned int    colour = my_pixel_get(xpm_img, i, j);
//                     scale_params.sR = get_argb(colour, 'r');
//                     scale_params.sG = get_argb(colour, 'g');
//                     scale_params.sB = get_argb(colour, 'b');

//                     if (PRINT == 1)
//                     {
//                         printf("colour = %u\n", colour);
//                         printf("sR = %d, sG = %d, sB = %d at i = %d, j = %d\n", scale_params.sR, scale_params.sG, scale_params.sB, i, j);
//                     }

//                     /* Area factor */
//                     scale_params.AP = scale_params.fix * scale_params.fiy * scale_params.dx * scale_params.dy;

//                     scale_params.destR += (scale_params.sR * scale_params.AP);
//                     scale_params.destG += (scale_params.sG * scale_params.AP);
//                     scale_params.destB += (scale_params.sB * scale_params.AP);

//                     if (PRINT == 1)
//                     {
//                         printf("AP = %f\n", scale_params.AP);
//                         printf("destR = %d\ndestG = %d\ndestB = %d\n", (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);
//                     }

//                     i++;
//                 }
//                 scale_params.dy = 1.0;
//                 j++;
//             }

//             if (PRINT == 1)
//                 printf("--------------------------------------------------------- >>>> color = %d %d %d\n", (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);

//             unsigned int    dst_colour = argb_to_hex(0, (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);
//             //printf("%p\n", scaled_xpm_img);
//             my_pixel_put(scaled_xpm_img, x, y, dst_colour);

//             x++;
//         }
//         x = 0;
//         y++;
//     }
// }

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

// void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img, int xpm_width, int xpm_height, int scaled_xpm_width, int scaled_xpm_height)
// {
//     t_scale	scale_params;
	
// 	/* Get the address of the xpm img */
//     xpm_img->img_addr = mlx_get_data_addr(xpm_img->img_ptr, &xpm_img->bits_per_pixel, &xpm_img->line_size, &xpm_img->endian);

//     /* Get the address of the scaled xpm img */
//     scaled_xpm_img->img_addr = mlx_get_data_addr(scaled_xpm_img->img_ptr, &scaled_xpm_img->bits_per_pixel, &scaled_xpm_img->line_size, &scaled_xpm_img->endian);

//     /* Calculate the scaling factors */
//     scale_params.fx = (double)xpm_width / scaled_xpm_width;
//     scale_params.fy = (double)xpm_height / scaled_xpm_height;

//     /* Correcting for the rounding error */
//     scale_params.fxstep = 0.9999 * scale_params.fx;
//     scale_params.fystep = 0.9999 * scale_params.fy;

//     /* Inverse of fx and fy */
//     scale_params.fix = 1 / scale_params.fx;
//     scale_params.fiy = 1 / scale_params.fy;

//     if (PRINT == 1)
//         printf("fx = %f, fy = %f\n", scale_params.fx, scale_params.fy);

//     /* x and y loop over the destination bitmap, the scaled bitmap */
//     int x = 0;
//     int y = 0;

//     /* i and j loop over the source bitmap, the original image */
//     int i = 0;
//     int j = 0;

//     while (y < scaled_xpm_height)
//     {
//         scale_params.sy1 = y * scale_params.fy;
//         scale_params.sy2 = scale_params.sy1 + scale_params.fystep;
//         scale_params.jstart = trunc(scale_params.sy1);
//         scale_params.jend = trunc(scale_params.sy2);
//         scale_params.devY1 = 1.0 - (scale_params.sy1 - scale_params.jstart);
//         scale_params.devY2 = 1.0 - (scale_params.sy2 - scale_params.jend);

//         if (PRINT == 1)
//             printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

//         while (x < scaled_xpm_width)
//         {
//             scale_params.sx1 = x * scale_params.fx;
//             scale_params.sx2 = scale_params.sx1 + scale_params.fxstep;
//             scale_params.istart = trunc(scale_params.sx1);
//             scale_params.iend = trunc(scale_params.sx2);
//             scale_params.devX1 = 1.0 - (scale_params.sx1 - scale_params.istart);
//             scale_params.devX2 = 1.0 - (scale_params.sx2 - scale_params.iend);

//             scale_params.destR = 0;
//             scale_params.destG = 0;
//             scale_params.destB = 0;

//             scale_params.dy = scale_params.devY1;

//             if (PRINT == 1)
//             {
//                 printf("x = %d, y = %d\n", x, y);
//                 printf("sx1 = %f, sx2 = %f\n", scale_params.sx1, scale_params.sx2);
//                 printf("sy1 = %f, sy2 = %f\n", scale_params.sy1, scale_params.sy2);
//                 printf("istart = %d, iend = %d\n", scale_params.istart, scale_params.iend);
//                 printf("jstart = %d, jend = %d\n", scale_params.jstart, scale_params.jend);
//                 printf("devX1 = %f, devX2 = %f\n", scale_params.devX1, scale_params.devX2);
//                 printf("devY1 = %f, devY2 = %f\n", scale_params.devY1, scale_params.devY2);
//             }

//             j = scale_params.jstart;
//             while (j <= scale_params.jend)
//             {
//                 scale_params.dx = scale_params.devX1;
//                 if (j == scale_params.jend)
//                     scale_params.dy -= scale_params.devY2;

//                 i = scale_params.istart;
//                 while (i <= scale_params.iend)
//                 {
//                     if (i == scale_params.iend)
//                         scale_params.dx -= scale_params.devX2;
//                     else
//                         scale_params.dx = 1.0;
                    

//                     /* Read colour of source bitmap at pixel i,j */
//                     unsigned int    colour = my_pixel_get(xpm_img, i, j);
//                     scale_params.sR = get_argb(colour, 'r');
//                     scale_params.sG = get_argb(colour, 'g');
//                     scale_params.sB = get_argb(colour, 'b');

//                     if (PRINT == 1)
//                     {
//                         printf("colour = %u\n", colour);
//                         printf("sR = %d, sG = %d, sB = %d\n", scale_params.sR, scale_params.sG, scale_params.sB);
//                     }

//                     /* Area factor */
//                     scale_params.AP = scale_params.fix * scale_params.fiy * scale_params.dx * scale_params.dy;

//                     scale_params.destR += scale_params.sR * scale_params.AP;
//                     scale_params.destG += scale_params.sG * scale_params.AP;
//                     scale_params.destB += scale_params.sB * scale_params.AP;

//                     i++;
//                 }
//                 scale_params.dy = 1.0;
//                 j++;
//             }

//             if (PRINT == 1)
//                 printf("color = %d %d %d\n", (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);

//             unsigned int    dst_colour = argb_to_hex(0, (int)scale_params.destR, (int)scale_params.destG, (int)scale_params.destB);
//             my_pixel_put(scaled_xpm_img, x, y, dst_colour);

//             x++;
//         }
//         x = 0;
//         y++;
//     }
// }