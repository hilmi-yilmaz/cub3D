/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:18:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:56:43 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "print_data.h"

void	print_intersections(t_player *player, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		printf("hor: x = %5f | y = %5f\n", \
				player->hor_ray[i].x, player->hor_ray[i].y);
		printf("ver: x = %5f | y = %5f\n\n", \
				player->ver_ray[i].x, player->ver_ray[i].y);
		i++;
	}
}

void	print_ray_data(t_ray ray)
{
	printf("x = %f\n", ray.x);
	printf("y = %f\n", ray.y);
	printf("xa = %.15f\n", ray.xa);
	printf("ya = %.15f\n", ray.ya);
	printf("error = %d\n", ray.error);
}

void	print_rays_array(double *rays_array, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		printf("%.15f ", rays_array[i]);
		if (i % 4 == 0)
			printf("\n");
		i++;
	}
	printf("\n\n");
}

void	print_side_array(int *side_array, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		printf("%d = %d\n", i, side_array[i]);
		if (i % 10 == 0 && i != 0)
			printf("\n");
		i++;
	}
	printf("\n\n");
}
