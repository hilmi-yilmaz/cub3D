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
void	init(t_img *img, t_player *player, char **map)
{
	set_start_location(map, &img->player.x, &img->player.y, &img->player.angle);
	//printf("x = %d, y = %d\n", img->player.x, img->player.y);
	player_location(img); /* set x_unit and y_unit */
	img->player.width = 11;
	img->player.height = 11;
	draw_map(img, map);
	draw_player(img);
	//draw_line(img, img->player.alpha, 20);
	
	/* Initialize ray */
	img->ray.len = 1;
	//cast_rays(img, img->info.win_width);
	//cast_ray(img, img->player.alpha);
	//cast_all_rays(img);
	cast_fov(img); /* cast field of vision */

	/* Print the data of the player */
	//printf("x = %d, y = %d, alpha = %f (%f)\n", img->player.x, img->player.y, img->player.alpha, img->player.alpha / PI * 180);
}

void	set_start_location(char **map, int *x, int *y, float *alpha)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*(map + i) != NULL)
	{
		while (map[i][j] != '\0')
		{
			//printf("%d\n", map.map[i][j]);
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
			{
				*x = (j + 0.5) * UNIT; /* check wether value j + 0.5 is not rounded to j */
				*y = (i + 0.5) * UNIT;
				if (map[i][j] == 'N')
					*alpha = 0.5 * PI;
				else if (map[i][j] == 'W')
					*alpha = 1 * PI;
				else if (map[i][j] == 'S')
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