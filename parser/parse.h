/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:07:59 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/11 17:08:00 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define RGB_DATA_COUNT 3
# define RESOLUTION_DATA_COUNT 2
# define MAX_KOMMAS 2
# define STACK_MAX 10000
# define UNIT 1

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

/* parse_main.c */
int		parse_main(t_parse *parse, char **argv);

/* init.c */
void	parse_init(t_parse *parse);
void	recursion_management_init(t_recursion_management *rec_man);

/* parse_data.c */
int		parse_data(int fd, t_parse *parse);

/* parse_resolution.c */
int		parse_resolution(int *win_width, int *win_height, char *line);

/* parse_textures.c */
int		parse_textures(t_parse *parse, char *line);

/* parse_colour.c */
int		parse_colour(t_parse *parse, char *line);

/* parse_map.c */
int		parse_map(int fd, t_parse *parse, char *line);

/* checks.c */
int		check_map(char **map);
int		check_data_completeness(t_parse *parse);

/* print.c */
void	print_parse(t_parse *parse);
void	print_map(char **map);

/* utils.c */
void	find_player_location(int *x, int *y, char **map);
char	**copy_map(char **map);

/* flood_fill.c */
int		managed_flood_fill(int player_x, int player_y, char **map, \
							t_recursion_management *rec_man);

/* free_data.c */
void	free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);

#endif