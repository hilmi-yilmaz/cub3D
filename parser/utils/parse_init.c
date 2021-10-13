/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:17:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/13 11:53:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_init.h"

void	parse_init(t_parse *parse)
{
	int	i;

	i = 0;
	parse->win_width = WINDOW_WIDTH;
	parse->win_height = WINDOW_HEIGHT;
	parse->north_text = NULL;
	parse->south_text = NULL;
	parse->west_text = NULL;
	parse->east_text = NULL;
	while (i < RGB_DATA_COUNT)
	{
		parse->floor_colour[i] = UNINIT;
		parse->ceiling_colour[i] = UNINIT;
		i++;
	}
	parse->map = NULL;
}

void	recursion_management_init(t_recursion_management *rec_man)
{
	rec_man->i = 0;
	rec_man->total_recursions = 0;
	rec_man->max_stack_reached = 0;
	rec_man->save_x = -1;
	rec_man->save_y = -1;
	rec_man->error = 0;
}
