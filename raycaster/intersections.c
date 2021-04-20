/* Standard library header files */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* User defined header files */
#include "../cub3d.h"

int	*intersection(t_img *img, float angle)
{
	int*	horiz;			/* Horizontal intersection with coordinates x, y */
	int*	verti;			/* Vertical intersection with coordinates x, y */
	float 	horiz_dist;
	float 	verti_dist;

	horiz_dist = -1;
	verti_dist = -1;
	printf("Entered intersection function\n");
	horiz = horizontal_intersection(img, angle);
	verti = vertical_intersection(img, angle);
	printf("horiz = %p\n", horiz);
	printf("verti = %p\n", verti);
	if (horiz != NULL)
		horiz_dist = sqrt(pow(img->player.x - *(horiz + 0), 2) + pow(img->player.y - *(horiz + 1), 2));
	if (verti != NULL)
		verti_dist = sqrt(pow(img->player.x - *(verti + 0), 2) + pow(img->player.y - *(verti + 1), 2));

	printf("horiz_dist = %f\n", horiz_dist);
	printf("verti_dist = %f\n", verti_dist);
	printf("angle = %f\n", angle);

	if (horiz_dist == -1)
	{
		free(horiz);
		return (verti);
	}
	if (verti_dist == -1)
	{
		free(verti);
		return (horiz);
	}
	if (verti_dist < horiz_dist)
	{
		free(horiz);
		return (verti);
	}
	else
	{
		free(verti);
		return (horiz);
	}
}

int	*horizontal_intersection(t_img *img, float angle)
{
	int	y; 	/* The y pixel coordinate of the horizontal intersection point */
	int	x; 	/* The x pixel coordinate of the horizontal intersection point */
	int	ya;
	int	xa;
	int	wall;
	int *x_y;
	
	printf("Entered horizontal intersection function\n");
	x_y = (int *)malloc(sizeof(int) * 2);
	x_y[0] = -1;
	x_y[1] = -1;
	if (unit_circle_upper_lower(angle) == 0) /* if ray is facing up */
	{
		y = (int)(img->player.y / UNIT) * UNIT - 1; /* y is in pixel coordinates */
		ya = -64;
	}
	else if (unit_circle_upper_lower(angle) == 1)  /* if ray is facing down */
	{
		y = (int)(img->player.y / UNIT) * UNIT + UNIT; /* y is in pixel coordinates */
		ya = 64;
	}
	x = img->player.x + (img->player.y - y) / tan(angle); /* Also in pixel coordinates */
	printf("x = %d\n", x);
	if (x > img->info.win_width || x < 0)
	{
		free(x_y);
		return (NULL);
	}
	printf("\ny_horizontal = %d = (%d / %d) * %d - 1\n", y, img->player.y, UNIT, UNIT);
	printf("x_horizontal = %d = %d + (%d - %d) / %f\n", x, img->player.x, img->player.y, y, tan(angle));

	/* Find xa */
	xa = UNIT / tan(angle);
	// if (angle > PI && angle <= 2 * PI)
	// 	xa *= -1;
	// if (angle >= -PI && angle < 0)
	// 	xa *= -1;
	if (unit_circle_upper_lower(angle) == 1) /* if alpha is lowerhalf circle of unit circle */
		xa *= -1;
	printf("xa = %d\n", xa);

	/* Check for wall at (x, y) */
	wall = check_wall(img->info.map, x, y);
	if (wall == 1)
	{
		//printf("Found wall at x = %d, y = %d\n", x, y);
		x_y[0] = x;
		x_y[1] = y;
		//draw_point(img, x, y);
		return (x_y);
	}
	if (wall == -1)
	{
		//printf("Can't find horizontal intersection in the image with angle = %f\n", angle);
		free(x_y);
		return (NULL);
	}
	//draw_point(img, x, y);

	while (wall == 0)
	{
		x += xa;
		y += ya;
		if (x > img->info.win_width || x < 0)
		{
			free(x_y);
			return (NULL);
		}
		//draw_point(img, x, y);
		wall = check_wall(img->info.map, x, y);
		if (wall == 1)
		{
			//printf("Found wall at x = %d, y = %d\n", x, y);
			x_y[0] = x;
			x_y[1] = y;
			draw_point(img, x, y);
			return (x_y);
		}
		if (wall == -1)
		{
			//printf("Can't find horizontal intersection in the image with angle = %f\n", angle);
			free(x_y);
			return (NULL);
		}
	}
	return (NULL);
}

int *vertical_intersection(t_img *img, float angle)
{
	int x;
	int y;
	int xa;
	int ya;
	int wall;
	int *x_y;
	
	printf("Entered vertical intersection function\n");
	x_y = (int *)malloc(sizeof(int) * 2);
	x_y[0] = -1;
	x_y[1] = -1;
	if (unit_circle_left_right(angle) == 1) /* Ray facing right */
	{
		x = (int)(img->player.x / UNIT) * UNIT + UNIT;
		xa = UNIT;
		printf("Ray facing RIGHT\n");
	}
	else if (unit_circle_left_right(angle) == 0) /* Ray facing left */
	{
		x = (int)(img->player.x / UNIT) * UNIT - 1;
		xa = -UNIT;
		printf("Ray facing LEFT\n");
	}
	y = img->player.y + (img->player.x - x) * tan(angle);
	printf("y = %d\n", y);
	if (y > img->info.win_height || y < 0)
	{
		free(x_y);
		return (NULL);
	}

	ya = UNIT * tan(angle);
	if (unit_circle_left_right(angle) == 1)
		ya *= -1;

	/* Check for wall at (x, y) */
	wall = check_wall(img->info.map, x, y);
	if (wall == 1)
	{
		//printf("Found wall at x = %d, y = %d\n", x, y);
		x_y[0] = x;
		x_y[1] = y;
		draw_point(img, x, y);
		return (x_y);
	}
	if (wall == -1)
	{
		//printf("Can't find horizontal intersection in the image with angle = %f\n", angle);
		free(x_y);
		return (NULL);
	}
	//draw_point(img, x, y);

	while (wall == 0)
	{
		x += xa;
		y += ya;
		if (y > img->info.win_height || y < 0)
		{
			free(x_y);
			return (NULL);
		}
		if (x > img->info.win_width || x < 0)
		{
			free(x_y);
			return (NULL);
		}
		//draw_point(img, x, y);
		wall = check_wall(img->info.map, x, y);
		if (wall == 1)
		{
			//printf("Found wall at x = %d, y = %d\n", x, y);
			draw_point(img, x, y);
			x_y[0] = x;
			x_y[1] = y;			
			return (x_y);
		}
		if (wall == -1)
		{
			//printf("Can't find horizontal intersection in the image with angle = %f\n", angle);
			free(x_y);
			return (NULL);
		}
	}
	return (NULL);
}