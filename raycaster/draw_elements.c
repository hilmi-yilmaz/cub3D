/* User defined header files */
#include "../cub3d.h"

#include <stdio.h>

void	draw_floor_ceiling(t_img *main, t_parse *parse)
{
	int				i;
	int				j;
	unsigned int	ceiling_colour;
	unsigned int	floor_colour;

	i = 0;
	j = 0;
	ceiling_colour = argb_to_hex(0, parse->ceiling_colour[0], \
									parse->ceiling_colour[1], \
									parse->ceiling_colour[2]);
	floor_colour = argb_to_hex(0, parse->floor_colour[0], \
									parse->floor_colour[1], \
									parse->floor_colour[2]);
	while (i < parse->win_height)
	{
		while (j < parse->win_width)
		{
			if (i < parse->win_height / 2)
				my_pixel_put(main, j, i, ceiling_colour);
			else
				my_pixel_put(main, j, i, floor_colour);
			j++;
		}
		j = 0;
		i++;
	}
}
