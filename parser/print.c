/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

void    print_parse(t_parse *parse)
{
    printf("win_width = |%d|\n", parse->win_width);
    printf("win_height = |%d|\n", parse->win_height);
    printf("north_texture = |%s|\n", parse->north_text);
    printf("south_texture = |%s|\n", parse->south_text);
    printf("west_texture = |%s|\n", parse->west_text);
    printf("east_texture = |%s|\n", parse->east_text);
    printf("Floor colour = |%d,%d,%d|\n", parse->floor_colour[0], parse->floor_colour[1], parse->floor_colour[2]);
    printf("Ceiling colour = |%d,%d,%d|\n", parse->ceiling_colour[0], parse->ceiling_colour[1], parse->ceiling_colour[2]);
}

void    print_map(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*(map + i) != NULL)
    {
        printf("|");
        while (map[i][j] != '\0')
        {
            printf("%c", *(*(map + i) + j));
            j++;
        }
        //printf("     %d", parse->map_len[i]);
        printf("\n");
        j = 0;
        i++;
    }
}