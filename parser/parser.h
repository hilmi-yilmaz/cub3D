/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:00:01 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:01:56 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Macros */
# define RGB_DATA_COUNT 3
# define UNINIT -1

/* Data structures */
typedef struct s_parse
{
	int		win_width;
	int		win_height;
	char	*north_text;
	char	*south_text;
	char	*west_text;
	char	*east_text;
	int		floor_colour[RGB_DATA_COUNT];
	int		ceiling_colour[RGB_DATA_COUNT];
	char	**map;
}				t_parse;

typedef struct s_recursion_management
{
	unsigned int	i;
	unsigned int	total_recursions;
	char			max_stack_reached;
	int				save_x;
	int				save_y;
	char			error;

}	t_recursion_management;

#endif