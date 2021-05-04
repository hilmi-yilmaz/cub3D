/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

int check_wall(char **map, int x, int y)
{
    int x_unit;
    int y_unit;

    /* Convert player unit to map coordinates */
    x_unit = x / UNIT;
    y_unit = y / UNIT;
   
    /* Check for glass wall */
    if (map[y_unit][x_unit] == '1')
        return (-1);
    return (0);
}

int check_coordinates(int x, int y, char **map)
{
    if (x < 0 || y < 0)
        return (-1);
    x /= UNIT;
    y /= UNIT;
    if (y >= ft_arrlen(map) || x > ft_strlen(map[y]))
        return (-1);
    return (0);
}

void    check_directions(t_player *player, char **map)
{
    /* Check north direction */
    player->direction.north = check_wall(map, player->x, player->y - player->speed - GLASS);

    /* Check west direction */
    player->direction.west = check_wall(map, player->x - player->speed - GLASS, player->y);
    
    /* Check east direction */
    player->direction.east = check_wall(map, player->x + player->speed + GLASS, player->y);
    
    /* Check south direction */
    player->direction.south = check_wall(map, player->x, player->y + player->speed + GLASS);
}
