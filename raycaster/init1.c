/* Standard library header files */
#include <stdio.h>

/* User defined header files */
#include "../cub3d.h"

/*
** The init function draws the 2D map.
** It initializes the player with its location and orientation.
** It also casts the rays according to the orientation of the player.
**
** Arguments:
**		(t_img *)	img:	this is the struct that contains all
**							information about the window, player and rays.
**
** Returns:
**		(void)		None
*/
void	init(t_img *img)
{
	set_start_location(img->info.map, &img->player.x, &img->player.y, &img->player.alpha);
	//printf("x = %d, y = %d\n", img->player.x, img->player.y);
	player_location(img);
	img->player.width = 11;
	img->player.height = 11;
	draw_map(img, &img->info);
	draw_player(img);
	draw_line(img, img->player.x, img->player.y, 20);
	
	/* Initialize ray */
	img->ray.len = 1;
	horizontal_intersection(img);
	//cast_ray(img);

	/* Print the data of the player */
	printf("x = %d, y = %d, alpha = %f (%f)\n", img->player.x, img->player.y, img->player.alpha, img->player.alpha / PI * 180);
}

void	set_start_location(t_map map, int *x, int *y, float *alpha)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*(map.map + i) != NULL)
	{
		while (j < map.len_element[i])
		{
			//printf("%d\n", map.map[i][j]);
			if (map.map[i][j] == 'N' || map.map[i][j] == 'W' || map.map[i][j] == 'S' || map.map[i][j] == 'E')
			{
				*x = (j + 0.5) * UNIT;
				*y = (i + 0.5) * UNIT;
				if (map.map[i][j] == 'N')
					*alpha = 0.5 * PI;
				else if (map.map[i][j] == 'W')
					*alpha = 1 * PI;
				else if (map.map[i][j] == 'S')
					*alpha = 1.5 * PI;
				else
					*alpha = 0 * PI;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}