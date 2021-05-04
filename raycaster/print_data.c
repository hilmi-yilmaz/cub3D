/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void    print_ray_data(t_ray ray)
{
    printf("x = %f\n", ray.x);
    printf("y = %f\n", ray.y);
    printf("xa = %.15f\n", ray.xa);
    printf("ya = %.15f\n", ray.ya);
    printf("error = %d\n", ray.error);
}
