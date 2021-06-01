/* Standard library header files */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

void	get_scale_params_x(t_tmpscale *scale_params, t_img *xpm, int width)
{
	scale_params->fx = (double)xpm->width / width;
	scale_params->fix = 1 / scale_params->fx;
	scale_params->fxstep = 0.9999 * scale_params->fx;
}

void	get_scale_params_y(t_tmpscale *scale_params, t_img *xpm, int height)
{
	scale_params->fy = (double)xpm->height / height;
	scale_params->fiy = 1 / scale_params->fy;
	scale_params->fystep = 0.9999 * scale_params->fy;
}

/*
** The get_texture_pixel function puts a pixel from the xpm image into
** the to be drawn wall. It scales the pixel as needed and mixes the colours
** so that no data loss occurs.
**
** Arguments:
**		(t_img *)	xpm: 
**
**
*/
unsigned int	get_texture_pixel(t_img *xpm, t_tmpscale *scale_params, int dest_x, int dest_y)
{
	/* x scaling params */
	scale_params->sx1 = dest_x * scale_params->fx;
	scale_params->sx2 = scale_params->sx1 + scale_params->fxstep;
	scale_params->istart = trunc(scale_params->sx1);
	scale_params->iend = trunc(scale_params->sx2);
	scale_params->devX1 = 1.0 - (scale_params->sx1 - scale_params->istart);
	scale_params->devX2 = 1.0 - (scale_params->sx2 - scale_params->iend);

	/* y scaling params */
	scale_params->sy1 = dest_y * scale_params->fy;
	scale_params->sy2 = scale_params->sy1 + scale_params->fystep;
	scale_params->jstart = trunc(scale_params->sy1);
	scale_params->jend = trunc(scale_params->sy2);
	scale_params->devY1 = 1.0 - (scale_params->sy1 - scale_params->jstart);
	scale_params->devY2 = 1.0 - (scale_params->sy2 - scale_params->jend);

	/* Set dest colours to zero */
	scale_params->destR = 0;
	scale_params->destG = 0;
	scale_params->destB = 0;

	/* Loop over src pixels */
	int	j = scale_params->jstart;
	scale_params->dy = scale_params->devY1;
	while (j <= scale_params->jend)
	{
		if (j == scale_params->jend)
			scale_params->dy -= scale_params->devY2;

		int i = scale_params->istart;
		scale_params->dx = scale_params->devX1;
		while (i <= scale_params->iend)
		{
			if (i == scale_params->iend)
				scale_params->dx -= scale_params->devX2;

            unsigned int    colour = my_pixel_get(xpm, i, j);
            scale_params->sR = get_argb(colour, 'r');
            scale_params->sG = get_argb(colour, 'g');
            scale_params->sB = get_argb(colour, 'b');

            scale_params->AP = scale_params->fix *scale_params->fiy * scale_params->dx * scale_params->dy;
		
            scale_params->destR += (scale_params->sR * scale_params->AP);
            scale_params->destG += (scale_params->sG * scale_params->AP);
            scale_params->destB += (scale_params->sB * scale_params->AP);

			scale_params->dx = 1.0;
			
			i++;
		}
		scale_params->dy = 1.0;
		i = 0;
		j++;
	}
	unsigned int    dst_colour = argb_to_hex(0, (int)scale_params->destR, (int)scale_params->destG, (int)scale_params->destB);
	// my_pixel_put(xpm, dest_x, dest_y, dst_colour);
	return (dst_colour);
}

/*
** y is height of the wall
**
*/
void	pixel_from_xpm_to_window(t_img *img, t_img *xpm, t_tmpscale *scale_params, int x_screen, int x, int y, int win_height)
{
	//int				j;
	unsigned int	colour;
    int 			y_start;
    int 			y_end;
	int				start_xpm;
	int				end_xpm;

	//printf("height = %d\n", y);
	y_start = (win_height - y) / 2;
	start_xpm = 0;
	end_xpm = xpm->height;
	if (y_start < 0)
	{
		start_xpm = -(y_start);
		y_start = 0;
	}
	//printf("start_xpm = %d\n", start_xpm);
	y_end = (win_height + y) / 2;
	if (y_end > win_height - 1)
		y_end = win_height - 1;
	//j = 0;
	while (y_start < y_end)
	{
		//colour = get_texture_pixel(xpm, scale_params, x, j);
		colour = get_texture_pixel(xpm, scale_params, x, start_xpm);
		my_pixel_put(img, x_screen, y_start, colour);
		y_start++;
		start_xpm++;
		//j++;
		//printf("j = %d\n", j);
	}
}