/* User defined header files */
#include "../cub3d.h"

/* This function checks whether the data file was complete (no missing data) */
int	check_data_completeness(t_parse *parse)
{
	int i;
	int	error;

	i = 0;
	error = 0;
	if (parse->win_width == UNINIT || parse->win_height == UNINIT)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing resolution data.\n");
		error = -1;
	}
	if (parse->north_text == NULL || parse->south_text == NULL || \
		parse->west_text == NULL || parse->east_text == NULL)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing texture data.\nMake sure to add NO, SO, WE and EA textures.\n");
		error = -1;
	}
    while (i < RGB_DATA_COUNT)
    {
        if (*(parse->floor_colour + i) == UNINIT || \
			*(parse->ceiling_colour + i) == UNINIT)
		{
			if (error != -1)
				printf("Error\n");
			printf("Missing floor/ceiling data.\n");
			error = -1;
			break ;
		}
        i++;
    }
	if (parse->map == NULL)
	{
		if (error != -1)
			printf("Error\n");
		printf("Missing map data.\n");
		error = -1;
	}
	return (error);
}

int check_map(char **map)
{
    int ret;
    int player_x;
    int player_y;
    t_recursion_management rec_man;

    player_x = -1;
    player_y = -1;
    find_player_location(&player_x, &player_y, map);
    if (player_x == -1 && player_y == -1)
    {
        printf("Error\nNo player in the map. Put a N, S, E, W character in the map.\n");
        return (-1);
    }
    recursion_management_init(&rec_man);
    ret = -1;
    while (ret != 0)
    {
        ret = flood_fill(player_x, player_y, map, &rec_man);
        rec_man.max_stack_reached = 0;
        if (rec_man.error == 1)
            break ;
    }
    printf("total recursions = %d\n", rec_man.total_recursions);
    if (rec_man.error == 1)
    {
        printf("Error\nMap is invalid. Make sure the map is surrounded by walls.\n");
        return (-1);
    }
    return (ret);

}