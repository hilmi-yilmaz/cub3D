/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int check_wall(char **map, double x, double y)
{  
    //printf("Checking with x = %d, y = %d\n", (int)x, (int)y);

    if (check_coordinates(x, y, map) == -1)
        return (-1);
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

void    check_directions(t_player *player, char **map)
{
    double  x_tmp;
    double  y_tmp;
    double  x_local;
    double  y_local;
    
    x_tmp = player->x;
    y_tmp = player->y;

    /* Check north */
    x_local = 0.0;
    y_local = player->speed;
    rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
    x_tmp += x_local;
    y_tmp += y_local;
    printf("x_tmp = %f, y_tmp = %f\n", x_tmp, y_tmp);
    player->direction.north = check_wall(map, x_tmp, y_tmp);

    /* Check south */
    x_tmp = player->x;
    y_tmp = player->y;
    x_local = 0.0;
    y_local = -player->speed;
    rotate_vector(&x_local, &y_local, player->angle + 0.5 * PI);
    x_tmp += x_local;
    y_tmp += y_local;
    printf("x_tmp = %f, y_tmp = %f\n", x_tmp, y_tmp);
    player->direction.south = check_wall(map, x_tmp, y_tmp);
}
