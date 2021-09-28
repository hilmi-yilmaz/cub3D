/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void	print_width_walls(int *width_walls)
{
    int p = 0;
    int total = 0;
    while (width_walls[p] != -1)
    {
        printf("%d ", width_walls[p]);
        total += width_walls[p];
        p++;
    }
}

void    print_ray_data(t_ray ray)
{
        printf("x = %f\n", ray.x);
        printf("y = %f\n", ray.y);
        printf("xa = %.15f\n", ray.xa);
        printf("ya = %.15f\n", ray.ya);
        printf("error = %d\n", ray.error);
}

void    print_rays_array(double *rays_array, int width)
{
    int i;

    i = 0;
    while (i < width)
    {
        printf("%.15f ", rays_array[i]);
		if (i % 4 == 0)
			printf("\n");
        i++;
    }
    printf("\n\n");
}

void    print_side_array(int *side_array, int width)
{
    int i;

    i = 0;
    while (i < width)
    {
        printf("%d = %d\n", i, side_array[i]);
		if (i % 10 == 0 && i != 0)
			printf("\n");
        i++;
    }
    printf("\n\n");
}

void    print_columns(unsigned int *arr, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        printf("%u ", arr[i]);
        i++;
    }
    printf("\n\n");
}
