/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void    print_ray_data(t_ray ray)
{
    printf("hor_x = %d\n", ray.hor_x);
    printf("hor_y = %d\n", ray.hor_y);
    printf("hor_xa = %.15f\n", ray.hor_xa);
    printf("hor_ya = %.15f\n", ray.hor_ya);
    printf("---------------------------------\n");
    printf("ver_x = %d\n", ray.ver_x);
    printf("ver_y = %d\n", ray.ver_y);
    printf("ver_xa = %.15f\n", ray.ver_xa);
    printf("ver_ya = %.15f\n", ray.ver_ya);
}
