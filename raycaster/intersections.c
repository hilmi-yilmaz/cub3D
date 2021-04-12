/* Standard library header files */
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int	horizontal_intersection(t_img *img)
{
	int	y; 	/* The y pixel coordinate of the horizontal intersection point */
	int	x; 	/* The x pixel coordinate of the horizontal intersection point */
	int	ya;
	int	xa;
	int	wall;
	
	if (unit_circle(img->player.alpha) == 0) /* if ray is facing up */
	{
		y = (int)(img->player.y / UNIT) * UNIT - 1; /* y is in pixel coordinates */
		ya = -64;
	}
	else if (unit_circle(img->player.alpha) == 1)  /* if ray is facing down */
	{
		y = (int)(img->player.y / UNIT) * UNIT + UNIT; /* y is in pixel coordinates */
		ya = 64;
	}
	x = img->player.x + (img->player.y - y) / tan(img->player.alpha); /* Also in pixel coordinates */
	if (x > img->info.win_width || x < 0)
		return (-1);

	printf("\ny_horizontal = %d = (%d / %d) * %d - 1\n", y, img->player.y, UNIT, UNIT);
	printf("x_horizontal = %d = %d + (%d - %d) / %f\n", x, img->player.x, img->player.y, y, tan(img->player.alpha));

	/* Find xa */
	xa = UNIT / tan(img->player.alpha);
	if (img->player.alpha > PI && img->player.alpha <= 2 * PI)
		xa *= -1;
	if (img->player.alpha >= -PI && img->player.alpha < 0)
		xa *= -1;
	printf("xa = %d\n", xa);

	/* Check for wall at (x, y) */
	wall = check_wall(img->info.map, x, y);
	if (wall == 1)
	{
		//printf("Found wall at x = %d, y = %d\n", x, y);
		draw_point(img, x, y);
		return (1);
	}
	if (wall == -1)
	{
		//printf("Can't find horizontal intersection in the image with angle = %f\n", img->player.alpha);
		return (-1);
	}
	//draw_point(img, x, y);

	while (wall == 0)
	{
		x += xa;
		y += ya;
		if (x > img->info.win_width || x < 0)
			return (-1);
		//draw_point(img, x, y);
		wall = check_wall(img->info.map, x, y);
		if (wall == 1)
		{
			//printf("Found wall at x = %d, y = %d\n", x, y);
			draw_point(img, x, y);
			return (1);
		}
		if (wall == -1)
		{
			//printf("Can't find horizontal intersection in the image with angle = %f\n", img->player.alpha);
			return (-1);
		}
	}
	return (0);
}