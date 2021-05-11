/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int check_wall(char **map, double x, double y)
{  
    /* Check for glass wall */
    if (map[(int)y][(int)x] == '1')
        return (1);
    return (0);
}

int check_coordinates(double x, double y, char **map)
{
    if (x < 0 || y < 0 || x > INF || y > INF)
        return (-1);
    if ((int)y >= ft_arrlen(map) || x > ft_strlen(map[(int)y]))
        return (-1);
    return (0);
}
