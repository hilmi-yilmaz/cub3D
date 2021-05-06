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

int check_wall_corners(char **map, int x, int y, double angle)
{
    int wall_hor;
    int wall_ver;
    int lower;
    int right;

    wall_hor = 0;
    wall_ver = 0;
    lower = unit_circle_upper_lower(angle);
    right = unit_circle_left_right(angle);

    /* If first quarter of the unit cirle (0 - 0.5*PI) */
    if (lower == 0 && right == 1)
    {
        wall_hor = check_wall(map, x - 1, y);
        wall_ver = check_wall(map, x, y + 1);
    }
    else if (lower == 0 && right == 0)
    {
        wall_hor = check_wall(map, x + 1, y);
        wall_ver = check_wall(map, x, y + 1);
    }
    else if (lower == 1 && right == 1)// && check_coordinates(x + 1, y + 1, map) == 0 && check_wall(map, x + 1, y + 1) != -1)
    { 
        wall_hor = check_wall(map, x - 1, y);
        wall_ver = check_wall(map, x, y - 1);
    }
    else
    {
        wall_hor = check_wall(map, x + 1, y);
        wall_ver = check_wall(map, x, y - 1);
    }
    if (wall_hor == -1 && wall_ver == -1)
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
